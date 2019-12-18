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

/* Variables and functions */
#define  ASM_OPERANDS 139 
 int /*<<< orphan*/  ASM_OPERANDS_INPUT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ASM_OPERANDS_INPUT_LENGTH (int /*<<< orphan*/ ) ; 
#define  CALL 138 
 int CC0 ; 
#define  CLOBBER 137 
#define  COND_EXEC 136 
 int /*<<< orphan*/  COND_EXEC_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COND_EXEC_TEST (int /*<<< orphan*/ ) ; 
 int GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE (int /*<<< orphan*/ ) ; 
 int GET_MODE_SIZE (int /*<<< orphan*/ ) ; 
#define  IF_THEN_ELSE 135 
 int /*<<< orphan*/  MEM_P (int /*<<< orphan*/ ) ; 
#define  PARALLEL 134 
 int PC ; 
#define  PREFETCH 133 
 int /*<<< orphan*/  REG_P (int /*<<< orphan*/ ) ; 
#define  SET 132 
 int /*<<< orphan*/  SET_DEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_SRC (int /*<<< orphan*/ ) ; 
 int SUBREG ; 
 int /*<<< orphan*/  SUBREG_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRAP_CONDITION (int /*<<< orphan*/ ) ; 
#define  TRAP_IF 131 
 int UNITS_PER_WORD ; 
#define  UNSPEC 130 
#define  UNSPEC_VOLATILE 129 
#define  USE 128 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XVECLEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int reg_overlap_mentioned_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
reg_referenced_p (rtx x, rtx body)
{
  int i;

  switch (GET_CODE (body))
    {
    case SET:
      if (reg_overlap_mentioned_p (x, SET_SRC (body)))
	return 1;

      /* If the destination is anything other than CC0, PC, a REG or a SUBREG
	 of a REG that occupies all of the REG, the insn references X if
	 it is mentioned in the destination.  */
      if (GET_CODE (SET_DEST (body)) != CC0
	  && GET_CODE (SET_DEST (body)) != PC
	  && !REG_P (SET_DEST (body))
	  && ! (GET_CODE (SET_DEST (body)) == SUBREG
		&& REG_P (SUBREG_REG (SET_DEST (body)))
		&& (((GET_MODE_SIZE (GET_MODE (SUBREG_REG (SET_DEST (body))))
		      + (UNITS_PER_WORD - 1)) / UNITS_PER_WORD)
		    == ((GET_MODE_SIZE (GET_MODE (SET_DEST (body)))
			 + (UNITS_PER_WORD - 1)) / UNITS_PER_WORD)))
	  && reg_overlap_mentioned_p (x, SET_DEST (body)))
	return 1;
      return 0;

    case ASM_OPERANDS:
      for (i = ASM_OPERANDS_INPUT_LENGTH (body) - 1; i >= 0; i--)
	if (reg_overlap_mentioned_p (x, ASM_OPERANDS_INPUT (body, i)))
	  return 1;
      return 0;

    case CALL:
    case USE:
    case IF_THEN_ELSE:
      return reg_overlap_mentioned_p (x, body);

    case TRAP_IF:
      return reg_overlap_mentioned_p (x, TRAP_CONDITION (body));

    case PREFETCH:
      return reg_overlap_mentioned_p (x, XEXP (body, 0));

    case UNSPEC:
    case UNSPEC_VOLATILE:
      for (i = XVECLEN (body, 0) - 1; i >= 0; i--)
	if (reg_overlap_mentioned_p (x, XVECEXP (body, 0, i)))
	  return 1;
      return 0;

    case PARALLEL:
      for (i = XVECLEN (body, 0) - 1; i >= 0; i--)
	if (reg_referenced_p (x, XVECEXP (body, 0, i)))
	  return 1;
      return 0;

    case CLOBBER:
      if (MEM_P (XEXP (body, 0)))
	if (reg_overlap_mentioned_p (x, XEXP (XEXP (body, 0), 0)))
	  return 1;
      return 0;

    case COND_EXEC:
      if (reg_overlap_mentioned_p (x, COND_EXEC_TEST (body)))
	return 1;
      return reg_referenced_p (x, COND_EXEC_CODE (body));

    default:
      return 0;
    }
}