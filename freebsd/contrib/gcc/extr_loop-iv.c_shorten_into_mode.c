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
struct rtx_iv {int mode; int /*<<< orphan*/  extend; int /*<<< orphan*/  base; int /*<<< orphan*/  extend_mode; } ;
struct niter_desc {void* infinite; void* noloop_assumptions; } ;
typedef  int /*<<< orphan*/  rtx ;
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
#define  GE 136 
#define  GEU 135 
#define  GT 134 
#define  GTU 133 
#define  LE 132 
#define  LEU 131 
#define  LT 130 
#define  LTU 129 
#define  NE 128 
 int /*<<< orphan*/  SIGN_EXTEND ; 
 int /*<<< orphan*/  SImode ; 
 int /*<<< orphan*/  ZERO_EXTEND ; 
 void* alloc_EXPR_LIST (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  const0_rtx ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  get_mode_bounds (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simplify_gen_relational (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
shorten_into_mode (struct rtx_iv *iv, enum machine_mode mode,
		   enum rtx_code cond, bool signed_p, struct niter_desc *desc)
{
  rtx mmin, mmax, cond_over, cond_under;

  get_mode_bounds (mode, signed_p, iv->extend_mode, &mmin, &mmax);
  cond_under = simplify_gen_relational (LT, SImode, iv->extend_mode,
					iv->base, mmin);
  cond_over = simplify_gen_relational (GT, SImode, iv->extend_mode,
				       iv->base, mmax);

  switch (cond)
    {
      case LE:
      case LT:
      case LEU:
      case LTU:
	if (cond_under != const0_rtx)
	  desc->infinite =
		  alloc_EXPR_LIST (0, cond_under, desc->infinite);
	if (cond_over != const0_rtx)
	  desc->noloop_assumptions =
		  alloc_EXPR_LIST (0, cond_over, desc->noloop_assumptions);
	break;

      case GE:
      case GT:
      case GEU:
      case GTU:
	if (cond_over != const0_rtx)
	  desc->infinite =
		  alloc_EXPR_LIST (0, cond_over, desc->infinite);
	if (cond_under != const0_rtx)
	  desc->noloop_assumptions =
		  alloc_EXPR_LIST (0, cond_under, desc->noloop_assumptions);
	break;

      case NE:
	if (cond_over != const0_rtx)
	  desc->infinite =
		  alloc_EXPR_LIST (0, cond_over, desc->infinite);
	if (cond_under != const0_rtx)
	  desc->infinite =
		  alloc_EXPR_LIST (0, cond_under, desc->infinite);
	break;

      default:
	gcc_unreachable ();
    }

  iv->mode = mode;
  iv->extend = signed_p ? SIGN_EXTEND : ZERO_EXTEND;
}