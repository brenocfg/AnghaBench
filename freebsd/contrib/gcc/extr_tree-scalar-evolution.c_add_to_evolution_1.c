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
 int /*<<< orphan*/  SCALAR_FLOAT_TYPE_P (int /*<<< orphan*/ ) ; 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_int_cst (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_polynomial_chrec (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_real (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chrec_convert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chrec_dont_know ; 
 int /*<<< orphan*/  chrec_fold_plus (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chrec_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dconst0 ; 

__attribute__((used)) static tree
add_to_evolution_1 (unsigned loop_nb, tree chrec_before, tree to_add,
		    tree at_stmt)
{
  tree type, left, right;

  switch (TREE_CODE (chrec_before))
    {
    case POLYNOMIAL_CHREC:
      if (CHREC_VARIABLE (chrec_before) <= loop_nb)
	{
	  unsigned var;

	  type = chrec_type (chrec_before);
	  
	  /* When there is no evolution part in this loop, build it.  */
	  if (CHREC_VARIABLE (chrec_before) < loop_nb)
	    {
	      var = loop_nb;
	      left = chrec_before;
	      right = SCALAR_FLOAT_TYPE_P (type)
		? build_real (type, dconst0)
		: build_int_cst (type, 0);
	    }
	  else
	    {
	      var = CHREC_VARIABLE (chrec_before);
	      left = CHREC_LEFT (chrec_before);
	      right = CHREC_RIGHT (chrec_before);
	    }

	  to_add = chrec_convert (type, to_add, at_stmt);
	  right = chrec_convert (type, right, at_stmt);
	  right = chrec_fold_plus (type, right, to_add);
	  return build_polynomial_chrec (var, left, right);
	}
      else
	{
	  /* Search the evolution in LOOP_NB.  */
	  left = add_to_evolution_1 (loop_nb, CHREC_LEFT (chrec_before),
				     to_add, at_stmt);
	  right = CHREC_RIGHT (chrec_before);
	  right = chrec_convert (chrec_type (left), right, at_stmt);
	  return build_polynomial_chrec (CHREC_VARIABLE (chrec_before),
					 left, right);
	}
      
    default:
      /* These nodes do not depend on a loop.  */
      if (chrec_before == chrec_dont_know)
	return chrec_dont_know;

      left = chrec_before;
      right = chrec_convert (chrec_type (left), to_add, at_stmt);
      return build_polynomial_chrec (loop_nb, left, right);
    }
}