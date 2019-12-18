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
typedef  int /*<<< orphan*/ * lambda_vector ;
typedef  int /*<<< orphan*/ ** lambda_matrix ;

/* Variables and functions */

__attribute__((used)) static void
lambda_matrix_get_column (lambda_matrix mat, int n, int col,
			  lambda_vector vec)
{
  int i;

  for (i = 0; i < n; i++)
    vec[i] = mat[i][col];
}