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
struct iv_to_split {scalar_t__ base_var; scalar_t__ step; } ;
typedef  scalar_t__ rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int GET_MODE (scalar_t__) ; 
 int /*<<< orphan*/  MULT ; 
 int /*<<< orphan*/  PLUS ; 
 int /*<<< orphan*/  SET_DEST (scalar_t__) ; 
 int /*<<< orphan*/  SET_SRC (scalar_t__) ; 
 scalar_t__ copy_rtx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delete_insn (scalar_t__) ; 
 int /*<<< orphan*/  emit_insn_before (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  emit_move_insn (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  end_sequence () ; 
 scalar_t__ force_operand (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gcc_assert (scalar_t__) ; 
 scalar_t__ gen_int_mode (unsigned int,int) ; 
 scalar_t__ gen_reg_rtx (int) ; 
 scalar_t__ get_insns () ; 
 scalar_t__* get_ivts_expr (scalar_t__,struct iv_to_split*) ; 
 scalar_t__ simplify_gen_binary (int /*<<< orphan*/ ,int,scalar_t__,scalar_t__) ; 
 scalar_t__ single_set (scalar_t__) ; 
 int /*<<< orphan*/  start_sequence () ; 
 scalar_t__ validate_change (scalar_t__,scalar_t__*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
split_iv (struct iv_to_split *ivts, rtx insn, unsigned delta)
{
  rtx expr, *loc, seq, incr, var;
  enum machine_mode mode = GET_MODE (ivts->base_var);
  rtx src, dest, set;

  /* Construct base + DELTA * step.  */
  if (!delta)
    expr = ivts->base_var;
  else
    {
      incr = simplify_gen_binary (MULT, mode,
				  ivts->step, gen_int_mode (delta, mode));
      expr = simplify_gen_binary (PLUS, GET_MODE (ivts->base_var),
				  ivts->base_var, incr);
    }

  /* Figure out where to do the replacement.  */
  loc = get_ivts_expr (single_set (insn), ivts);

  /* If we can make the replacement right away, we're done.  */
  if (validate_change (insn, loc, expr, 0))
    return;

  /* Otherwise, force EXPR into a register and try again.  */
  start_sequence ();
  var = gen_reg_rtx (mode);
  expr = force_operand (expr, var);
  if (expr != var)
    emit_move_insn (var, expr);
  seq = get_insns ();
  end_sequence ();
  emit_insn_before (seq, insn);
      
  if (validate_change (insn, loc, var, 0))
    return;

  /* The last chance.  Try recreating the assignment in insn
     completely from scratch.  */
  set = single_set (insn);
  gcc_assert (set);

  start_sequence ();
  *loc = var;
  src = copy_rtx (SET_SRC (set));
  dest = copy_rtx (SET_DEST (set));
  src = force_operand (src, dest);
  if (src != dest)
    emit_move_insn (dest, src);
  seq = get_insns ();
  end_sequence ();
     
  emit_insn_before (seq, insn);
  delete_insn (insn);
}