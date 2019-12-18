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
typedef  scalar_t__ rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
typedef  int HOST_WIDE_INT ;

/* Variables and functions */
 int BRANCH_COST ; 
 scalar_t__ COSTS_N_INSNS (int) ; 
 int /*<<< orphan*/  GE ; 
 scalar_t__ GEN_INT (int) ; 
 int GET_MODE_BITSIZE (int) ; 
 int /*<<< orphan*/  LT ; 
 int /*<<< orphan*/  NULL_RTX ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  OPTAB_LIB_WIDEN ; 
 int /*<<< orphan*/  RSHIFT_EXPR ; 
 int /*<<< orphan*/  add_optab ; 
 int /*<<< orphan*/  and_optab ; 
 int /*<<< orphan*/  build_int_cst (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  const0_rtx ; 
 scalar_t__ copy_to_mode_reg (int,scalar_t__) ; 
 int /*<<< orphan*/  do_cmp_and_jump (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  do_pending_stack_adjust () ; 
 scalar_t__ emit_conditional_move (scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_insn (scalar_t__) ; 
 int /*<<< orphan*/  emit_label (scalar_t__) ; 
 scalar_t__ emit_store_flag (scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  end_sequence () ; 
 scalar_t__ expand_binop (int,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expand_inc (scalar_t__,scalar_t__) ; 
 scalar_t__ expand_shift (int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int floor_log2 (int) ; 
 scalar_t__ force_reg (int,scalar_t__) ; 
 scalar_t__ gen_label_rtx () ; 
 scalar_t__ gen_reg_rtx (int) ; 
 scalar_t__ get_insns () ; 
 scalar_t__** shift_cost ; 
 int /*<<< orphan*/  start_sequence () ; 

__attribute__((used)) static rtx
expand_sdiv_pow2 (enum machine_mode mode, rtx op0, HOST_WIDE_INT d)
{
  rtx temp, label;
  tree shift;
  int logd;

  logd = floor_log2 (d);
  shift = build_int_cst (NULL_TREE, logd);

  if (d == 2 && BRANCH_COST >= 1)
    {
      temp = gen_reg_rtx (mode);
      temp = emit_store_flag (temp, LT, op0, const0_rtx, mode, 0, 1);
      temp = expand_binop (mode, add_optab, temp, op0, NULL_RTX,
			   0, OPTAB_LIB_WIDEN);
      return expand_shift (RSHIFT_EXPR, mode, temp, shift, NULL_RTX, 0);
    }

#ifdef HAVE_conditional_move
  if (BRANCH_COST >= 2)
    {
      rtx temp2;

      /* ??? emit_conditional_move forces a stack adjustment via
	 compare_from_rtx so, if the sequence is discarded, it will
	 be lost.  Do it now instead.  */
      do_pending_stack_adjust ();

      start_sequence ();
      temp2 = copy_to_mode_reg (mode, op0);
      temp = expand_binop (mode, add_optab, temp2, GEN_INT (d-1),
			   NULL_RTX, 0, OPTAB_LIB_WIDEN);
      temp = force_reg (mode, temp);

      /* Construct "temp2 = (temp2 < 0) ? temp : temp2".  */
      temp2 = emit_conditional_move (temp2, LT, temp2, const0_rtx,
				     mode, temp, temp2, mode, 0);
      if (temp2)
	{
	  rtx seq = get_insns ();
	  end_sequence ();
	  emit_insn (seq);
	  return expand_shift (RSHIFT_EXPR, mode, temp2, shift, NULL_RTX, 0);
	}
      end_sequence ();
    }
#endif

  if (BRANCH_COST >= 2)
    {
      int ushift = GET_MODE_BITSIZE (mode) - logd;

      temp = gen_reg_rtx (mode);
      temp = emit_store_flag (temp, LT, op0, const0_rtx, mode, 0, -1);
      if (shift_cost[mode][ushift] > COSTS_N_INSNS (1))
	temp = expand_binop (mode, and_optab, temp, GEN_INT (d - 1),
			     NULL_RTX, 0, OPTAB_LIB_WIDEN);
      else
	temp = expand_shift (RSHIFT_EXPR, mode, temp,
			     build_int_cst (NULL_TREE, ushift),
			     NULL_RTX, 1);
      temp = expand_binop (mode, add_optab, temp, op0, NULL_RTX,
			   0, OPTAB_LIB_WIDEN);
      return expand_shift (RSHIFT_EXPR, mode, temp, shift, NULL_RTX, 0);
    }

  label = gen_label_rtx ();
  temp = copy_to_mode_reg (mode, op0);
  do_cmp_and_jump (temp, const0_rtx, GE, mode, label);
  expand_inc (temp, GEN_INT (d - 1));
  emit_label (label);
  return expand_shift (RSHIFT_EXPR, mode, temp, shift, NULL_RTX, 0);
}