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
struct noce_if_info {void* x; void* cond_earliest; void* cond; int /*<<< orphan*/  insn_a; int /*<<< orphan*/  jump; int /*<<< orphan*/  b; int /*<<< orphan*/  a; } ;
typedef  void* rtx ;
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;

/* Variables and functions */
 int FALSE ; 
#define  GE 139 
 int GET_CODE (void*) ; 
 int /*<<< orphan*/  GET_MODE (void*) ; 
#define  GEU 138 
#define  GT 137 
#define  GTU 136 
 scalar_t__ HONOR_NANS (int /*<<< orphan*/ ) ; 
 scalar_t__ HONOR_SIGNED_ZEROS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSN_LOCATOR (int /*<<< orphan*/ ) ; 
#define  LE 135 
#define  LEU 134 
#define  LT 133 
#define  LTU 132 
 int /*<<< orphan*/  OPTAB_WIDEN ; 
 int SMAX ; 
 int SMIN ; 
 int TRUE ; 
 int UMAX ; 
 int UMIN ; 
#define  UNGE 131 
#define  UNGT 130 
#define  UNLE 129 
#define  UNLT 128 
 int /*<<< orphan*/  XEXP (void*,int) ; 
 int /*<<< orphan*/  emit_insn_before_setloc (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* end_ifcvt_sequence (struct noce_if_info*) ; 
 int /*<<< orphan*/  end_sequence () ; 
 void* expand_simple_binop (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ no_new_pseudos ; 
 int /*<<< orphan*/  noce_emit_move_insn (void*,void*) ; 
 void* noce_get_alt_condition (struct noce_if_info*,int /*<<< orphan*/ ,void**) ; 
 scalar_t__ rtx_equal_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_sequence () ; 
 int swap_condition (int) ; 

__attribute__((used)) static int
noce_try_minmax (struct noce_if_info *if_info)
{
  rtx cond, earliest, target, seq;
  enum rtx_code code, op;
  int unsignedp;

  /* ??? Can't guarantee that expand_binop won't create pseudos.  */
  if (no_new_pseudos)
    return FALSE;

  /* ??? Reject modes with NaNs or signed zeros since we don't know how
     they will be resolved with an SMIN/SMAX.  It wouldn't be too hard
     to get the target to tell us...  */
  if (HONOR_SIGNED_ZEROS (GET_MODE (if_info->x))
      || HONOR_NANS (GET_MODE (if_info->x)))
    return FALSE;

  cond = noce_get_alt_condition (if_info, if_info->a, &earliest);
  if (!cond)
    return FALSE;

  /* Verify the condition is of the form we expect, and canonicalize
     the comparison code.  */
  code = GET_CODE (cond);
  if (rtx_equal_p (XEXP (cond, 0), if_info->a))
    {
      if (! rtx_equal_p (XEXP (cond, 1), if_info->b))
	return FALSE;
    }
  else if (rtx_equal_p (XEXP (cond, 1), if_info->a))
    {
      if (! rtx_equal_p (XEXP (cond, 0), if_info->b))
	return FALSE;
      code = swap_condition (code);
    }
  else
    return FALSE;

  /* Determine what sort of operation this is.  Note that the code is for
     a taken branch, so the code->operation mapping appears backwards.  */
  switch (code)
    {
    case LT:
    case LE:
    case UNLT:
    case UNLE:
      op = SMAX;
      unsignedp = 0;
      break;
    case GT:
    case GE:
    case UNGT:
    case UNGE:
      op = SMIN;
      unsignedp = 0;
      break;
    case LTU:
    case LEU:
      op = UMAX;
      unsignedp = 1;
      break;
    case GTU:
    case GEU:
      op = UMIN;
      unsignedp = 1;
      break;
    default:
      return FALSE;
    }

  start_sequence ();

  target = expand_simple_binop (GET_MODE (if_info->x), op,
				if_info->a, if_info->b,
				if_info->x, unsignedp, OPTAB_WIDEN);
  if (! target)
    {
      end_sequence ();
      return FALSE;
    }
  if (target != if_info->x)
    noce_emit_move_insn (if_info->x, target);

  seq = end_ifcvt_sequence (if_info);
  if (!seq)
    return FALSE;

  emit_insn_before_setloc (seq, if_info->jump, INSN_LOCATOR (if_info->insn_a));
  if_info->cond = cond;
  if_info->cond_earliest = earliest;

  return TRUE;
}