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
typedef  scalar_t__ rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
typedef  enum insn_code { ____Placeholder_insn_code } insn_code ;
typedef  TYPE_3__* convert_optab ;
struct TYPE_10__ {TYPE_1__* handlers; } ;
struct TYPE_9__ {TYPE_2__** handlers; } ;
struct TYPE_8__ {scalar_t__ libfunc; } ;
struct TYPE_7__ {int insn_code; } ;
typedef  int /*<<< orphan*/  REAL_VALUE_TYPE ;
typedef  int HOST_WIDE_INT ;

/* Variables and functions */
 int CODE_FOR_nothing ; 
 scalar_t__ CONST_DOUBLE_FROM_REAL_VALUE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FIX ; 
 int /*<<< orphan*/  GE ; 
 size_t GET_MODE (scalar_t__) ; 
 int GET_MODE_BITSIZE (size_t) ; 
 scalar_t__ GET_MODE_SIZE (size_t) ; 
 int GET_MODE_WIDER_MODE (int) ; 
 int HOST_BITS_PER_WIDE_INT ; 
 int /*<<< orphan*/  LCT_CONST ; 
 scalar_t__ NULL_RTX ; 
 int /*<<< orphan*/  OPTAB_LIB_WIDEN ; 
 int /*<<< orphan*/  REG_EQUAL ; 
 size_t SImode ; 
 int /*<<< orphan*/  UNSIGNED_FIX ; 
 int VOIDmode ; 
 int can_fix_p (size_t,int,int,int*) ; 
 int /*<<< orphan*/  convert_move (scalar_t__,scalar_t__,int) ; 
 scalar_t__ convert_to_mode (int,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ copy_rtx (scalar_t__) ; 
 int /*<<< orphan*/  do_pending_stack_adjust () ; 
 int /*<<< orphan*/  emit_barrier () ; 
 int /*<<< orphan*/  emit_cmp_and_jump_insns (scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__,size_t,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  emit_jump_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_label (scalar_t__) ; 
 int /*<<< orphan*/  emit_libcall_block (scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ emit_library_call_value (scalar_t__,scalar_t__,int /*<<< orphan*/ ,size_t,int,scalar_t__,size_t) ; 
 scalar_t__ emit_move_insn (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  emit_unop_insn (int,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  end_sequence () ; 
 scalar_t__ expand_binop (size_t,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ expand_unop (size_t,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ftrunc_optab ; 
 int /*<<< orphan*/  gcc_assert (scalar_t__) ; 
 scalar_t__ gen_int_mode (int,size_t) ; 
 int /*<<< orphan*/  gen_jump (scalar_t__) ; 
 scalar_t__ gen_label_rtx () ; 
 scalar_t__ gen_reg_rtx (size_t) ; 
 int /*<<< orphan*/  gen_rtx_fmt_e (int /*<<< orphan*/ ,size_t,scalar_t__) ; 
 scalar_t__ get_insns () ; 
 TYPE_6__* mov_optab ; 
 int /*<<< orphan*/  real_2expN (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_unique_reg_note (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* sfix_optab ; 
 int /*<<< orphan*/  start_sequence () ; 
 int /*<<< orphan*/  sub_optab ; 
 TYPE_3__* ufix_optab ; 
 int /*<<< orphan*/  xor_optab ; 

void
expand_fix (rtx to, rtx from, int unsignedp)
{
  enum insn_code icode;
  rtx target = to;
  enum machine_mode fmode, imode;
  int must_trunc = 0;

  /* We first try to find a pair of modes, one real and one integer, at
     least as wide as FROM and TO, respectively, in which we can open-code
     this conversion.  If the integer mode is wider than the mode of TO,
     we can do the conversion either signed or unsigned.  */

  for (fmode = GET_MODE (from); fmode != VOIDmode;
       fmode = GET_MODE_WIDER_MODE (fmode))
    for (imode = GET_MODE (to); imode != VOIDmode;
	 imode = GET_MODE_WIDER_MODE (imode))
      {
	int doing_unsigned = unsignedp;

	icode = can_fix_p (imode, fmode, unsignedp, &must_trunc);
	if (icode == CODE_FOR_nothing && imode != GET_MODE (to) && unsignedp)
	  icode = can_fix_p (imode, fmode, 0, &must_trunc), doing_unsigned = 0;

	if (icode != CODE_FOR_nothing)
	  {
	    if (fmode != GET_MODE (from))
	      from = convert_to_mode (fmode, from, 0);

	    if (must_trunc)
	      {
		rtx temp = gen_reg_rtx (GET_MODE (from));
		from = expand_unop (GET_MODE (from), ftrunc_optab, from,
				    temp, 0);
	      }

	    if (imode != GET_MODE (to))
	      target = gen_reg_rtx (imode);

	    emit_unop_insn (icode, target, from,
			    doing_unsigned ? UNSIGNED_FIX : FIX);
	    if (target != to)
	      convert_move (to, target, unsignedp);
	    return;
	  }
      }

  /* For an unsigned conversion, there is one more way to do it.
     If we have a signed conversion, we generate code that compares
     the real value to the largest representable positive number.  If if
     is smaller, the conversion is done normally.  Otherwise, subtract
     one plus the highest signed number, convert, and add it back.

     We only need to check all real modes, since we know we didn't find
     anything with a wider integer mode.

     This code used to extend FP value into mode wider than the destination.
     This is not needed.  Consider, for instance conversion from SFmode
     into DImode.

     The hot path through the code is dealing with inputs smaller than 2^63
     and doing just the conversion, so there is no bits to lose.

     In the other path we know the value is positive in the range 2^63..2^64-1
     inclusive.  (as for other imput overflow happens and result is undefined)
     So we know that the most important bit set in mantissa corresponds to
     2^63.  The subtraction of 2^63 should not generate any rounding as it
     simply clears out that bit.  The rest is trivial.  */

  if (unsignedp && GET_MODE_BITSIZE (GET_MODE (to)) <= HOST_BITS_PER_WIDE_INT)
    for (fmode = GET_MODE (from); fmode != VOIDmode;
	 fmode = GET_MODE_WIDER_MODE (fmode))
      if (CODE_FOR_nothing != can_fix_p (GET_MODE (to), fmode, 0,
					 &must_trunc))
	{
	  int bitsize;
	  REAL_VALUE_TYPE offset;
	  rtx limit, lab1, lab2, insn;

	  bitsize = GET_MODE_BITSIZE (GET_MODE (to));
	  real_2expN (&offset, bitsize - 1);
	  limit = CONST_DOUBLE_FROM_REAL_VALUE (offset, fmode);
	  lab1 = gen_label_rtx ();
	  lab2 = gen_label_rtx ();

	  if (fmode != GET_MODE (from))
	    from = convert_to_mode (fmode, from, 0);

	  /* See if we need to do the subtraction.  */
	  do_pending_stack_adjust ();
	  emit_cmp_and_jump_insns (from, limit, GE, NULL_RTX, GET_MODE (from),
				   0, lab1);

	  /* If not, do the signed "fix" and branch around fixup code.  */
	  expand_fix (to, from, 0);
	  emit_jump_insn (gen_jump (lab2));
	  emit_barrier ();

	  /* Otherwise, subtract 2**(N-1), convert to signed number,
	     then add 2**(N-1).  Do the addition using XOR since this
	     will often generate better code.  */
	  emit_label (lab1);
	  target = expand_binop (GET_MODE (from), sub_optab, from, limit,
				 NULL_RTX, 0, OPTAB_LIB_WIDEN);
	  expand_fix (to, target, 0);
	  target = expand_binop (GET_MODE (to), xor_optab, to,
				 gen_int_mode
				 ((HOST_WIDE_INT) 1 << (bitsize - 1),
				  GET_MODE (to)),
				 to, 1, OPTAB_LIB_WIDEN);

	  if (target != to)
	    emit_move_insn (to, target);

	  emit_label (lab2);

	  if (mov_optab->handlers[(int) GET_MODE (to)].insn_code
	      != CODE_FOR_nothing)
	    {
	      /* Make a place for a REG_NOTE and add it.  */
	      insn = emit_move_insn (to, to);
	      set_unique_reg_note (insn,
	                           REG_EQUAL,
				   gen_rtx_fmt_e (UNSIGNED_FIX,
						  GET_MODE (to),
						  copy_rtx (from)));
	    }

	  return;
	}

  /* We can't do it with an insn, so use a library call.  But first ensure
     that the mode of TO is at least as wide as SImode, since those are the
     only library calls we know about.  */

  if (GET_MODE_SIZE (GET_MODE (to)) < GET_MODE_SIZE (SImode))
    {
      target = gen_reg_rtx (SImode);

      expand_fix (target, from, unsignedp);
    }
  else
    {
      rtx insns;
      rtx value;
      rtx libfunc;

      convert_optab tab = unsignedp ? ufix_optab : sfix_optab;
      libfunc = tab->handlers[GET_MODE (to)][GET_MODE (from)].libfunc;
      gcc_assert (libfunc);

      start_sequence ();

      value = emit_library_call_value (libfunc, NULL_RTX, LCT_CONST,
				       GET_MODE (to), 1, from,
				       GET_MODE (from));
      insns = get_insns ();
      end_sequence ();

      emit_libcall_block (insns, target, value,
			  gen_rtx_fmt_e (unsignedp ? UNSIGNED_FIX : FIX,
					 GET_MODE (to), from));
    }

  if (target != to)
    {
      if (GET_MODE (to) == GET_MODE (target))
        emit_move_insn (to, target);
      else
        convert_move (to, target, 0);
    }
}