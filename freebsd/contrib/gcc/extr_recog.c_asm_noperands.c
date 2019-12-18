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
#define  ASM_OPERANDS 130 
 int ASM_OPERANDS_INPUT_LENGTH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASM_OPERANDS_INPUT_VEC (int /*<<< orphan*/ ) ; 
 int const CLOBBER ; 
 int const GET_CODE (int /*<<< orphan*/ ) ; 
#define  PARALLEL 129 
#define  SET 128 
 int /*<<< orphan*/  SET_SRC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int XVECLEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
asm_noperands (rtx body)
{
  switch (GET_CODE (body))
    {
    case ASM_OPERANDS:
      /* No output operands: return number of input operands.  */
      return ASM_OPERANDS_INPUT_LENGTH (body);
    case SET:
      if (GET_CODE (SET_SRC (body)) == ASM_OPERANDS)
	/* Single output operand: BODY is (set OUTPUT (asm_operands ...)).  */
	return ASM_OPERANDS_INPUT_LENGTH (SET_SRC (body)) + 1;
      else
	return -1;
    case PARALLEL:
      if (GET_CODE (XVECEXP (body, 0, 0)) == SET
	  && GET_CODE (SET_SRC (XVECEXP (body, 0, 0))) == ASM_OPERANDS)
	{
	  /* Multiple output operands, or 1 output plus some clobbers:
	     body is [(set OUTPUT (asm_operands ...))... (clobber (reg ...))...].  */
	  int i;
	  int n_sets;

	  /* Count backwards through CLOBBERs to determine number of SETs.  */
	  for (i = XVECLEN (body, 0); i > 0; i--)
	    {
	      if (GET_CODE (XVECEXP (body, 0, i - 1)) == SET)
		break;
	      if (GET_CODE (XVECEXP (body, 0, i - 1)) != CLOBBER)
		return -1;
	    }

	  /* N_SETS is now number of output operands.  */
	  n_sets = i;

	  /* Verify that all the SETs we have
	     came from a single original asm_operands insn
	     (so that invalid combinations are blocked).  */
	  for (i = 0; i < n_sets; i++)
	    {
	      rtx elt = XVECEXP (body, 0, i);
	      if (GET_CODE (elt) != SET)
		return -1;
	      if (GET_CODE (SET_SRC (elt)) != ASM_OPERANDS)
		return -1;
	      /* If these ASM_OPERANDS rtx's came from different original insns
	         then they aren't allowed together.  */
	      if (ASM_OPERANDS_INPUT_VEC (SET_SRC (elt))
		  != ASM_OPERANDS_INPUT_VEC (SET_SRC (XVECEXP (body, 0, 0))))
		return -1;
	    }
	  return (ASM_OPERANDS_INPUT_LENGTH (SET_SRC (XVECEXP (body, 0, 0)))
		  + n_sets);
	}
      else if (GET_CODE (XVECEXP (body, 0, 0)) == ASM_OPERANDS)
	{
	  /* 0 outputs, but some clobbers:
	     body is [(asm_operands ...) (clobber (reg ...))...].  */
	  int i;

	  /* Make sure all the other parallel things really are clobbers.  */
	  for (i = XVECLEN (body, 0) - 1; i > 0; i--)
	    if (GET_CODE (XVECEXP (body, 0, i)) != CLOBBER)
	      return -1;

	  return ASM_OPERANDS_INPUT_LENGTH (XVECEXP (body, 0, 0));
	}
      else
	return -1;
    default:
      return -1;
    }
}