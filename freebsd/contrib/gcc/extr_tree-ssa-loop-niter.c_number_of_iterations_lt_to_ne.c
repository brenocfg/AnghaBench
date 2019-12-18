#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* tree ;
struct tree_niter_desc {void* assumptions; void* may_be_zero; } ;
struct TYPE_4__ {void* step; void* base; int /*<<< orphan*/  no_overflow; } ;
typedef  TYPE_1__ affine_iv ;

/* Variables and functions */
 int /*<<< orphan*/  FLOOR_MOD_EXPR ; 
 int /*<<< orphan*/  GE_EXPR ; 
 int /*<<< orphan*/  GT_EXPR ; 
 scalar_t__ INTEGER_CST ; 
 int /*<<< orphan*/  LE_EXPR ; 
 int /*<<< orphan*/  MINUS_EXPR ; 
 int /*<<< orphan*/  PLUS_EXPR ; 
 scalar_t__ TREE_CODE (void*) ; 
 void* TREE_TYPE (void*) ; 
 int /*<<< orphan*/  TRUTH_AND_EXPR ; 
 int /*<<< orphan*/  TRUTH_OR_EXPR ; 
 void* TYPE_MAX_VALUE (void*) ; 
 void* TYPE_MIN_VALUE (void*) ; 
 void* boolean_true_node ; 
 void* boolean_type_node ; 
 void* fold_build2 (int /*<<< orphan*/ ,void*,void*,void*) ; 
 void* fold_convert (void*,void*) ; 
 scalar_t__ nonzero_p (void*) ; 
 scalar_t__ zero_p (void*) ; 

__attribute__((used)) static bool
number_of_iterations_lt_to_ne (tree type, affine_iv *iv0, affine_iv *iv1,
			       struct tree_niter_desc *niter,
			       tree *delta, tree step)
{
  tree niter_type = TREE_TYPE (step);
  tree mod = fold_build2 (FLOOR_MOD_EXPR, niter_type, *delta, step);
  tree tmod;
  tree assumption = boolean_true_node, bound, noloop;

  if (TREE_CODE (mod) != INTEGER_CST)
    return false;
  if (nonzero_p (mod))
    mod = fold_build2 (MINUS_EXPR, niter_type, step, mod);
  tmod = fold_convert (type, mod);

  if (nonzero_p (iv0->step))
    {
      /* The final value of the iv is iv1->base + MOD, assuming that this
	 computation does not overflow, and that
	 iv0->base <= iv1->base + MOD.  */
      if (!iv1->no_overflow && !zero_p (mod))
	{
	  bound = fold_build2 (MINUS_EXPR, type,
			       TYPE_MAX_VALUE (type), tmod);
	  assumption = fold_build2 (LE_EXPR, boolean_type_node,
				    iv1->base, bound);
	  if (zero_p (assumption))
	    return false;
	}
      noloop = fold_build2 (GT_EXPR, boolean_type_node,
			    iv0->base,
			    fold_build2 (PLUS_EXPR, type,
					 iv1->base, tmod));
    }
  else
    {
      /* The final value of the iv is iv0->base - MOD, assuming that this
	 computation does not overflow, and that
	 iv0->base - MOD <= iv1->base. */
      if (!iv0->no_overflow && !zero_p (mod))
	{
	  bound = fold_build2 (PLUS_EXPR, type,
			       TYPE_MIN_VALUE (type), tmod);
	  assumption = fold_build2 (GE_EXPR, boolean_type_node,
				    iv0->base, bound);
	  if (zero_p (assumption))
	    return false;
	}
      noloop = fold_build2 (GT_EXPR, boolean_type_node,
			    fold_build2 (MINUS_EXPR, type,
					 iv0->base, tmod),
			    iv1->base);
    }

  if (!nonzero_p (assumption))
    niter->assumptions = fold_build2 (TRUTH_AND_EXPR, boolean_type_node,
				      niter->assumptions,
				      assumption);
  if (!zero_p (noloop))
    niter->may_be_zero = fold_build2 (TRUTH_OR_EXPR, boolean_type_node,
				      niter->may_be_zero,
				      noloop);
  *delta = fold_build2 (PLUS_EXPR, niter_type, *delta, mod);
  return true;
}