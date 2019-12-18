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
typedef  int /*<<< orphan*/ * rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
typedef  int HOST_WIDE_INT ;

/* Variables and functions */
 int BITS_PER_WORD ; 
 int BLKmode ; 
 scalar_t__ CONST_DOUBLE ; 
 int /*<<< orphan*/  EQ ; 
 scalar_t__ FLOAT_WORDS_BIG_ENDIAN ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ *) ; 
 int GET_MODE_BITSIZE (int) ; 
 scalar_t__ GET_MODE_SIZE (int) ; 
 int HOST_BITS_PER_WIDE_INT ; 
 int /*<<< orphan*/  NEG ; 
 int /*<<< orphan*/ * NULL_RTX ; 
 int /*<<< orphan*/  OPTAB_LIB_WIDEN ; 
 scalar_t__ UNITS_PER_WORD ; 
 int /*<<< orphan*/  abs_optab ; 
 int /*<<< orphan*/  and_optab ; 
 int /*<<< orphan*/  const0_rtx ; 
 int /*<<< orphan*/ * copy_to_reg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emit_cmp_and_jump_insns (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emit_label (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * expand_binop (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * expand_unop (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gen_label_rtx () ; 
 int /*<<< orphan*/ * gen_lowpart (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  immed_double_const (int,int,int) ; 
 int int_mode_for_mode (int) ; 
 int /*<<< orphan*/  neg_optab ; 
 int /*<<< orphan*/ * operand_subword_force (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * simplify_unary_operation (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int word_mode ; 

__attribute__((used)) static rtx
expand_copysign_absneg (enum machine_mode mode, rtx op0, rtx op1, rtx target,
		        int bitpos, bool op0_is_abs)
{
  enum machine_mode imode;
  HOST_WIDE_INT hi, lo;
  int word;
  rtx label;

  if (target == op1)
    target = NULL_RTX;

  if (!op0_is_abs)
    {
      op0 = expand_unop (mode, abs_optab, op0, target, 0);
      if (op0 == NULL)
	return NULL_RTX;
      target = op0;
    }
  else
    {
      if (target == NULL_RTX)
        target = copy_to_reg (op0);
      else
	emit_move_insn (target, op0);
    }

  if (GET_MODE_SIZE (mode) <= UNITS_PER_WORD)
    {
      imode = int_mode_for_mode (mode);
      if (imode == BLKmode)
	return NULL_RTX;
      op1 = gen_lowpart (imode, op1);
    }
  else
    {
      imode = word_mode;
      if (FLOAT_WORDS_BIG_ENDIAN)
	word = (GET_MODE_BITSIZE (mode) - bitpos) / BITS_PER_WORD;
      else
	word = bitpos / BITS_PER_WORD;
      bitpos = bitpos % BITS_PER_WORD;
      op1 = operand_subword_force (op1, word, mode);
    }

  if (bitpos < HOST_BITS_PER_WIDE_INT)
    {
      hi = 0;
      lo = (HOST_WIDE_INT) 1 << bitpos;
    }
  else
    {
      hi = (HOST_WIDE_INT) 1 << (bitpos - HOST_BITS_PER_WIDE_INT);
      lo = 0;
    }

  op1 = expand_binop (imode, and_optab, op1,
		      immed_double_const (lo, hi, imode),
		      NULL_RTX, 1, OPTAB_LIB_WIDEN);

  label = gen_label_rtx ();
  emit_cmp_and_jump_insns (op1, const0_rtx, EQ, NULL_RTX, imode, 1, label);

  if (GET_CODE (op0) == CONST_DOUBLE)
    op0 = simplify_unary_operation (NEG, mode, op0, mode);
  else
    op0 = expand_unop (mode, neg_optab, op0, target, 0);
  if (op0 != target)
    emit_move_insn (target, op0);

  emit_label (label);

  return target;
}