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
typedef  int /*<<< orphan*/  tree ;
typedef  int** lambda_matrix ;

/* Variables and functions */
 int /*<<< orphan*/  CHREC_LEFT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHREC_RIGHT (int /*<<< orphan*/ ) ; 
 scalar_t__ POLYNOMIAL_CHREC ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 int int_cst_value (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
initialize_matrix_A (lambda_matrix A, tree chrec, unsigned index, int mult)
{
  gcc_assert (chrec);

  if (TREE_CODE (chrec) != POLYNOMIAL_CHREC)
    return int_cst_value (chrec);

  A[index][0] = mult * int_cst_value (CHREC_RIGHT (chrec));
  return initialize_matrix_A (A, CHREC_LEFT (chrec), index + 1, mult);
}