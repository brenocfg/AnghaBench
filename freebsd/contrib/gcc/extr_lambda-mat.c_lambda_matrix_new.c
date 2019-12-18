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
 int /*<<< orphan*/ * ggc_alloc (int) ; 
 int /*<<< orphan*/  lambda_vector_new (int) ; 

lambda_matrix
lambda_matrix_new (int m, int n)
{
  lambda_matrix mat;
  int i;

  mat = ggc_alloc (m * sizeof (lambda_vector));
  
  for (i = 0; i < m; i++)
    mat[i] = lambda_vector_new (n);

  return mat;
}