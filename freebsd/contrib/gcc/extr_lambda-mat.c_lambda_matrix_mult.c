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
typedef  int** lambda_matrix ;

/* Variables and functions */

void
lambda_matrix_mult (lambda_matrix mat1, lambda_matrix mat2,
		    lambda_matrix mat3, int m, int r, int n)
{

  int i, j, k;

  for (i = 0; i < m; i++)
    {
      for (j = 0; j < n; j++)
	{
	  mat3[i][j] = 0;
	  for (k = 0; k < r; k++)
	    mat3[i][j] += mat1[i][k] * mat2[k][j];
	}
    }
}