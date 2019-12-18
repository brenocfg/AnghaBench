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
typedef  int /*<<< orphan*/ * lambda_matrix ;

/* Variables and functions */
 int /*<<< orphan*/  lambda_vector_negate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
lambda_matrix_negate (lambda_matrix mat1, lambda_matrix mat2, int m, int n)
{
  int i;

  for (i = 0; i < m; i++)
    lambda_vector_negate (mat1[i], mat2[i], n);
}