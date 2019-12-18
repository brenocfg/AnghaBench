#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  lambda_vector ;
typedef  int /*<<< orphan*/  lambda_matrix ;

/* Variables and functions */
 int /*<<< orphan*/  lambda_matrix_add_mc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  lambda_matrix_get_column (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lambda_matrix_id (int /*<<< orphan*/ ,int) ; 
 int lambda_matrix_inverse (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lambda_matrix_mult (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  lambda_matrix_negate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  lambda_matrix_new (int,int) ; 
 int /*<<< orphan*/  lambda_matrix_transpose (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

void
lambda_matrix_project_to_null (lambda_matrix B, int rowsize,
			       int colsize, int k, lambda_vector x)
{
  lambda_matrix M1, M2, M3, I;
  int determinant;

  /* Compute c(I-B^T inv(B B^T) B) e sub k.  */

  /* M1 is the transpose of B.  */
  M1 = lambda_matrix_new (colsize, colsize);
  lambda_matrix_transpose (B, M1, rowsize, colsize);

  /* M2 = B * B^T */
  M2 = lambda_matrix_new (colsize, colsize);
  lambda_matrix_mult (B, M1, M2, rowsize, colsize, rowsize);

  /* M3 = inv(M2) */
  M3 = lambda_matrix_new (colsize, colsize);
  determinant = lambda_matrix_inverse (M2, M3, rowsize);

  /* M2 = B^T (inv(B B^T)) */
  lambda_matrix_mult (M1, M3, M2, colsize, rowsize, rowsize);

  /* M1 = B^T (inv(B B^T)) B */
  lambda_matrix_mult (M2, B, M1, colsize, rowsize, colsize);
  lambda_matrix_negate (M1, M1, colsize, colsize);

  I = lambda_matrix_new (colsize, colsize);
  lambda_matrix_id (I, colsize);

  lambda_matrix_add_mc (I, determinant, M1, 1, M2, colsize, colsize);

  lambda_matrix_get_column (M2, colsize, k - 1, x);

}