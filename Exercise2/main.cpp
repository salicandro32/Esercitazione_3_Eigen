#include <iostream>
#include <iomanip>
#include <Eigen/Eigen>

using namespace std;
using namespace Eigen;


                                        /* *** DATA *** */
Matrix2d A1() 
{
    Vector4d v;
    v <<5.547001962252291e-01, -3.770900990025203e-02, 8.320502943378437e-01,
    -9.992887623566787e-01;
    Matrix2d A = v.reshaped (2, 2).transpose(); 
    return A;
}

Matrix2d A2()
{
    Vector4d v;
    v <<5.547001962252291e-01, -5.540607316466765e-01, 8.320502943378437e-01,
    -8.324762492991313e-01;
    Matrix2d A = v.reshaped (2, 2).transpose(); 
    return A;
}

Matrix2d A3() 
{
    Vector4d v;
    v <<5.547001962252291e-01, -5.547001955851905e-01, 8.320502943378437e-01,
    -8.320502947645361e-01;
    Matrix2d A = v.reshaped (2, 2).transpose(); 
    return A;
}

Vector2d b1()
{
    Vector2d v;
    v << -5.169911863249772e-01, 1.672384680188350e-01;
    return v;
}

Vector2d b2()
{
    Vector2d v;
    v << -6.394645785530173e-04, 4.259549612877223e-04;
    return v;
}

Vector2d b3()
{
    Vector2d v;
    v << -6.400391328043042e-10, 4.266924591433963e-10;
    return v;
}

Vector2d real_sol()
{
    Vector2d v;
    v<< -1, -1;
    return v;
}

                            /* *** FUNCTIONS *** */

Vector2d solve_lu(Matrix2d A, Vector2d b){
    Vector2d sol;
    sol = A.lu().solve(b);
    return sol;
}

Vector2d solve_qr(Matrix2d A, Vector2d b){
    Vector2d sol;
    sol = A.householderQr().solve(b);
    return sol;
}

double err_rel(VectorXd v, VectorXd w){
    VectorXd z = v-w;
    double nz = z.norm();
    double nw = w.norm();
    double res = nz/nw;
    return res;
}


int main()
{
    const Vector2d exact_sol = real_sol();
    const Matrix2d a1 = A1();
    const Matrix2d a2 = A2();
    const Matrix2d a3 = A3();
    const Vector2d b_1 = b1();
    const Vector2d b_2 = b2();
    const Vector2d b_3 = b3();
    const Vector2d sol_1_lu = solve_lu(a1, b_1);
    const Vector2d sol_2_lu = solve_lu(a2, b_2);
    const Vector2d sol_3_lu = solve_lu(a3, b_3);
    const Vector2d sol_1_qr = solve_qr(a1, b_1);
    const Vector2d sol_2_qr = solve_qr(a2, b_2);
    const Vector2d sol_3_qr = solve_qr(a3, b_3);

    /* ***PRINT RESULTS *** */
    cout<<setprecision(18);
    cout<<scientific;
    cout<<"Sistema 1: "<<endl;
    cout<<"Errore relativo con LU: "<<err_rel(sol_1_lu, exact_sol)<<endl;
    cout<<"Errore relativo con QR: "<<err_rel(sol_1_qr, exact_sol)<<endl;
    cout<<"Sistema 2: "<<endl;
    cout<<"Errore relativo con LU: "<<err_rel(sol_2_lu, exact_sol)<<endl;
    cout<<"Errore relativo con QR: "<<err_rel(sol_2_qr, exact_sol)<<endl;
    cout<<"Sistema 3: "<<endl;
    cout<<"Errore relativo con LU: "<<err_rel(sol_3_lu, exact_sol)<<endl;
    cout<<"Errore relativo con QR: "<<err_rel(sol_3_qr, exact_sol)<<endl;
    return 0;
}