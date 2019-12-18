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
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
typedef  enum entry_type { ____Placeholder_entry_type } entry_type ;
typedef  int HOST_WIDE_INT ;

/* Variables and functions */
 int /*<<< orphan*/  BITS_PER_WORD ; 
#define  CONST_INT 131 
 int EXTENDED_DEF ; 
 int GET_CLASS_NARROWEST_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_CODE (int /*<<< orphan*/ *) ; 
 int GET_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE_BITSIZE (int) ; 
 int /*<<< orphan*/  GET_MODE_MASK (int) ; 
 int GET_MODE_WIDER_MODE (int) ; 
 scalar_t__ INSN_P (int /*<<< orphan*/ *) ; 
 int INTVAL (int /*<<< orphan*/ *) ; 
 int MAX_MACHINE_MODE ; 
 int /*<<< orphan*/  MODE_INT ; 
 int /*<<< orphan*/ * NEXT_INSN (int /*<<< orphan*/ *) ; 
 int NOT_RELEVANT ; 
 int /*<<< orphan*/  NULL_RTX ; 
 int /*<<< orphan*/  PARALLEL ; 
 int /*<<< orphan*/ * PATTERN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PREV_INSN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  REGNO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  REG_LIBCALL ; 
 int /*<<< orphan*/  REG_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  REG_RETVAL ; 
 int /*<<< orphan*/ * SET_DEST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SET_SRC (int /*<<< orphan*/ *) ; 
#define  SIGN_EXTEND 130 
 int SIGN_EXTENDED_DEF ; 
 int /*<<< orphan*/  SUBREG_REG (int /*<<< orphan*/ *) ; 
#define  UNKNOWN 129 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
#define  ZERO_EXTEND 128 
 int ZERO_EXTENDED_DEF ; 
 int /*<<< orphan*/  asm_noperands (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  find_reg_note (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  reg_set_between_p (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int see_get_extension_data (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/ * see_get_extension_reg (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * single_set (int /*<<< orphan*/ *) ; 
 int trunc_int_for_mode (int,int) ; 

__attribute__((used)) static enum entry_type
see_analyze_one_def (rtx insn, enum machine_mode *source_mode,
		     enum machine_mode *source_mode_unsigned)
{
  enum rtx_code extension_code;
  rtx rhs = NULL;
  rtx lhs = NULL;
  rtx set = NULL;
  rtx source_register = NULL;
  rtx prev_insn = NULL;
  rtx next_insn = NULL;
  enum machine_mode mode;
  enum machine_mode next_source_mode;
  HOST_WIDE_INT val = 0;
  HOST_WIDE_INT val2 = 0;
  int i = 0;

  *source_mode = MAX_MACHINE_MODE;
  *source_mode_unsigned = MAX_MACHINE_MODE;

  if (!insn)
    return NOT_RELEVANT;

  if (!INSN_P (insn))
    return NOT_RELEVANT;

  extension_code = see_get_extension_data (insn, source_mode);
  switch (extension_code)
    {
    case SIGN_EXTEND:
    case ZERO_EXTEND:
      source_register = see_get_extension_reg (insn, 0);
      /* FIXME: This restriction can be relaxed.  The only thing that is
	 important is that the reference would be inside the same basic block
	 as the extension.  */
      prev_insn = PREV_INSN (insn);
      if (!prev_insn || !INSN_P (prev_insn))
	return NOT_RELEVANT;

      if (!reg_set_between_p (source_register, PREV_INSN (prev_insn), insn))
	return NOT_RELEVANT;

      if (find_reg_note (prev_insn, REG_LIBCALL, NULL_RTX))
	return NOT_RELEVANT;

      if (find_reg_note (prev_insn, REG_RETVAL, NULL_RTX))
	return NOT_RELEVANT;

      /* If we can't use copy_rtx on the reference it can't be a reference.  */
      if (GET_CODE (PATTERN (prev_insn)) == PARALLEL
	   && asm_noperands (PATTERN (prev_insn)) >= 0)
	return NOT_RELEVANT;

      /* Now, check if this extension is a reference itself.  If so, it is not
	 relevant.  Handling this extension as relevant would make things much
	 more complicated.  */
      next_insn = NEXT_INSN (insn);
      if (next_insn
	  && INSN_P (next_insn)
	  && (see_get_extension_data (next_insn, &next_source_mode) !=
	      NOT_RELEVANT))
	{
	  rtx curr_dest_register = see_get_extension_reg (insn, 1);
	  rtx next_source_register = see_get_extension_reg (next_insn, 0);

	  if (REGNO (curr_dest_register) == REGNO (next_source_register))
	    return NOT_RELEVANT;
	}

      if (extension_code == SIGN_EXTEND)
	return SIGN_EXTENDED_DEF;
      else
	return ZERO_EXTENDED_DEF;

    case UNKNOWN:
      /* This may still be an EXTENDED_DEF.  */

      /* FIXME: This restriction can be relaxed.  It is possible to handle
	 PARALLEL insns too.  */
      set = single_set (insn);
      if (!set)
	return NOT_RELEVANT;
      rhs = SET_SRC (set);
      lhs = SET_DEST (set);

      /* Don't handle extensions to something other then register or
	 subregister.  */
      if (!REG_P (lhs) && !SUBREG_REG (lhs))
	return NOT_RELEVANT;

      switch (GET_CODE (rhs))
	{
	case SIGN_EXTEND:
	  *source_mode = GET_MODE (XEXP (rhs, 0));
	  *source_mode_unsigned = MAX_MACHINE_MODE;
	  return EXTENDED_DEF;
	case ZERO_EXTEND:
	  *source_mode = MAX_MACHINE_MODE;
	  *source_mode_unsigned = GET_MODE (XEXP (rhs, 0));
	  return EXTENDED_DEF;
	case CONST_INT:

	  val = INTVAL (rhs);

	  /* Find the narrowest mode, val could fit into.  */
	  for (mode = GET_CLASS_NARROWEST_MODE (MODE_INT), i = 0;
	       GET_MODE_BITSIZE (mode) < BITS_PER_WORD;
	       mode = GET_MODE_WIDER_MODE (mode), i++)
	    {
	      val2 = trunc_int_for_mode (val, mode);
  	      if (val2 == val && *source_mode == MAX_MACHINE_MODE)
		*source_mode = mode;
	      if (val == (val & (HOST_WIDE_INT)GET_MODE_MASK (mode))
		  && *source_mode_unsigned == MAX_MACHINE_MODE)
		*source_mode_unsigned = mode;
	      if (*source_mode != MAX_MACHINE_MODE
		  && *source_mode_unsigned !=MAX_MACHINE_MODE)
		return EXTENDED_DEF;
	    }
	  if (*source_mode != MAX_MACHINE_MODE
	      || *source_mode_unsigned !=MAX_MACHINE_MODE)
	    return EXTENDED_DEF;
	  return NOT_RELEVANT;
	default:
	  return NOT_RELEVANT;
	}
    default:
      gcc_unreachable ();
    }
}