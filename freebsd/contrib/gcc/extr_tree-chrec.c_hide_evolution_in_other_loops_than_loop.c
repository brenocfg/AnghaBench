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
#define  POLYNOMIAL_CHREC 128 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ automatically_generated_chrec_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_polynomial_chrec (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initial_condition (int /*<<< orphan*/ ) ; 

tree 
hide_evolution_in_other_loops_than_loop (tree chrec, 
					 unsigned loop_num)
{
  if (automatically_generated_chrec_p (chrec))
    return chrec;
  
  switch (TREE_CODE (chrec))
    {
    case POLYNOMIAL_CHREC:
      if (CHREC_VARIABLE (chrec) == loop_num)
	return build_polynomial_chrec 
	  (loop_num, 
	   hide_evolution_in_other_loops_than_loop (CHREC_LEFT (chrec), 
						    loop_num), 
	   CHREC_RIGHT (chrec));
      
      else if (CHREC_VARIABLE (chrec) < loop_num)
	/* There is no evolution in this loop.  */
	return initial_condition (chrec);
      
      else
	return hide_evolution_in_other_loops_than_loop (CHREC_LEFT (chrec), 
							loop_num);
      
    default:
      return chrec;
    }
}