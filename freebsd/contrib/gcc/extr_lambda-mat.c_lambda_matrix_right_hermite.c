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
typedef  scalar_t__** lambda_matrix ;

/* Variables and functions */
 int abs (int) ; 
 int /*<<< orphan*/  lambda_matrix_copy (scalar_t__**,scalar_t__**,int,int) ; 
 int /*<<< orphan*/  lambda_matrix_id (scalar_t__**,int) ; 
 int /*<<< orphan*/  lambda_matrix_row_add (scalar_t__**,int,int,int,int) ; 
 int /*<<< orphan*/  lambda_matrix_row_exchange (scalar_t__**,int,int) ; 
 int lambda_vector_first_nz (scalar_t__*,int,int) ; 

void
lambda_matrix_right_hermite (lambda_matrix A, int m, int n,
			     lambda_matrix S, lambda_matrix U)
{
  int i, j, i0 = 0;

  lambda_matrix_copy (A, S, m, n);
  lambda_matrix_id (U, m);

  for (j = 0; j < n; j++)
    {
      if (lambda_vector_first_nz (S[j], m, i0) < m)
	{
	  ++i0;
	  for (i = m - 1; i >= i0; i--)
	    {
	      while (S[i][j] != 0)
		{
		  int sigma, factor, a, b;

		  a = S[i-1][j];
		  b = S[i][j];
		  sigma = (a * b < 0) ? -1: 1;
		  a = abs (a);
		  b = abs (b);
		  factor = sigma * (a / b);

		  lambda_matrix_row_add (S, n, i, i-1, -factor);
		  lambda_matrix_row_exchange (S, i, i-1);

		  lambda_matrix_row_add (U, m, i, i-1, -factor);
		  lambda_matrix_row_exchange (U, i, i-1);
		}
	    }
	}
    }
}