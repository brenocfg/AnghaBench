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
typedef  int /*<<< orphan*/ * lambda_matrix ;

/* Variables and functions */

void
lambda_matrix_row_exchange (lambda_matrix mat, int r1, int r2)
{
  lambda_vector row;

  row = mat[r1];
  mat[r1] = mat[r2];
  mat[r2] = row;
}