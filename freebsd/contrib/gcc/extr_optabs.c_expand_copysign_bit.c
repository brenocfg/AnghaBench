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
typedef  scalar_t__ rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
typedef  int HOST_WIDE_INT ;

/* Variables and functions */
 int BITS_PER_WORD ; 
 int BLKmode ; 
 scalar_t__ FLOAT_WORDS_BIG_ENDIAN ; 
 int GET_MODE_BITSIZE (int) ; 
 scalar_t__ GET_MODE_SIZE (int) ; 
 int HOST_BITS_PER_WIDE_INT ; 
 scalar_t__ NULL_RTX ; 
 int /*<<< orphan*/  OPTAB_LIB_WIDEN ; 
 scalar_t__ UNITS_PER_WORD ; 
 int /*<<< orphan*/  and_optab ; 
 int /*<<< orphan*/  emit_move_insn (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  emit_no_conflict_block (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  end_sequence () ; 
 scalar_t__ expand_binop (int,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ gen_lowpart (int,scalar_t__) ; 
 scalar_t__ gen_reg_rtx (int) ; 
 scalar_t__ get_insns () ; 
 scalar_t__ immed_double_const (int,int,int) ; 
 int int_mode_for_mode (int) ; 
 int /*<<< orphan*/  ior_optab ; 
 scalar_t__ lowpart_subreg_maybe_copy (int,scalar_t__,int) ; 
 scalar_t__ operand_subword (scalar_t__,int,int,int) ; 
 scalar_t__ operand_subword_force (scalar_t__,int,int) ; 
 int /*<<< orphan*/  start_sequence () ; 
 int word_mode ; 

__attribute__((used)) static rtx
expand_copysign_bit (enum machine_mode mode, rtx op0, rtx op1, rtx target,
		     int bitpos, bool op0_is_abs)
{
  enum machine_mode imode;
  HOST_WIDE_INT hi, lo;
  int word, nwords, i;
  rtx temp, insns;

  if (GET_MODE_SIZE (mode) <= UNITS_PER_WORD)
    {
      imode = int_mode_for_mode (mode);
      if (imode == BLKmode)
	return NULL_RTX;
      word = 0;
      nwords = 1;
    }
  else
    {
      imode = word_mode;

      if (FLOAT_WORDS_BIG_ENDIAN)
	word = (GET_MODE_BITSIZE (mode) - bitpos) / BITS_PER_WORD;
      else
	word = bitpos / BITS_PER_WORD;
      bitpos = bitpos % BITS_PER_WORD;
      nwords = (GET_MODE_BITSIZE (mode) + BITS_PER_WORD - 1) / BITS_PER_WORD;
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

  if (target == 0 || target == op0 || target == op1)
    target = gen_reg_rtx (mode);

  if (nwords > 1)
    {
      start_sequence ();

      for (i = 0; i < nwords; ++i)
	{
	  rtx targ_piece = operand_subword (target, i, 1, mode);
	  rtx op0_piece = operand_subword_force (op0, i, mode);

	  if (i == word)
	    {
	      if (!op0_is_abs)
		op0_piece = expand_binop (imode, and_optab, op0_piece,
					  immed_double_const (~lo, ~hi, imode),
					  NULL_RTX, 1, OPTAB_LIB_WIDEN);

	      op1 = expand_binop (imode, and_optab,
				  operand_subword_force (op1, i, mode),
				  immed_double_const (lo, hi, imode),
				  NULL_RTX, 1, OPTAB_LIB_WIDEN);

	      temp = expand_binop (imode, ior_optab, op0_piece, op1,
				   targ_piece, 1, OPTAB_LIB_WIDEN);
	      if (temp != targ_piece)
		emit_move_insn (targ_piece, temp);
	    }
	  else
	    emit_move_insn (targ_piece, op0_piece);
	}

      insns = get_insns ();
      end_sequence ();

      emit_no_conflict_block (insns, target, op0, op1, NULL_RTX);
    }
  else
    {
      op1 = expand_binop (imode, and_optab, gen_lowpart (imode, op1),
		          immed_double_const (lo, hi, imode),
		          NULL_RTX, 1, OPTAB_LIB_WIDEN);

      op0 = gen_lowpart (imode, op0);
      if (!op0_is_abs)
	op0 = expand_binop (imode, and_optab, op0,
			    immed_double_const (~lo, ~hi, imode),
			    NULL_RTX, 1, OPTAB_LIB_WIDEN);

      temp = expand_binop (imode, ior_optab, op0, op1,
			   gen_lowpart (imode, target), 1, OPTAB_LIB_WIDEN);
      target = lowpart_subreg_maybe_copy (mode, temp, imode);
    }

  return target;
}