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

/* Variables and functions */
 unsigned int BITS_PER_UNIT ; 
 scalar_t__ CONST ; 
 scalar_t__ CONSTANT_P (scalar_t__) ; 
 scalar_t__ CONST_INT ; 
 unsigned int DECL_ALIGN (scalar_t__) ; 
 scalar_t__ DECL_P (scalar_t__) ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 int INTVAL (scalar_t__) ; 
 scalar_t__ LABEL_REF ; 
 unsigned int MEM_ALIGN (scalar_t__) ; 
 scalar_t__ MEM_P (scalar_t__) ; 
 scalar_t__ MEM_POINTER (scalar_t__) ; 
 unsigned int MIN (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  NULL_RTX ; 
 scalar_t__ PLUS ; 
 int /*<<< orphan*/  REG_EQUAL ; 
 scalar_t__ REG_P (scalar_t__) ; 
 scalar_t__ SET_DEST (scalar_t__) ; 
 int /*<<< orphan*/  SET_SRC (scalar_t__) ; 
 scalar_t__ SYMBOL_REF ; 
 scalar_t__ SYMBOL_REF_DECL (scalar_t__) ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 scalar_t__ emit_move_insn (scalar_t__,scalar_t__) ; 
 unsigned int exact_log2 (int) ; 
 scalar_t__ force_operand (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ gen_reg_rtx (int) ; 
 scalar_t__ general_operand (scalar_t__,int) ; 
 scalar_t__ get_last_insn () ; 
 int /*<<< orphan*/  mark_reg_pointer (scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  rtx_equal_p (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_unique_reg_note (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ single_set (scalar_t__) ; 

rtx
force_reg (enum machine_mode mode, rtx x)
{
  rtx temp, insn, set;

  if (REG_P (x))
    return x;

  if (general_operand (x, mode))
    {
      temp = gen_reg_rtx (mode);
      insn = emit_move_insn (temp, x);
    }
  else
    {
      temp = force_operand (x, NULL_RTX);
      if (REG_P (temp))
	insn = get_last_insn ();
      else
	{
	  rtx temp2 = gen_reg_rtx (mode);
	  insn = emit_move_insn (temp2, temp);
	  temp = temp2;
	}
    }

  /* Let optimizers know that TEMP's value never changes
     and that X can be substituted for it.  Don't get confused
     if INSN set something else (such as a SUBREG of TEMP).  */
  if (CONSTANT_P (x)
      && (set = single_set (insn)) != 0
      && SET_DEST (set) == temp
      && ! rtx_equal_p (x, SET_SRC (set)))
    set_unique_reg_note (insn, REG_EQUAL, x);

  /* Let optimizers know that TEMP is a pointer, and if so, the
     known alignment of that pointer.  */
  {
    unsigned align = 0;
    if (GET_CODE (x) == SYMBOL_REF)
      {
        align = BITS_PER_UNIT;
	if (SYMBOL_REF_DECL (x) && DECL_P (SYMBOL_REF_DECL (x)))
	  align = DECL_ALIGN (SYMBOL_REF_DECL (x));
      }
    else if (GET_CODE (x) == LABEL_REF)
      align = BITS_PER_UNIT;
    else if (GET_CODE (x) == CONST
	     && GET_CODE (XEXP (x, 0)) == PLUS
	     && GET_CODE (XEXP (XEXP (x, 0), 0)) == SYMBOL_REF
	     && GET_CODE (XEXP (XEXP (x, 0), 1)) == CONST_INT)
      {
	rtx s = XEXP (XEXP (x, 0), 0);
	rtx c = XEXP (XEXP (x, 0), 1);
	unsigned sa, ca;

	sa = BITS_PER_UNIT;
	if (SYMBOL_REF_DECL (s) && DECL_P (SYMBOL_REF_DECL (s)))
	  sa = DECL_ALIGN (SYMBOL_REF_DECL (s));

	ca = exact_log2 (INTVAL (c) & -INTVAL (c)) * BITS_PER_UNIT;

	align = MIN (sa, ca);
      }
    else if (MEM_P (x) && MEM_POINTER (x))
      align = MEM_ALIGN (x);

    if (align)
      mark_reg_pointer (temp, align);
  }

  return temp;
}