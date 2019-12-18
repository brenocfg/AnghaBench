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
#define  POLYNOMIAL_CHREC 128 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evolution_function_is_constant_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_fold_divides_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
chrec_steps_divide_constant_p (tree chrec, 
			       tree cst, 
			       bool *res)
{
  switch (TREE_CODE (chrec))
    {
    case POLYNOMIAL_CHREC:
      if (evolution_function_is_constant_p (CHREC_RIGHT (chrec)))
	{
	  if (tree_fold_divides_p (CHREC_RIGHT (chrec), cst))
	    /* Keep RES to true, and iterate on other dimensions.  */
	    return chrec_steps_divide_constant_p (CHREC_LEFT (chrec), cst, res);
	  
	  *res = false;
	  return true;
	}
      else
	/* When the step is a parameter the result is undetermined.  */
	return false;

    default:
      /* On the initial condition, return true.  */
      return true;
    }
}