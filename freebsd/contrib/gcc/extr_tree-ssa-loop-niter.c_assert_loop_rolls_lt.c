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
struct tree_niter_desc {void* may_be_zero; void* assumptions; } ;
struct TYPE_4__ {void* base; void* step; } ;
typedef  TYPE_1__ affine_iv ;

/* Variables and functions */
 int /*<<< orphan*/  GE_EXPR ; 
 int /*<<< orphan*/  GT_EXPR ; 
 int /*<<< orphan*/  LE_EXPR ; 
 int /*<<< orphan*/  MINUS_EXPR ; 
 int /*<<< orphan*/  PLUS_EXPR ; 
 int /*<<< orphan*/  POINTER_TYPE_P (void*) ; 
 int /*<<< orphan*/  TRUTH_AND_EXPR ; 
 int /*<<< orphan*/  TRUTH_OR_EXPR ; 
 void* TYPE_MAX_VALUE (void*) ; 
 void* TYPE_MIN_VALUE (void*) ; 
 void* boolean_true_node ; 
 void* boolean_type_node ; 
 void* build_int_cst (void*,int) ; 
 void* fold_build2 (int /*<<< orphan*/ ,void*,void*,void*) ; 
 scalar_t__ nonzero_p (void*) ; 
 int /*<<< orphan*/  zero_p (void*) ; 

__attribute__((used)) static void
assert_loop_rolls_lt (tree type, affine_iv *iv0, affine_iv *iv1,
		      struct tree_niter_desc *niter)
{
  tree assumption = boolean_true_node, bound, diff;
  tree mbz, mbzl, mbzr;

  if (nonzero_p (iv0->step))
    {
      diff = fold_build2 (MINUS_EXPR, type,
			  iv0->step, build_int_cst (type, 1));

      /* We need to know that iv0->base >= MIN + iv0->step - 1.  Since
	 0 address never belongs to any object, we can assume this for
	 pointers.  */
      if (!POINTER_TYPE_P (type))
	{
	  bound = fold_build2 (PLUS_EXPR, type,
			       TYPE_MIN_VALUE (type), diff);
	  assumption = fold_build2 (GE_EXPR, boolean_type_node,
				    iv0->base, bound);
	}

      /* And then we can compute iv0->base - diff, and compare it with
	 iv1->base.  */      
      mbzl = fold_build2 (MINUS_EXPR, type, iv0->base, diff);
      mbzr = iv1->base;
    }
  else
    {
      diff = fold_build2 (PLUS_EXPR, type,
			  iv1->step, build_int_cst (type, 1));

      if (!POINTER_TYPE_P (type))
	{
	  bound = fold_build2 (PLUS_EXPR, type,
			       TYPE_MAX_VALUE (type), diff);
	  assumption = fold_build2 (LE_EXPR, boolean_type_node,
				    iv1->base, bound);
	}

      mbzl = iv0->base;
      mbzr = fold_build2 (MINUS_EXPR, type, iv1->base, diff);
    }

  mbz = fold_build2 (GT_EXPR, boolean_type_node, mbzl, mbzr);

  if (!nonzero_p (assumption))
    niter->assumptions = fold_build2 (TRUTH_AND_EXPR, boolean_type_node,
				      niter->assumptions, assumption);
  if (!zero_p (mbz))
    niter->may_be_zero = fold_build2 (TRUTH_OR_EXPR, boolean_type_node,
				      niter->may_be_zero, mbz);
}