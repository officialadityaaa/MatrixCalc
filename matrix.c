#include <stdlib.h>
#include <stdio.h>
#include <math.h>
void input(float mat[][10], int row, int col)
{
    for (int i = 0; i < (row); i++)
    {
        printf("Enter Row %d : ", i + 1);
        for (int j = 0; j < (col); j++)
            scanf("%f", &mat[i][j]);
    }
}

void REF(float mat[][10], float ref[][10], int row, int col)
{
    float pvt = 0, mul;
    int i, j;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
            ref[i][j] = mat[i][j];
    }
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
        {
            if (ref[i][j] != 0)
            {
                pvt = ref[i][j];
                break;
            }
        }
        for (int l = i + 1; l < row; l++)
        {
            mul = ref[l][j] / (pvt);
            for (int m = 0; m < col; m++)
            {
                ref[l][m] -= (mul) * (ref[i][m]);
                if (abs(ref[l][m] - 0) <= 0.00001)
                    ref[l][m] = 0;
            }
        }
    }
}

void display(float mat[][10], int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
            printf("%.4f\t", mat[i][j]);
        printf("\n");
    }
}

void product(float a[][10], float q[][10], float pro[][10], int r1, int c1, int r2, int c2)
{
    if (c1 != r2)
    {
        printf("Multiplication does not exists !!");
        return;
    }
    for (int i = 0; i < r1; i++)
    {
        for (int j = 0; j < c2; j++)
        {
            pro[i][j] = 0;
            for (int k = 0; k < r2; k++)
            {
                pro[i][j] += a[i][k] * q[k][j];
            }
        }
    }
}

void getCofactor(float A[][10], float temp[][10], int p, int q, int n)
{
    int i = 0, j = 0;
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            if (row != p && col != q)
            {
                temp[i][j++] = A[row][col];
                if (j == n - 1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
}
float Det(int a[][10], int n)
{
    float D = 0;
    if (n == 1)
        return a[0][0];

    int temp[10][10];

    int sign = 1;

    for (int f = 0; f < n; f++)
    {
        getCofactor(a, temp, 0, f, n);
        D += sign * a[0][f] * determinant(temp, n - 1);
        sign = -sign;
    }

    return D;
}
void adjoint(float A[][10], float adj[][10], int row)
{
    int sign = 1;
    float temp[10][10];

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < row; j++)
        {
            getCofactor(A, temp, i, j, row);
            sign = ((i + j) % 2 == 0) ? 1 : -1;
            adj[j][i] = (sign) * (Det(temp, row - 1));
        }
    }
}

void inverse(float A[][10], float inverse[][10], int row)
{
    float det = Det(A, row);
    if (det == 0)
    {
        printf("Inverse Does not exists!\n");
        return;
    }
    float adj[10][10];
    adjoint(A, adj, row);
    for (int i = 0; i < row; i++)
        for (int j = 0; j < row; j++)
            inverse[i][j] = adj[i][j] / det;
}

void EqSol()
{
    int unk;
    float A[10][10], B[10][10], in[10][10], sol[10][10];
    printf("Enter Number of Unknowns : ");
    scanf("%d", &unk);
    printf("Enter Coefficients in Matrix form \n");
    for (int i = 0; i < unk; i++)
    {
        printf("Enter Row %d : ", i + 1);
        for (int j = 0; j < unk; j++)
            scanf("%f", &A[i][j]);
    }
    printf("Enter Column Matrix corresponding to RHS\n");
    for (int i = 0; i < unk; i++)
    {
        printf("Enter Row %d : ", i + 1);
        scanf("%f", &B[i]);
    }
    inverse(A, in, unk);
    // display(in,unk,unk);
    product(in, B, sol, unk, unk, unk, 1);
    printf("The solution Matrix is :\n");
    display(sol, unk, 1);
}

int main()
{
    while (1)
    {
        int choice;
        printf("Enter 1 to find rank\nEnter 2 to find determinant\nEnter 3 to find product \nEnter 4 to find REF\nEnter 5 to find adjoint \nEnter 6 to inverse\nEnter 7 to solve equation\nEnter 0 to exit\nEnter your choice : ");
        scanf("%d", &choice);
        if (choice == 0)
        {
            break;
        }
        else if (choice == 1)
        {
            int row, col;
            printf("Enter the number of row : ");
            scanf("%d", &row);
            printf("Enter the number of column : ");
            scanf("%d", &col);
            float a[10][10];
            input(a, row, col);
            float ref[10][10];
            REF(a, ref, row, col);
            Rank(a, ref, row, col);
            printf("\n\n");
        }
        else if (choice == 2)
        {
            int row, col;
            printf("Enter the number of row : ");
            scanf("%d", &row);
            printf("Enter the number of column : ");
            scanf("%d", &col);
            float a[10][10];
            input(a, row, col);
            if (row != col)
            {
                printf("Determinant is not defined ! \n\n\n");
                continue;
            }
            printf("Determinant of given matrix is : %.2f\n", Det(a, row));
            printf("\n\n");
        }
        else if (choice == 3)
        {
            int row1, col1;
            printf("Enter the number of row of matrix-1: ");
            scanf("%d", &row1);
            printf("Enter the number of column of matrix-1: ");
            scanf("%d", &col1);
            float a[10][10];
            input(a, row1, col1);
            int row2, col2;
            printf("Enter the number of row of matrix-2: ");
            scanf("%d", &row2);
            printf("Enter the number of column of matrix-2: ");
            scanf("%d", &col2);
            float b[10][10];
            input(b, row2, col2);
            float pro[10][10];
            product(a, b, pro, row1, col1, row2, col2);
            printf("Product of given matrices is : \n");
            display(pro, row1, col2);
            printf("\n\n");
        }
        else if (choice == 4)
        {
            int row, col;
            printf("Enter the number of row : ");
            scanf("%d", &row);
            printf("Enter the number of column : ");
            scanf("%d", &col);
            float a[10][10];
            input(a, row, col);
            float ref[10][10];
            REF(a, ref, row, col);
            printf("REF of given matrices are:\n");
            display(ref, row, col);
            printf("\n\n");
        }
        else if (choice == 5)
        {
            int row, col;
            printf("Enter the number of row : ");
            scanf("%d", &row);
            printf("Enter the number of column : ");
            scanf("%d", &col);
            if (col != row)
            {
                printf("Adjoint does not exist!\n");
                continue;
            }
            float a[10][10];
            input(a, row, col);
            float adj[10][10];
            adjoint(a, adj, row);
            printf("Adjoint of the matrix is : \n");
            display(adj, row, row);
            printf("\n\n");
        }
        else if (choice == 6)
        {
            int row, col;
            printf("Enter the number of row : ");
            scanf("%d", &row);
            printf("Enter the number of column : ");
            scanf("%d", &col);
            float a[10][10];
            input(a, row, col);
            if (col != row || Det(a, row) == 0)
            {
                printf("Inverse does not exist\n\n\n");
                continue;
            }
            float inv[10][10];
            inverse(a, inv, row);
            printf("Inverse of given Matrix is : \n");
            display(inv, row, col);
            printf("\n\n");
        }
        else if (choice == 7)
        {
            EqSol();
            printf("\n\n");
        }
    }
    return 0;
}
