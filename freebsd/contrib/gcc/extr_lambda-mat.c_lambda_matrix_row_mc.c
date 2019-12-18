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
lambda_matrix_row_mc (lambda_matrix mat, int n, int r1, int const1)
{
  int i;

  for (i = 0; i < n; i++)
    mat[r1][i] *= const1;
}