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
struct noce_if_info {scalar_t__ cond; scalar_t__ a; scalar_t__ b; int /*<<< orphan*/  insn_a; int /*<<< orphan*/  jump; int /*<<< orphan*/  x; int /*<<< orphan*/  b_unconditional; } ;
typedef  scalar_t__ rtx ;
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 scalar_t__ COSTS_N_INSNS (int) ; 
 int FALSE ; 
 int GE ; 
 int GET_CODE (scalar_t__) ; 
 int GET_MODE (scalar_t__) ; 
 int GT ; 
 int /*<<< orphan*/  INSN_LOCATOR (int /*<<< orphan*/ ) ; 
 int LE ; 
 int LT ; 
 scalar_t__ NULL_RTX ; 
 int /*<<< orphan*/  OPTAB_DIRECT ; 
 int /*<<< orphan*/  SET ; 
 int TRUE ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 int /*<<< orphan*/  and_optab ; 
 scalar_t__ const0_rtx ; 
 scalar_t__ constm1_rtx ; 
 int /*<<< orphan*/  emit_insn_before_setloc (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ emit_store_flag (int /*<<< orphan*/ ,int,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ end_ifcvt_sequence (struct noce_if_info*) ; 
 int /*<<< orphan*/  end_sequence () ; 
 scalar_t__ expand_binop (int,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_reg_rtx (int) ; 
 scalar_t__ no_new_pseudos ; 
 int /*<<< orphan*/  noce_emit_move_insn (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ rtx_cost (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ side_effects_p (scalar_t__) ; 
 int /*<<< orphan*/  start_sequence () ; 

__attribute__((used)) static int
noce_try_sign_mask (struct noce_if_info *if_info)
{
  rtx cond, t, m, c, seq;
  enum machine_mode mode;
  enum rtx_code code;

  if (no_new_pseudos)
    return FALSE;

  cond = if_info->cond;
  code = GET_CODE (cond);
  m = XEXP (cond, 0);
  c = XEXP (cond, 1);

  t = NULL_RTX;
  if (if_info->a == const0_rtx)
    {
      if ((code == LT && c == const0_rtx)
	  || (code == LE && c == constm1_rtx))
	t = if_info->b;
    }
  else if (if_info->b == const0_rtx)
    {
      if ((code == GE && c == const0_rtx)
	  || (code == GT && c == constm1_rtx))
	t = if_info->a;
    }

  if (! t || side_effects_p (t))
    return FALSE;

  /* We currently don't handle different modes.  */
  mode = GET_MODE (t);
  if (GET_MODE (m) != mode)
    return FALSE;

  /* This is only profitable if T is cheap, or T is unconditionally
     executed/evaluated in the original insn sequence.  */
  if (rtx_cost (t, SET) >= COSTS_N_INSNS (2)
      && (!if_info->b_unconditional
          || t != if_info->b))
    return FALSE;

  start_sequence ();
  /* Use emit_store_flag to generate "m < 0 ? -1 : 0" instead of expanding
     "(signed) m >> 31" directly.  This benefits targets with specialized
     insns to obtain the signmask, but still uses ashr_optab otherwise.  */
  m = emit_store_flag (gen_reg_rtx (mode), LT, m, const0_rtx, mode, 0, -1);
  t = m ? expand_binop (mode, and_optab, m, t, NULL_RTX, 0, OPTAB_DIRECT)
	: NULL_RTX;

  if (!t)
    {
      end_sequence ();
      return FALSE;
    }

  noce_emit_move_insn (if_info->x, t);

  seq = end_ifcvt_sequence (if_info);
  if (!seq)
    return FALSE;

  emit_insn_before_setloc (seq, if_info->jump, INSN_LOCATOR (if_info->insn_a));
  return TRUE;
}