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
struct rtx_iv {scalar_t__ mult; scalar_t__ delta; int extend_mode; int mode; scalar_t__ step; void* base; int /*<<< orphan*/  extend; scalar_t__ first_special; } ;
struct niter_desc {int mode; int signed_p; } ;
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 scalar_t__ GET_MODE_BITSIZE (int) ; 
#define  LE 132 
#define  LEU 131 
#define  LT 130 
#define  LTU 129 
#define  NE 128 
 int /*<<< orphan*/  SIGN_EXTEND ; 
 int /*<<< orphan*/  UNKNOWN ; 
 int /*<<< orphan*/  ZERO_EXTEND ; 
 scalar_t__ const0_rtx ; 
 scalar_t__ const1_rtx ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  shorten_into_mode (struct rtx_iv*,int,int,int,struct niter_desc*) ; 
 void* simplify_gen_unary (int /*<<< orphan*/ ,int,void*,int) ; 
 int swap_condition (int) ; 

__attribute__((used)) static bool
canonicalize_iv_subregs (struct rtx_iv *iv0, struct rtx_iv *iv1,
			 enum rtx_code cond, struct niter_desc *desc)
{
  enum machine_mode comp_mode;
  bool signed_p;

  /* If the ivs behave specially in the first iteration, or are
     added/multiplied after extending, we ignore them.  */
  if (iv0->first_special || iv0->mult != const1_rtx || iv0->delta != const0_rtx)
    return false;
  if (iv1->first_special || iv1->mult != const1_rtx || iv1->delta != const0_rtx)
    return false;

  /* If there is some extend, it must match signedness of the comparison.  */
  switch (cond)
    {
      case LE:
      case LT:
	if (iv0->extend == ZERO_EXTEND
	    || iv1->extend == ZERO_EXTEND)
	  return false;
	signed_p = true;
	break;

      case LEU:
      case LTU:
	if (iv0->extend == SIGN_EXTEND
	    || iv1->extend == SIGN_EXTEND)
	  return false;
	signed_p = false;
	break;

      case NE:
	if (iv0->extend != UNKNOWN
	    && iv1->extend != UNKNOWN
	    && iv0->extend != iv1->extend)
	  return false;

	signed_p = false;
	if (iv0->extend != UNKNOWN)
	  signed_p = iv0->extend == SIGN_EXTEND;
	if (iv1->extend != UNKNOWN)
	  signed_p = iv1->extend == SIGN_EXTEND;
	break;

      default:
	gcc_unreachable ();
    }

  /* Values of both variables should be computed in the same mode.  These
     might indeed be different, if we have comparison like

     (compare (subreg:SI (iv0)) (subreg:SI (iv1)))

     and iv0 and iv1 are both ivs iterating in SI mode, but calculated
     in different modes.  This does not seem impossible to handle, but
     it hardly ever occurs in practice.
     
     The only exception is the case when one of operands is invariant.
     For example pentium 3 generates comparisons like
     (lt (subreg:HI (reg:SI)) 100).  Here we assign HImode to 100, but we
     definitely do not want this prevent the optimization.  */
  comp_mode = iv0->extend_mode;
  if (GET_MODE_BITSIZE (comp_mode) < GET_MODE_BITSIZE (iv1->extend_mode))
    comp_mode = iv1->extend_mode;

  if (iv0->extend_mode != comp_mode)
    {
      if (iv0->mode != iv0->extend_mode
	  || iv0->step != const0_rtx)
	return false;

      iv0->base = simplify_gen_unary (signed_p ? SIGN_EXTEND : ZERO_EXTEND,
				      comp_mode, iv0->base, iv0->mode);
      iv0->extend_mode = comp_mode;
    }

  if (iv1->extend_mode != comp_mode)
    {
      if (iv1->mode != iv1->extend_mode
	  || iv1->step != const0_rtx)
	return false;

      iv1->base = simplify_gen_unary (signed_p ? SIGN_EXTEND : ZERO_EXTEND,
				      comp_mode, iv1->base, iv1->mode);
      iv1->extend_mode = comp_mode;
    }

  /* Check that both ivs belong to a range of a single mode.  If one of the
     operands is an invariant, we may need to shorten it into the common
     mode.  */
  if (iv0->mode == iv0->extend_mode
      && iv0->step == const0_rtx
      && iv0->mode != iv1->mode)
    shorten_into_mode (iv0, iv1->mode, cond, signed_p, desc);

  if (iv1->mode == iv1->extend_mode
      && iv1->step == const0_rtx
      && iv0->mode != iv1->mode)
    shorten_into_mode (iv1, iv0->mode, swap_condition (cond), signed_p, desc);

  if (iv0->mode != iv1->mode)
    return false;

  desc->mode = iv0->mode;
  desc->signed_p = signed_p;

  return true;
}