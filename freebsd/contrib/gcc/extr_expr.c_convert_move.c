#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
typedef  int rtx ;
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
typedef  enum insn_code { ____Placeholder_insn_code } insn_code ;
typedef  TYPE_3__* convert_optab ;
struct TYPE_10__ {TYPE_1__* operand; } ;
struct TYPE_9__ {TYPE_2__** handlers; } ;
struct TYPE_8__ {int insn_code; int libfunc; } ;
struct TYPE_7__ {int mode; } ;

/* Variables and functions */
 scalar_t__ BITS_PER_WORD ; 
 int BLKmode ; 
 int CEIL (scalar_t__,scalar_t__) ; 
 int CODE_FOR_nothing ; 
 scalar_t__ CODE_FOR_slt ; 
 scalar_t__ CONCAT ; 
 scalar_t__ CONSTANT_P (int) ; 
 scalar_t__ DECIMAL_FLOAT_MODE_P (int) ; 
 scalar_t__ FIRST_PSEUDO_REGISTER ; 
 int FLOAT_EXTEND ; 
 int FLOAT_TRUNCATE ; 
 scalar_t__ GET_CODE (int) ; 
 int GET_MODE (int) ; 
 scalar_t__ GET_MODE_BITSIZE (int) ; 
 scalar_t__ GET_MODE_CLASS (int) ; 
 scalar_t__ GET_MODE_PRECISION (int) ; 
 scalar_t__ GET_MODE_SIZE (int) ; 
 int GET_MODE_WIDER_MODE (int) ; 
 int /*<<< orphan*/  HARD_REGNO_MODE_OK (scalar_t__,int) ; 
 scalar_t__ HAVE_slt ; 
 int /*<<< orphan*/  LCT_CONST ; 
 int /*<<< orphan*/  LSHIFT_EXPR ; 
 scalar_t__ MEM_P (int) ; 
 int /*<<< orphan*/  MEM_VOLATILE_P (int) ; 
 int /*<<< orphan*/  MODE_INT ; 
 scalar_t__ MODE_PARTIAL_INT ; 
 int /*<<< orphan*/  NE ; 
 int NULL_RTX ; 
 int /*<<< orphan*/  NULL_TREE ; 
 scalar_t__ REGNO (int) ; 
 scalar_t__ REG_P (int) ; 
 int /*<<< orphan*/  RSHIFT_EXPR ; 
 int SCALAR_FLOAT_MODE_P (int) ; 
 int SIGN_EXTEND ; 
 int STORE_FLAG_VALUE ; 
 scalar_t__ SUBREG ; 
 int SUBREG_PROMOTED_UNSIGNED_P (int) ; 
 scalar_t__ SUBREG_PROMOTED_VAR_P (int) ; 
 int SUBREG_REG (int) ; 
 scalar_t__ TRULY_NOOP_TRUNCATION (scalar_t__,scalar_t__) ; 
 scalar_t__ UNITS_PER_WORD ; 
 int UNKNOWN ; 
 scalar_t__ VECTOR_MODE_P (int) ; 
 int VOIDmode ; 
 scalar_t__ WORDS_BIG_ENDIAN ; 
 int XEXP (int,int) ; 
 int ZERO_EXTEND ; 
 int /*<<< orphan*/  build_int_cst (int /*<<< orphan*/ ,scalar_t__) ; 
 int can_extend_p (int,int,int) ; 
 int const0_rtx ; 
 int convert_to_mode (int,int,int) ; 
 int /*<<< orphan*/  copy_rtx (int) ; 
 int copy_to_reg (int) ; 
 scalar_t__* direct_load ; 
 int /*<<< orphan*/  emit_cmp_insn (int,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_libcall_block (int,int,int,int /*<<< orphan*/ ) ; 
 int emit_library_call_value (int,int,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  emit_move_insn (int,int) ; 
 int /*<<< orphan*/  emit_no_conflict_block (int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_unop_insn (int,int,int,int) ; 
 int /*<<< orphan*/  end_sequence () ; 
 int expand_shift (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int,int) ; 
 int force_reg (int,int) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int gen_lowpart (int,int) ; 
 int gen_reg_rtx (int) ; 
 int /*<<< orphan*/  gen_rtx_CLOBBER (int,int) ; 
 int /*<<< orphan*/  gen_rtx_FLOAT_EXTEND (int,int) ; 
 int /*<<< orphan*/  gen_rtx_FLOAT_TRUNCATE (int,int) ; 
 int /*<<< orphan*/  gen_rtx_fmt_e (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_slt (int) ; 
 int get_insns () ; 
 TYPE_6__* insn_data ; 
 int /*<<< orphan*/  mode_dependent_address_p (int) ; 
 int operand_subword (int,int,int,int) ; 
 scalar_t__ optimize ; 
 scalar_t__ reg_overlap_mentioned_p (int,int) ; 
 TYPE_3__* sext_optab ; 
 int simplify_gen_subreg (int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  size_int (scalar_t__) ; 
 int smallest_mode_for_size (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_sequence () ; 
 TYPE_3__* trunc_optab ; 
 int word_mode ; 

void
convert_move (rtx to, rtx from, int unsignedp)
{
  enum machine_mode to_mode = GET_MODE (to);
  enum machine_mode from_mode = GET_MODE (from);
  int to_real = SCALAR_FLOAT_MODE_P (to_mode);
  int from_real = SCALAR_FLOAT_MODE_P (from_mode);
  enum insn_code code;
  rtx libcall;

  /* rtx code for making an equivalent value.  */
  enum rtx_code equiv_code = (unsignedp < 0 ? UNKNOWN
			      : (unsignedp ? ZERO_EXTEND : SIGN_EXTEND));


  gcc_assert (to_real == from_real);
  gcc_assert (to_mode != BLKmode);
  gcc_assert (from_mode != BLKmode);

  /* If the source and destination are already the same, then there's
     nothing to do.  */
  if (to == from)
    return;

  /* If FROM is a SUBREG that indicates that we have already done at least
     the required extension, strip it.  We don't handle such SUBREGs as
     TO here.  */

  if (GET_CODE (from) == SUBREG && SUBREG_PROMOTED_VAR_P (from)
      && (GET_MODE_SIZE (GET_MODE (SUBREG_REG (from)))
	  >= GET_MODE_SIZE (to_mode))
      && SUBREG_PROMOTED_UNSIGNED_P (from) == unsignedp)
    from = gen_lowpart (to_mode, from), from_mode = to_mode;

  gcc_assert (GET_CODE (to) != SUBREG || !SUBREG_PROMOTED_VAR_P (to));

  if (to_mode == from_mode
      || (from_mode == VOIDmode && CONSTANT_P (from)))
    {
      emit_move_insn (to, from);
      return;
    }

  if (VECTOR_MODE_P (to_mode) || VECTOR_MODE_P (from_mode))
    {
      gcc_assert (GET_MODE_BITSIZE (from_mode) == GET_MODE_BITSIZE (to_mode));

      if (VECTOR_MODE_P (to_mode))
	from = simplify_gen_subreg (to_mode, from, GET_MODE (from), 0);
      else
	to = simplify_gen_subreg (from_mode, to, GET_MODE (to), 0);

      emit_move_insn (to, from);
      return;
    }

  if (GET_CODE (to) == CONCAT && GET_CODE (from) == CONCAT)
    {
      convert_move (XEXP (to, 0), XEXP (from, 0), unsignedp);
      convert_move (XEXP (to, 1), XEXP (from, 1), unsignedp);
      return;
    }

  if (to_real)
    {
      rtx value, insns;
      convert_optab tab;

      gcc_assert ((GET_MODE_PRECISION (from_mode)
		   != GET_MODE_PRECISION (to_mode))
		  || (DECIMAL_FLOAT_MODE_P (from_mode)
		      != DECIMAL_FLOAT_MODE_P (to_mode)));

      if (GET_MODE_PRECISION (from_mode) == GET_MODE_PRECISION (to_mode))
	/* Conversion between decimal float and binary float, same size.  */
	tab = DECIMAL_FLOAT_MODE_P (from_mode) ? trunc_optab : sext_optab;
      else if (GET_MODE_PRECISION (from_mode) < GET_MODE_PRECISION (to_mode))
	tab = sext_optab;
      else
	tab = trunc_optab;

      /* Try converting directly if the insn is supported.  */

      code = tab->handlers[to_mode][from_mode].insn_code;
      if (code != CODE_FOR_nothing)
	{
	  emit_unop_insn (code, to, from,
			  tab == sext_optab ? FLOAT_EXTEND : FLOAT_TRUNCATE);
	  return;
	}

      /* Otherwise use a libcall.  */
      libcall = tab->handlers[to_mode][from_mode].libfunc;

      /* Is this conversion implemented yet?  */
      gcc_assert (libcall);

      start_sequence ();
      value = emit_library_call_value (libcall, NULL_RTX, LCT_CONST, to_mode,
				       1, from, from_mode);
      insns = get_insns ();
      end_sequence ();
      emit_libcall_block (insns, to, value,
			  tab == trunc_optab ? gen_rtx_FLOAT_TRUNCATE (to_mode,
								       from)
			  : gen_rtx_FLOAT_EXTEND (to_mode, from));
      return;
    }

  /* Handle pointer conversion.  */			/* SPEE 900220.  */
  /* Targets are expected to provide conversion insns between PxImode and
     xImode for all MODE_PARTIAL_INT modes they use, but no others.  */
  if (GET_MODE_CLASS (to_mode) == MODE_PARTIAL_INT)
    {
      enum machine_mode full_mode
	= smallest_mode_for_size (GET_MODE_BITSIZE (to_mode), MODE_INT);

      gcc_assert (trunc_optab->handlers[to_mode][full_mode].insn_code
		  != CODE_FOR_nothing);

      if (full_mode != from_mode)
	from = convert_to_mode (full_mode, from, unsignedp);
      emit_unop_insn (trunc_optab->handlers[to_mode][full_mode].insn_code,
		      to, from, UNKNOWN);
      return;
    }
  if (GET_MODE_CLASS (from_mode) == MODE_PARTIAL_INT)
    {
      rtx new_from;
      enum machine_mode full_mode
	= smallest_mode_for_size (GET_MODE_BITSIZE (from_mode), MODE_INT);

      gcc_assert (sext_optab->handlers[full_mode][from_mode].insn_code
		  != CODE_FOR_nothing);

      if (to_mode == full_mode)
	{
	  emit_unop_insn (sext_optab->handlers[full_mode][from_mode].insn_code,
			  to, from, UNKNOWN);
	  return;
	}

      new_from = gen_reg_rtx (full_mode);
      emit_unop_insn (sext_optab->handlers[full_mode][from_mode].insn_code,
		      new_from, from, UNKNOWN);

      /* else proceed to integer conversions below.  */
      from_mode = full_mode;
      from = new_from;
    }

  /* Now both modes are integers.  */

  /* Handle expanding beyond a word.  */
  if (GET_MODE_BITSIZE (from_mode) < GET_MODE_BITSIZE (to_mode)
      && GET_MODE_BITSIZE (to_mode) > BITS_PER_WORD)
    {
      rtx insns;
      rtx lowpart;
      rtx fill_value;
      rtx lowfrom;
      int i;
      enum machine_mode lowpart_mode;
      int nwords = CEIL (GET_MODE_SIZE (to_mode), UNITS_PER_WORD);

      /* Try converting directly if the insn is supported.  */
      if ((code = can_extend_p (to_mode, from_mode, unsignedp))
	  != CODE_FOR_nothing)
	{
	  /* If FROM is a SUBREG, put it into a register.  Do this
	     so that we always generate the same set of insns for
	     better cse'ing; if an intermediate assignment occurred,
	     we won't be doing the operation directly on the SUBREG.  */
	  if (optimize > 0 && GET_CODE (from) == SUBREG)
	    from = force_reg (from_mode, from);
	  emit_unop_insn (code, to, from, equiv_code);
	  return;
	}
      /* Next, try converting via full word.  */
      else if (GET_MODE_BITSIZE (from_mode) < BITS_PER_WORD
	       && ((code = can_extend_p (to_mode, word_mode, unsignedp))
		   != CODE_FOR_nothing))
	{
	  if (REG_P (to))
	    {
	      if (reg_overlap_mentioned_p (to, from))
		from = force_reg (from_mode, from);
	      emit_insn (gen_rtx_CLOBBER (VOIDmode, to));
	    }
	  convert_move (gen_lowpart (word_mode, to), from, unsignedp);
	  emit_unop_insn (code, to,
			  gen_lowpart (word_mode, to), equiv_code);
	  return;
	}

      /* No special multiword conversion insn; do it by hand.  */
      start_sequence ();

      /* Since we will turn this into a no conflict block, we must ensure
	 that the source does not overlap the target.  */

      if (reg_overlap_mentioned_p (to, from))
	from = force_reg (from_mode, from);

      /* Get a copy of FROM widened to a word, if necessary.  */
      if (GET_MODE_BITSIZE (from_mode) < BITS_PER_WORD)
	lowpart_mode = word_mode;
      else
	lowpart_mode = from_mode;

      lowfrom = convert_to_mode (lowpart_mode, from, unsignedp);

      lowpart = gen_lowpart (lowpart_mode, to);
      emit_move_insn (lowpart, lowfrom);

      /* Compute the value to put in each remaining word.  */
      if (unsignedp)
	fill_value = const0_rtx;
      else
	{
#ifdef HAVE_slt
	  if (HAVE_slt
	      && insn_data[(int) CODE_FOR_slt].operand[0].mode == word_mode
	      && STORE_FLAG_VALUE == -1)
	    {
	      emit_cmp_insn (lowfrom, const0_rtx, NE, NULL_RTX,
			     lowpart_mode, 0);
	      fill_value = gen_reg_rtx (word_mode);
	      emit_insn (gen_slt (fill_value));
	    }
	  else
#endif
	    {
	      fill_value
		= expand_shift (RSHIFT_EXPR, lowpart_mode, lowfrom,
				size_int (GET_MODE_BITSIZE (lowpart_mode) - 1),
				NULL_RTX, 0);
	      fill_value = convert_to_mode (word_mode, fill_value, 1);
	    }
	}

      /* Fill the remaining words.  */
      for (i = GET_MODE_SIZE (lowpart_mode) / UNITS_PER_WORD; i < nwords; i++)
	{
	  int index = (WORDS_BIG_ENDIAN ? nwords - i - 1 : i);
	  rtx subword = operand_subword (to, index, 1, to_mode);

	  gcc_assert (subword);

	  if (fill_value != subword)
	    emit_move_insn (subword, fill_value);
	}

      insns = get_insns ();
      end_sequence ();

      emit_no_conflict_block (insns, to, from, NULL_RTX,
			      gen_rtx_fmt_e (equiv_code, to_mode, copy_rtx (from)));
      return;
    }

  /* Truncating multi-word to a word or less.  */
  if (GET_MODE_BITSIZE (from_mode) > BITS_PER_WORD
      && GET_MODE_BITSIZE (to_mode) <= BITS_PER_WORD)
    {
      if (!((MEM_P (from)
	     && ! MEM_VOLATILE_P (from)
	     && direct_load[(int) to_mode]
	     && ! mode_dependent_address_p (XEXP (from, 0)))
	    || REG_P (from)
	    || GET_CODE (from) == SUBREG))
	from = force_reg (from_mode, from);
      convert_move (to, gen_lowpart (word_mode, from), 0);
      return;
    }

  /* Now follow all the conversions between integers
     no more than a word long.  */

  /* For truncation, usually we can just refer to FROM in a narrower mode.  */
  if (GET_MODE_BITSIZE (to_mode) < GET_MODE_BITSIZE (from_mode)
      && TRULY_NOOP_TRUNCATION (GET_MODE_BITSIZE (to_mode),
				GET_MODE_BITSIZE (from_mode)))
    {
      if (!((MEM_P (from)
	     && ! MEM_VOLATILE_P (from)
	     && direct_load[(int) to_mode]
	     && ! mode_dependent_address_p (XEXP (from, 0)))
	    || REG_P (from)
	    || GET_CODE (from) == SUBREG))
	from = force_reg (from_mode, from);
      if (REG_P (from) && REGNO (from) < FIRST_PSEUDO_REGISTER
	  && ! HARD_REGNO_MODE_OK (REGNO (from), to_mode))
	from = copy_to_reg (from);
      emit_move_insn (to, gen_lowpart (to_mode, from));
      return;
    }

  /* Handle extension.  */
  if (GET_MODE_BITSIZE (to_mode) > GET_MODE_BITSIZE (from_mode))
    {
      /* Convert directly if that works.  */
      if ((code = can_extend_p (to_mode, from_mode, unsignedp))
	  != CODE_FOR_nothing)
	{
	  emit_unop_insn (code, to, from, equiv_code);
	  return;
	}
      else
	{
	  enum machine_mode intermediate;
	  rtx tmp;
	  tree shift_amount;

	  /* Search for a mode to convert via.  */
	  for (intermediate = from_mode; intermediate != VOIDmode;
	       intermediate = GET_MODE_WIDER_MODE (intermediate))
	    if (((can_extend_p (to_mode, intermediate, unsignedp)
		  != CODE_FOR_nothing)
		 || (GET_MODE_SIZE (to_mode) < GET_MODE_SIZE (intermediate)
		     && TRULY_NOOP_TRUNCATION (GET_MODE_BITSIZE (to_mode),
					       GET_MODE_BITSIZE (intermediate))))
		&& (can_extend_p (intermediate, from_mode, unsignedp)
		    != CODE_FOR_nothing))
	      {
		convert_move (to, convert_to_mode (intermediate, from,
						   unsignedp), unsignedp);
		return;
	      }

	  /* No suitable intermediate mode.
	     Generate what we need with	shifts.  */
	  shift_amount = build_int_cst (NULL_TREE,
					GET_MODE_BITSIZE (to_mode)
					- GET_MODE_BITSIZE (from_mode));
	  from = gen_lowpart (to_mode, force_reg (from_mode, from));
	  tmp = expand_shift (LSHIFT_EXPR, to_mode, from, shift_amount,
			      to, unsignedp);
	  tmp = expand_shift (RSHIFT_EXPR, to_mode, tmp, shift_amount,
			      to, unsignedp);
	  if (tmp != to)
	    emit_move_insn (to, tmp);
	  return;
	}
    }

  /* Support special truncate insns for certain modes.  */
  if (trunc_optab->handlers[to_mode][from_mode].insn_code != CODE_FOR_nothing)
    {
      emit_unop_insn (trunc_optab->handlers[to_mode][from_mode].insn_code,
		      to, from, UNKNOWN);
      return;
    }

  /* Handle truncation of volatile memrefs, and so on;
     the things that couldn't be truncated directly,
     and for which there was no special instruction.

     ??? Code above formerly short-circuited this, for most integer
     mode pairs, with a force_reg in from_mode followed by a recursive
     call to this routine.  Appears always to have been wrong.  */
  if (GET_MODE_BITSIZE (to_mode) < GET_MODE_BITSIZE (from_mode))
    {
      rtx temp = force_reg (to_mode, gen_lowpart (to_mode, from));
      emit_move_insn (to, temp);
      return;
    }

  /* Mode combination is not recognized.  */
  gcc_unreachable ();
}