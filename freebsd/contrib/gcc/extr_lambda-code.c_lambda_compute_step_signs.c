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
typedef  int /*<<< orphan*/  lambda_trans_matrix ;
typedef  int** lambda_matrix ;

/* Variables and functions */
 int** LTM_MATRIX (int /*<<< orphan*/ ) ; 
 int LTM_ROWSIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lambda_matrix_col_add (int**,int,int,int,int) ; 
 int /*<<< orphan*/  lambda_matrix_col_exchange (int**,int,int,int) ; 
 int /*<<< orphan*/  lambda_matrix_col_negate (int**,int,int) ; 
 int /*<<< orphan*/  lambda_matrix_copy (int**,int**,int,int) ; 
 int** lambda_matrix_new (int,int) ; 
 int /*<<< orphan*/  lambda_vector_copy (int*,int*,int) ; 
 int lambda_vector_first_nz (int*,int,int) ; 
 int lambda_vector_min_nz (int*,int,int) ; 
 int* lambda_vector_new (int) ; 

__attribute__((used)) static lambda_vector
lambda_compute_step_signs (lambda_trans_matrix trans, lambda_vector stepsigns)
{
  lambda_matrix matrix, H;
  int size;
  lambda_vector newsteps;
  int i, j, factor, minimum_column;
  int temp;

  matrix = LTM_MATRIX (trans);
  size = LTM_ROWSIZE (trans);
  H = lambda_matrix_new (size, size);

  newsteps = lambda_vector_new (size);
  lambda_vector_copy (stepsigns, newsteps, size);

  lambda_matrix_copy (matrix, H, size, size);

  for (j = 0; j < size; j++)
    {
      lambda_vector row;
      row = H[j];
      for (i = j; i < size; i++)
	if (row[i] < 0)
	  lambda_matrix_col_negate (H, size, i);
      while (lambda_vector_first_nz (row, size, j + 1) < size)
	{
	  minimum_column = lambda_vector_min_nz (row, size, j);
	  lambda_matrix_col_exchange (H, size, j, minimum_column);

	  temp = newsteps[j];
	  newsteps[j] = newsteps[minimum_column];
	  newsteps[minimum_column] = temp;

	  for (i = j + 1; i < size; i++)
	    {
	      factor = row[i] / row[j];
	      lambda_matrix_col_add (H, size, j, i, -1 * factor);
	    }
	}
    }
  return newsteps;
}