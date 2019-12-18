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

/* Variables and functions */
 int /*<<< orphan*/  CHREC_LEFT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHREC_RIGHT (int /*<<< orphan*/ ) ; 
 unsigned int CHREC_VARIABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULL_TREE ; 
 scalar_t__ POLYNOMIAL_CHREC ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build3 (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_int_cst (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  build_polynomial_chrec (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ chrec_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 

tree 
reset_evolution_in_loop (unsigned loop_num,
			 tree chrec, 
			 tree new_evol)
{
  gcc_assert (chrec_type (chrec) == chrec_type (new_evol));

  if (TREE_CODE (chrec) == POLYNOMIAL_CHREC
      && CHREC_VARIABLE (chrec) > loop_num)
    {
      tree left = reset_evolution_in_loop (loop_num, CHREC_LEFT (chrec),
					   new_evol);
      tree right = reset_evolution_in_loop (loop_num, CHREC_RIGHT (chrec),
					    new_evol);
      return build3 (POLYNOMIAL_CHREC, TREE_TYPE (left),
		     build_int_cst (NULL_TREE, CHREC_VARIABLE (chrec)),
		     left, right);
    }

  while (TREE_CODE (chrec) == POLYNOMIAL_CHREC
	 && CHREC_VARIABLE (chrec) == loop_num)
    chrec = CHREC_LEFT (chrec);
  
  return build_polynomial_chrec (loop_num, chrec, new_evol);
}