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
typedef  int /*<<< orphan*/  rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 scalar_t__ CONST_DOUBLE ; 
 scalar_t__ CONST_DOUBLE_OK_FOR_CONSTRAINT_P (int /*<<< orphan*/ ,char,char*) ; 
 scalar_t__ CONST_INT ; 
 scalar_t__ CONST_OK_FOR_K (scalar_t__) ; 
 scalar_t__ CONST_OK_FOR_Os (scalar_t__) ; 
 scalar_t__ DISP_IN_RANGE (scalar_t__) ; 
 int DImode ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ HImode ; 
 scalar_t__ INTVAL (int /*<<< orphan*/ ) ; 
 scalar_t__ SImode ; 
 scalar_t__ TARGET_CPU_ZARCH ; 
 scalar_t__ TARGET_EXTIMM ; 
 scalar_t__ TARGET_ZARCH ; 
 int TImode ; 
 int /*<<< orphan*/  VOIDmode ; 
 scalar_t__ larl_operand (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  operand_subword (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ s390_single_part (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ trunc_int_for_mode (scalar_t__,scalar_t__) ; 
 scalar_t__ word_mode ; 

bool
legitimate_reload_constant_p (rtx op)
{
  /* Accept la(y) operands.  */
  if (GET_CODE (op) == CONST_INT
      && DISP_IN_RANGE (INTVAL (op)))
    return true;

  /* Accept l(g)hi/l(g)fi operands.  */
  if (GET_CODE (op) == CONST_INT
      && (CONST_OK_FOR_K (INTVAL (op)) || CONST_OK_FOR_Os (INTVAL (op))))
    return true;

  /* Accept lliXX operands.  */
  if (TARGET_ZARCH
      && GET_CODE (op) == CONST_INT
      && trunc_int_for_mode (INTVAL (op), word_mode) == INTVAL (op)
      && s390_single_part (op, word_mode, HImode, 0) >= 0)
  return true;

  if (TARGET_EXTIMM
      && GET_CODE (op) == CONST_INT
      && trunc_int_for_mode (INTVAL (op), word_mode) == INTVAL (op)
      && s390_single_part (op, word_mode, SImode, 0) >= 0)
    return true;

  /* Accept larl operands.  */
  if (TARGET_CPU_ZARCH
      && larl_operand (op, VOIDmode))
    return true;

  /* Accept lzXX operands.  */
  if (GET_CODE (op) == CONST_DOUBLE
      && CONST_DOUBLE_OK_FOR_CONSTRAINT_P (op, 'G', "G"))
    return true;

  /* Accept double-word operands that can be split.  */
  if (GET_CODE (op) == CONST_INT
      && trunc_int_for_mode (INTVAL (op), word_mode) != INTVAL (op))
    {
      enum machine_mode dword_mode = word_mode == SImode ? DImode : TImode;
      rtx hi = operand_subword (op, 0, 0, dword_mode);
      rtx lo = operand_subword (op, 1, 0, dword_mode);
      return legitimate_reload_constant_p (hi)
	     && legitimate_reload_constant_p (lo);
    }

  /* Everything else cannot be handled without reload.  */
  return false;
}