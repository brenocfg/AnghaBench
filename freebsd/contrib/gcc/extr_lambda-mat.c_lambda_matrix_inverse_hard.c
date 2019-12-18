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
typedef  int* lambda_vector ;
typedef  int** lambda_matrix ;

/* Variables and functions */
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  lambda_matrix_col_add (int**,int,int,int,int) ; 
 int /*<<< orphan*/  lambda_matrix_col_exchange (int**,int,int,int) ; 
 int /*<<< orphan*/  lambda_matrix_col_mc (int**,int,int,int) ; 
 int /*<<< orphan*/  lambda_matrix_col_negate (int**,int,int) ; 
 int /*<<< orphan*/  lambda_matrix_copy (int**,int**,int,int) ; 
 int /*<<< orphan*/  lambda_matrix_id (int**,int) ; 
 int** lambda_matrix_new (int,int) ; 
 int lambda_vector_first_nz (int*,int,int) ; 
 int lambda_vector_min_nz (int*,int,int) ; 

__attribute__((used)) static int
lambda_matrix_inverse_hard (lambda_matrix mat, lambda_matrix inv, int n)
{
  lambda_vector row;
  lambda_matrix temp;
  int i, j;
  int determinant;

  temp = lambda_matrix_new (n, n);
  lambda_matrix_copy (mat, temp, n, n);
  lambda_matrix_id (inv, n);

  /* Reduce TEMP to a lower triangular form, applying the same operations on
     INV which starts as the identity matrix.  N is the number of rows and
     columns.  */
  for (j = 0; j < n; j++)
    {
      row = temp[j];

      /* Make every element in the current row positive.  */
      for (i = j; i < n; i++)
	if (row[i] < 0)
	  {
	    lambda_matrix_col_negate (temp, n, i);
	    lambda_matrix_col_negate (inv, n, i);
	  }

      /* Sweep the upper triangle.  Stop when only the diagonal element in the
	 current row is nonzero.  */
      while (lambda_vector_first_nz (row, n, j + 1) < n)
	{
	  int min_col = lambda_vector_min_nz (row, n, j);
	  lambda_matrix_col_exchange (temp, n, j, min_col);
	  lambda_matrix_col_exchange (inv, n, j, min_col);

	  for (i = j + 1; i < n; i++)
	    {
	      int factor;

	      factor = -1 * row[i];
	      if (row[j] != 1)
		factor /= row[j];

	      lambda_matrix_col_add (temp, n, j, i, factor);
	      lambda_matrix_col_add (inv, n, j, i, factor);
	    }
	}
    }

  /* Reduce TEMP from a lower triangular to the identity matrix.  Also compute
     the determinant, which now is simply the product of the elements on the
     diagonal of TEMP.  If one of these elements is 0, the matrix has 0 as an
     eigenvalue so it is singular and hence not invertible.  */
  determinant = 1;
  for (j = n - 1; j >= 0; j--)
    {
      int diagonal;

      row = temp[j];
      diagonal = row[j];

      /* The matrix must not be singular.  */
      gcc_assert (diagonal);

      determinant = determinant * diagonal;

      /* If the diagonal is not 1, then multiply the each row by the
         diagonal so that the middle number is now 1, rather than a
         rational.  */
      if (diagonal != 1)
	{
	  for (i = 0; i < j; i++)
	    lambda_matrix_col_mc (inv, n, i, diagonal);
	  for (i = j + 1; i < n; i++)
	    lambda_matrix_col_mc (inv, n, i, diagonal);

	  row[j] = diagonal = 1;
	}

      /* Sweep the lower triangle column wise.  */
      for (i = j - 1; i >= 0; i--)
	{
	  if (row[i])
	    {
	      int factor = -row[i];
	      lambda_matrix_col_add (temp, n, j, i, factor);
	      lambda_matrix_col_add (inv, n, j, i, factor);
	    }

	}
    }

  return determinant;
}