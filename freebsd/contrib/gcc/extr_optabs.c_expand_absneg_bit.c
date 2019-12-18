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
struct real_format {int signbit_rw; int /*<<< orphan*/  has_signed_zero; } ;
typedef  scalar_t__ rtx ;
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
typedef  int HOST_WIDE_INT ;

/* Variables and functions */
 int ABS ; 
 int BITS_PER_WORD ; 
 int BLKmode ; 
 scalar_t__ FLOAT_WORDS_BIG_ENDIAN ; 
 int GET_MODE_BITSIZE (int) ; 
 scalar_t__ GET_MODE_SIZE (int) ; 
 int HOST_BITS_PER_WIDE_INT ; 
 int NEG ; 
 scalar_t__ NULL_RTX ; 
 int /*<<< orphan*/  OPTAB_LIB_WIDEN ; 
 struct real_format* REAL_MODE_FORMAT (int) ; 
 int /*<<< orphan*/  REG_EQUAL ; 
 scalar_t__ UNITS_PER_WORD ; 
 int /*<<< orphan*/  and_optab ; 
 int /*<<< orphan*/  copy_rtx (scalar_t__) ; 
 int /*<<< orphan*/  emit_move_insn (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  emit_no_conflict_block (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  end_sequence () ; 
 scalar_t__ expand_binop (int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ gen_lowpart (int,scalar_t__) ; 
 scalar_t__ gen_reg_rtx (int) ; 
 scalar_t__ gen_rtx_fmt_e (int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ get_insns () ; 
 int /*<<< orphan*/  get_last_insn () ; 
 int /*<<< orphan*/  immed_double_const (int,int,int) ; 
 int int_mode_for_mode (int) ; 
 scalar_t__ lowpart_subreg_maybe_copy (int,scalar_t__,int) ; 
 scalar_t__ operand_subword (scalar_t__,int,int,int) ; 
 scalar_t__ operand_subword_force (scalar_t__,int,int) ; 
 int /*<<< orphan*/  set_unique_reg_note (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  start_sequence () ; 
 int word_mode ; 
 int /*<<< orphan*/  xor_optab ; 

__attribute__((used)) static rtx
expand_absneg_bit (enum rtx_code code, enum machine_mode mode,
		   rtx op0, rtx target)
{
  const struct real_format *fmt;
  int bitpos, word, nwords, i;
  enum machine_mode imode;
  HOST_WIDE_INT hi, lo;
  rtx temp, insns;

  /* The format has to have a simple sign bit.  */
  fmt = REAL_MODE_FORMAT (mode);
  if (fmt == NULL)
    return NULL_RTX;

  bitpos = fmt->signbit_rw;
  if (bitpos < 0)
    return NULL_RTX;

  /* Don't create negative zeros if the format doesn't support them.  */
  if (code == NEG && !fmt->has_signed_zero)
    return NULL_RTX;

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
  if (code == ABS)
    lo = ~lo, hi = ~hi;

  if (target == 0 || target == op0)
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
	      temp = expand_binop (imode, code == ABS ? and_optab : xor_optab,
				   op0_piece,
				   immed_double_const (lo, hi, imode),
				   targ_piece, 1, OPTAB_LIB_WIDEN);
	      if (temp != targ_piece)
		emit_move_insn (targ_piece, temp);
	    }
	  else
	    emit_move_insn (targ_piece, op0_piece);
	}

      insns = get_insns ();
      end_sequence ();

      temp = gen_rtx_fmt_e (code, mode, copy_rtx (op0));
      emit_no_conflict_block (insns, target, op0, NULL_RTX, temp);
    }
  else
    {
      temp = expand_binop (imode, code == ABS ? and_optab : xor_optab,
			   gen_lowpart (imode, op0),
			   immed_double_const (lo, hi, imode),
		           gen_lowpart (imode, target), 1, OPTAB_LIB_WIDEN);
      target = lowpart_subreg_maybe_copy (mode, temp, imode);

      set_unique_reg_note (get_last_insn (), REG_EQUAL,
			   gen_rtx_fmt_e (code, mode, copy_rtx (op0)));
    }

  return target;
}