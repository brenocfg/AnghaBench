#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* tree ;
struct TYPE_3__ {void* step; void* base; } ;
struct tree_niter_desc {void* assumptions; void* niter; int /*<<< orphan*/  cmp; void* bound; TYPE_1__ control; } ;
typedef  TYPE_1__ affine_iv ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_AND_EXPR ; 
 int /*<<< orphan*/  EQ_EXPR ; 
 int /*<<< orphan*/  EXACT_DIV_EXPR ; 
 int /*<<< orphan*/  FLOOR_MOD_EXPR ; 
 int /*<<< orphan*/  LSHIFT_EXPR ; 
 int /*<<< orphan*/  MINUS_EXPR ; 
 int /*<<< orphan*/  MULT_EXPR ; 
 int /*<<< orphan*/  NEGATE_EXPR ; 
 int /*<<< orphan*/  NE_EXPR ; 
 int /*<<< orphan*/  RSHIFT_EXPR ; 
 int /*<<< orphan*/  TRUTH_AND_EXPR ; 
 scalar_t__ TYPE_PRECISION (void*) ; 
 void* boolean_type_node ; 
 void* build_int_cst (void*,int) ; 
 void* build_low_bits_mask (void*,scalar_t__) ; 
 void* fold_binary_to_constant (int /*<<< orphan*/ ,void*,void*,void*) ; 
 void* fold_build1 (int /*<<< orphan*/ ,void*,void*) ; 
 void* fold_build2 (int /*<<< orphan*/ ,void*,void*,void*) ; 
 void* fold_convert (void*,void*) ; 
 scalar_t__ integer_onep (void*) ; 
 void* inverse (void*,void*) ; 
 int /*<<< orphan*/  nonzero_p (void*) ; 
 void* num_ending_zeros (void*) ; 
 scalar_t__ tree_int_cst_sign_bit (void*) ; 
 scalar_t__ tree_low_cst (void*,int) ; 
 void* unsigned_type_for (void*) ; 

__attribute__((used)) static bool
number_of_iterations_ne (tree type, affine_iv *iv, tree final,
			 struct tree_niter_desc *niter, bool never_infinite)
{
  tree niter_type = unsigned_type_for (type);
  tree s, c, d, bits, assumption, tmp, bound;

  niter->control = *iv;
  niter->bound = final;
  niter->cmp = NE_EXPR;

  /* Rearrange the terms so that we get inequality s * i <> c, with s
     positive.  Also cast everything to the unsigned type.  */
  if (tree_int_cst_sign_bit (iv->step))
    {
      s = fold_convert (niter_type,
			fold_build1 (NEGATE_EXPR, type, iv->step));
      c = fold_build2 (MINUS_EXPR, niter_type,
		       fold_convert (niter_type, iv->base),
		       fold_convert (niter_type, final));
    }
  else
    {
      s = fold_convert (niter_type, iv->step);
      c = fold_build2 (MINUS_EXPR, niter_type,
		       fold_convert (niter_type, final),
		       fold_convert (niter_type, iv->base));
    }

  /* First the trivial cases -- when the step is 1.  */
  if (integer_onep (s))
    {
      niter->niter = c;
      return true;
    }

  /* Let nsd (step, size of mode) = d.  If d does not divide c, the loop
     is infinite.  Otherwise, the number of iterations is
     (inverse(s/d) * (c/d)) mod (size of mode/d).  */
  bits = num_ending_zeros (s);
  bound = build_low_bits_mask (niter_type,
			       (TYPE_PRECISION (niter_type)
				- tree_low_cst (bits, 1)));

  d = fold_binary_to_constant (LSHIFT_EXPR, niter_type,
			       build_int_cst (niter_type, 1), bits);
  s = fold_binary_to_constant (RSHIFT_EXPR, niter_type, s, bits);

  if (!never_infinite)
    {
      /* If we cannot assume that the loop is not infinite, record the
	 assumptions for divisibility of c.  */
      assumption = fold_build2 (FLOOR_MOD_EXPR, niter_type, c, d);
      assumption = fold_build2 (EQ_EXPR, boolean_type_node,
				assumption, build_int_cst (niter_type, 0));
      if (!nonzero_p (assumption))
	niter->assumptions = fold_build2 (TRUTH_AND_EXPR, boolean_type_node,
					  niter->assumptions, assumption);
    }
      
  c = fold_build2 (EXACT_DIV_EXPR, niter_type, c, d);
  tmp = fold_build2 (MULT_EXPR, niter_type, c, inverse (s, bound));
  niter->niter = fold_build2 (BIT_AND_EXPR, niter_type, tmp, bound);
  return true;
}