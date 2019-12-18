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
#define  POLYNOMIAL_CHREC 128 
 int const TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ automatically_generated_chrec_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_polynomial_chrec (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree 
chrec_component_in_loop_num (tree chrec, 
			     unsigned loop_num,
			     bool right)
{
  tree component;

  if (automatically_generated_chrec_p (chrec))
    return chrec;
  
  switch (TREE_CODE (chrec))
    {
    case POLYNOMIAL_CHREC:
      if (CHREC_VARIABLE (chrec) == loop_num)
	{
	  if (right)
	    component = CHREC_RIGHT (chrec);
	  else
	    component = CHREC_LEFT (chrec);

	  if (TREE_CODE (CHREC_LEFT (chrec)) != POLYNOMIAL_CHREC
	      || CHREC_VARIABLE (CHREC_LEFT (chrec)) != CHREC_VARIABLE (chrec))
	    return component;
	  
	  else
	    return build_polynomial_chrec
	      (loop_num, 
	       chrec_component_in_loop_num (CHREC_LEFT (chrec), 
					    loop_num, 
					    right), 
	       component);
	}
      
      else if (CHREC_VARIABLE (chrec) < loop_num)
	/* There is no evolution part in this loop.  */
	return NULL_TREE;
      
      else
	return chrec_component_in_loop_num (CHREC_LEFT (chrec), 
					    loop_num, 
					    right);
      
     default:
      if (right)
	return NULL_TREE;
      else
	return chrec;
    }
}