#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
typedef  enum insn_code { ____Placeholder_insn_code } insn_code ;
typedef  TYPE_2__* convert_optab ;
struct TYPE_6__ {TYPE_1__** handlers; } ;
struct TYPE_5__ {scalar_t__ libfunc; } ;
typedef  int /*<<< orphan*/  REAL_VALUE_TYPE ;

/* Variables and functions */
 int CODE_FOR_nothing ; 
 scalar_t__ CONST_DOUBLE_FROM_REAL_VALUE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DECIMAL_FLOAT_MODE_P (size_t) ; 
 scalar_t__ FIRST_PSEUDO_REGISTER ; 
 int /*<<< orphan*/  FLOAT ; 
 int /*<<< orphan*/  GE ; 
 size_t GET_MODE (scalar_t__) ; 
 scalar_t__ GET_MODE_BITSIZE (size_t) ; 
 scalar_t__ GET_MODE_SIZE (size_t) ; 
 int GET_MODE_WIDER_MODE (int) ; 
 int /*<<< orphan*/  LCT_CONST ; 
 int /*<<< orphan*/  LT ; 
 scalar_t__ NULL_RTX ; 
 int /*<<< orphan*/  OPTAB_LIB_WIDEN ; 
 scalar_t__ REGNO (scalar_t__) ; 
 int /*<<< orphan*/  REG_P (scalar_t__) ; 
 int /*<<< orphan*/  RSHIFT_EXPR ; 
 size_t SImode ; 
 int /*<<< orphan*/  UNSIGNED_FLOAT ; 
 int VOIDmode ; 
 int /*<<< orphan*/  add_optab ; 
 int /*<<< orphan*/  and_optab ; 
 int can_float_p (int,size_t,int) ; 
 int /*<<< orphan*/  const0_rtx ; 
 scalar_t__ const1_rtx ; 
 int /*<<< orphan*/  convert_move (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ convert_to_mode (size_t,scalar_t__,int) ; 
 int /*<<< orphan*/  do_pending_stack_adjust () ; 
 int /*<<< orphan*/  emit_barrier () ; 
 int /*<<< orphan*/  emit_cmp_and_jump_insns (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,size_t,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  emit_jump_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_label (scalar_t__) ; 
 int /*<<< orphan*/  emit_libcall_block (scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ emit_library_call_value (scalar_t__,scalar_t__,int /*<<< orphan*/ ,size_t,int,scalar_t__,size_t) ; 
 int /*<<< orphan*/  emit_move_insn (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  emit_unop_insn (int,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  end_sequence () ; 
 scalar_t__ expand_binop (int,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ expand_shift (int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  gcc_assert (scalar_t__) ; 
 int /*<<< orphan*/  gen_jump (scalar_t__) ; 
 scalar_t__ gen_label_rtx () ; 
 scalar_t__ gen_reg_rtx (int) ; 
 int /*<<< orphan*/  gen_rtx_FLOAT (size_t,scalar_t__) ; 
 scalar_t__ get_insns () ; 
 int /*<<< orphan*/  integer_one_node ; 
 int /*<<< orphan*/  ior_optab ; 
 int /*<<< orphan*/  real_2expN (int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_2__* sfloat_optab ; 
 scalar_t__ significand_size (int) ; 
 int /*<<< orphan*/  start_sequence () ; 
 TYPE_2__* ufloat_optab ; 

void
expand_float (rtx to, rtx from, int unsignedp)
{
  enum insn_code icode;
  rtx target = to;
  enum machine_mode fmode, imode;
  bool can_do_signed = false;

  /* Crash now, because we won't be able to decide which mode to use.  */
  gcc_assert (GET_MODE (from) != VOIDmode);

  /* Look for an insn to do the conversion.  Do it in the specified
     modes if possible; otherwise convert either input, output or both to
     wider mode.  If the integer mode is wider than the mode of FROM,
     we can do the conversion signed even if the input is unsigned.  */

  for (fmode = GET_MODE (to); fmode != VOIDmode;
       fmode = GET_MODE_WIDER_MODE (fmode))
    for (imode = GET_MODE (from); imode != VOIDmode;
	 imode = GET_MODE_WIDER_MODE (imode))
      {
	int doing_unsigned = unsignedp;

	if (fmode != GET_MODE (to)
	    && significand_size (fmode) < GET_MODE_BITSIZE (GET_MODE (from)))
	  continue;

	icode = can_float_p (fmode, imode, unsignedp);
	if (icode == CODE_FOR_nothing && unsignedp)
	  {
	    enum insn_code scode = can_float_p (fmode, imode, 0);
	    if (scode != CODE_FOR_nothing)
	      can_do_signed = true;
	    if (imode != GET_MODE (from))
	      icode = scode, doing_unsigned = 0;
	  }

	if (icode != CODE_FOR_nothing)
	  {
	    if (imode != GET_MODE (from))
	      from = convert_to_mode (imode, from, unsignedp);

	    if (fmode != GET_MODE (to))
	      target = gen_reg_rtx (fmode);

	    emit_unop_insn (icode, target, from,
			    doing_unsigned ? UNSIGNED_FLOAT : FLOAT);

	    if (target != to)
	      convert_move (to, target, 0);
	    return;
	  }
      }

  /* Unsigned integer, and no way to convert directly.  For binary
     floating point modes, convert as signed, then conditionally adjust
     the result.  */
  if (unsignedp && can_do_signed && !DECIMAL_FLOAT_MODE_P (GET_MODE (to)))
    {
      rtx label = gen_label_rtx ();
      rtx temp;
      REAL_VALUE_TYPE offset;

      /* Look for a usable floating mode FMODE wider than the source and at
	 least as wide as the target.  Using FMODE will avoid rounding woes
	 with unsigned values greater than the signed maximum value.  */

      for (fmode = GET_MODE (to);  fmode != VOIDmode;
	   fmode = GET_MODE_WIDER_MODE (fmode))
	if (GET_MODE_BITSIZE (GET_MODE (from)) < GET_MODE_BITSIZE (fmode)
	    && can_float_p (fmode, GET_MODE (from), 0) != CODE_FOR_nothing)
	  break;

      if (fmode == VOIDmode)
	{
	  /* There is no such mode.  Pretend the target is wide enough.  */
	  fmode = GET_MODE (to);

	  /* Avoid double-rounding when TO is narrower than FROM.  */
	  if ((significand_size (fmode) + 1)
	      < GET_MODE_BITSIZE (GET_MODE (from)))
	    {
	      rtx temp1;
	      rtx neglabel = gen_label_rtx ();

	      /* Don't use TARGET if it isn't a register, is a hard register,
		 or is the wrong mode.  */
	      if (!REG_P (target)
		  || REGNO (target) < FIRST_PSEUDO_REGISTER
		  || GET_MODE (target) != fmode)
		target = gen_reg_rtx (fmode);

	      imode = GET_MODE (from);
	      do_pending_stack_adjust ();

	      /* Test whether the sign bit is set.  */
	      emit_cmp_and_jump_insns (from, const0_rtx, LT, NULL_RTX, imode,
				       0, neglabel);

	      /* The sign bit is not set.  Convert as signed.  */
	      expand_float (target, from, 0);
	      emit_jump_insn (gen_jump (label));
	      emit_barrier ();

	      /* The sign bit is set.
		 Convert to a usable (positive signed) value by shifting right
		 one bit, while remembering if a nonzero bit was shifted
		 out; i.e., compute  (from & 1) | (from >> 1).  */

	      emit_label (neglabel);
	      temp = expand_binop (imode, and_optab, from, const1_rtx,
				   NULL_RTX, 1, OPTAB_LIB_WIDEN);
	      temp1 = expand_shift (RSHIFT_EXPR, imode, from, integer_one_node,
				    NULL_RTX, 1);
	      temp = expand_binop (imode, ior_optab, temp, temp1, temp, 1,
				   OPTAB_LIB_WIDEN);
	      expand_float (target, temp, 0);

	      /* Multiply by 2 to undo the shift above.  */
	      temp = expand_binop (fmode, add_optab, target, target,
				   target, 0, OPTAB_LIB_WIDEN);
	      if (temp != target)
		emit_move_insn (target, temp);

	      do_pending_stack_adjust ();
	      emit_label (label);
	      goto done;
	    }
	}

      /* If we are about to do some arithmetic to correct for an
	 unsigned operand, do it in a pseudo-register.  */

      if (GET_MODE (to) != fmode
	  || !REG_P (to) || REGNO (to) < FIRST_PSEUDO_REGISTER)
	target = gen_reg_rtx (fmode);

      /* Convert as signed integer to floating.  */
      expand_float (target, from, 0);

      /* If FROM is negative (and therefore TO is negative),
	 correct its value by 2**bitwidth.  */

      do_pending_stack_adjust ();
      emit_cmp_and_jump_insns (from, const0_rtx, GE, NULL_RTX, GET_MODE (from),
			       0, label);


      real_2expN (&offset, GET_MODE_BITSIZE (GET_MODE (from)));
      temp = expand_binop (fmode, add_optab, target,
			   CONST_DOUBLE_FROM_REAL_VALUE (offset, fmode),
			   target, 0, OPTAB_LIB_WIDEN);
      if (temp != target)
	emit_move_insn (target, temp);

      do_pending_stack_adjust ();
      emit_label (label);
      goto done;
    }

  /* No hardware instruction available; call a library routine.  */
    {
      rtx libfunc;
      rtx insns;
      rtx value;
      convert_optab tab = unsignedp ? ufloat_optab : sfloat_optab;

      if (GET_MODE_SIZE (GET_MODE (from)) < GET_MODE_SIZE (SImode))
	from = convert_to_mode (SImode, from, unsignedp);

      libfunc = tab->handlers[GET_MODE (to)][GET_MODE (from)].libfunc;
      gcc_assert (libfunc);

      start_sequence ();

      value = emit_library_call_value (libfunc, NULL_RTX, LCT_CONST,
				       GET_MODE (to), 1, from,
				       GET_MODE (from));
      insns = get_insns ();
      end_sequence ();

      emit_libcall_block (insns, target, value,
			  gen_rtx_FLOAT (GET_MODE (to), from));
    }

 done:

  /* Copy result to requested destination
     if we have been computing in a temp location.  */

  if (target != to)
    {
      if (GET_MODE (target) == GET_MODE (to))
	emit_move_insn (to, target);
      else
	convert_move (to, target, 0);
    }
}