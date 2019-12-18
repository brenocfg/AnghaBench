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
struct tree_niter_desc {void* assumptions; } ;
struct TYPE_4__ {int no_overflow; void* base; void* step; } ;
typedef  TYPE_1__ affine_iv ;

/* Variables and functions */
 int /*<<< orphan*/  FLOOR_MOD_EXPR ; 
 int /*<<< orphan*/  GE_EXPR ; 
 scalar_t__ INTEGER_CST ; 
 int /*<<< orphan*/  LE_EXPR ; 
 int /*<<< orphan*/  MINUS_EXPR ; 
 int /*<<< orphan*/  PLUS_EXPR ; 
 scalar_t__ TREE_CODE (void*) ; 
 void* TREE_TYPE (void*) ; 
 int /*<<< orphan*/  TRUTH_AND_EXPR ; 
 void* TYPE_MAX_VALUE (void*) ; 
 void* TYPE_MIN_VALUE (void*) ; 
 void* boolean_type_node ; 
 void* build_int_cst (void*,int) ; 
 void* fold_build2 (int /*<<< orphan*/ ,void*,void*,void*) ; 
 void* fold_convert (void*,void*) ; 
 scalar_t__ nonzero_p (void*) ; 
 scalar_t__ zero_p (void*) ; 

__attribute__((used)) static bool
assert_no_overflow_lt (tree type, affine_iv *iv0, affine_iv *iv1,
		       struct tree_niter_desc *niter, tree step)
{
  tree bound, d, assumption, diff;
  tree niter_type = TREE_TYPE (step);

  if (nonzero_p (iv0->step))
    {
      /* for (i = iv0->base; i < iv1->base; i += iv0->step) */
      if (iv0->no_overflow)
	return true;

      /* If iv0->base is a constant, we can determine the last value before
	 overflow precisely; otherwise we conservatively assume
	 MAX - STEP + 1.  */

      if (TREE_CODE (iv0->base) == INTEGER_CST)
	{
	  d = fold_build2 (MINUS_EXPR, niter_type,
			   fold_convert (niter_type, TYPE_MAX_VALUE (type)),
			   fold_convert (niter_type, iv0->base));
	  diff = fold_build2 (FLOOR_MOD_EXPR, niter_type, d, step);
	}
      else
	diff = fold_build2 (MINUS_EXPR, niter_type, step,
			    build_int_cst (niter_type, 1));
      bound = fold_build2 (MINUS_EXPR, type,
			   TYPE_MAX_VALUE (type), fold_convert (type, diff));
      assumption = fold_build2 (LE_EXPR, boolean_type_node,
				iv1->base, bound);
    }
  else
    {
      /* for (i = iv1->base; i > iv0->base; i += iv1->step) */
      if (iv1->no_overflow)
	return true;

      if (TREE_CODE (iv1->base) == INTEGER_CST)
	{
	  d = fold_build2 (MINUS_EXPR, niter_type,
			   fold_convert (niter_type, iv1->base),
			   fold_convert (niter_type, TYPE_MIN_VALUE (type)));
	  diff = fold_build2 (FLOOR_MOD_EXPR, niter_type, d, step);
	}
      else
	diff = fold_build2 (MINUS_EXPR, niter_type, step,
			    build_int_cst (niter_type, 1));
      bound = fold_build2 (PLUS_EXPR, type,
			   TYPE_MIN_VALUE (type), fold_convert (type, diff));
      assumption = fold_build2 (GE_EXPR, boolean_type_node,
				iv0->base, bound);
    }

  if (zero_p (assumption))
    return false;
  if (!nonzero_p (assumption))
    niter->assumptions = fold_build2 (TRUTH_AND_EXPR, boolean_type_node,
				      niter->assumptions, assumption);
    
  iv0->no_overflow = true;
  iv1->no_overflow = true;
  return true;
}