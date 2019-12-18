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
struct resources {int cc; int memory; int volatil; int /*<<< orphan*/  regs; int /*<<< orphan*/  unch_memory; } ;
typedef  int /*<<< orphan*/  rtx ;
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;
typedef  enum mark_resource_type { ____Placeholder_mark_resource_type } mark_resource_type ;

/* Variables and functions */
#define  ASM_INPUT 160 
#define  ASM_OPERANDS 159 
 int /*<<< orphan*/  ASM_OPERANDS_INPUT (int /*<<< orphan*/ ,int) ; 
 int ASM_OPERANDS_INPUT_LENGTH (int /*<<< orphan*/ ) ; 
#define  BARRIER 158 
 int CALL ; 
#define  CALL_INSN 157 
 int /*<<< orphan*/  CALL_INSN_FUNCTION_USAGE (int /*<<< orphan*/ ) ; 
#define  CC0 156 
#define  CLOBBER 155 
#define  CODE_LABEL 154 
#define  CONST 153 
#define  CONST_DOUBLE 152 
#define  CONST_INT 151 
#define  CONST_VECTOR 150 
 unsigned int FIRST_PSEUDO_REGISTER ; 
 int GET_CODE (int /*<<< orphan*/ ) ; 
 size_t GET_MODE (int /*<<< orphan*/ ) ; 
 char* GET_RTX_FORMAT (int) ; 
 int GET_RTX_LENGTH (int) ; 
#define  INSN 149 
 int /*<<< orphan*/  INSN_ANNULLED_BRANCH_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSN_FROM_TARGET_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSN_SETS_ARE_DELAYED (int /*<<< orphan*/ ) ; 
#define  JUMP_INSN 148 
#define  LABEL_REF 147 
 int MARK_SRC_DEST ; 
 int MARK_SRC_DEST_CALL ; 
#define  MEM 146 
 int /*<<< orphan*/  MEM_READONLY_P (int /*<<< orphan*/ ) ; 
 int MEM_VOLATILE_P (int /*<<< orphan*/ ) ; 
#define  NOTE 145 
 int /*<<< orphan*/  PATTERN (int /*<<< orphan*/ ) ; 
#define  PC 144 
#define  POST_DEC 143 
#define  POST_INC 142 
#define  POST_MODIFY 141 
#define  PRE_DEC 140 
#define  PRE_INC 139 
#define  PRE_MODIFY 138 
#define  REG 137 
 unsigned int REGNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SETJMP ; 
#define  SEQUENCE 136 
#define  SET 135 
 int /*<<< orphan*/  SET_DEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_HARD_REG_BIT (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  SET_HARD_REG_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_SRC (int /*<<< orphan*/ ) ; 
#define  SIGN_EXTRACT 134 
#define  SUBREG 133 
 int /*<<< orphan*/  SUBREG_REG (int /*<<< orphan*/ ) ; 
#define  SYMBOL_REF 132 
#define  TRAP_IF 131 
#define  UNSPEC_VOLATILE 130 
#define  USE 129 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int,int) ; 
 int XVECLEN (int /*<<< orphan*/ ,int) ; 
#define  ZERO_EXTRACT 128 
 int /*<<< orphan*/ * call_used_regs ; 
 int /*<<< orphan*/  find_reg_note (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/ * global_regs ; 
 int /*<<< orphan*/ ** hard_regno_nregs ; 
 unsigned int subreg_regno (int /*<<< orphan*/ ) ; 

void
mark_set_resources (rtx x, struct resources *res, int in_dest,
		    enum mark_resource_type mark_type)
{
  enum rtx_code code;
  int i, j;
  unsigned int r;
  const char *format_ptr;

 restart:

  code = GET_CODE (x);

  switch (code)
    {
    case NOTE:
    case BARRIER:
    case CODE_LABEL:
    case USE:
    case CONST_INT:
    case CONST_DOUBLE:
    case CONST_VECTOR:
    case LABEL_REF:
    case SYMBOL_REF:
    case CONST:
    case PC:
      /* These don't set any resources.  */
      return;

    case CC0:
      if (in_dest)
	res->cc = 1;
      return;

    case CALL_INSN:
      /* Called routine modifies the condition code, memory, any registers
	 that aren't saved across calls, global registers and anything
	 explicitly CLOBBERed immediately after the CALL_INSN.  */

      if (mark_type == MARK_SRC_DEST_CALL)
	{
	  rtx link;

	  res->cc = res->memory = 1;
	  for (r = 0; r < FIRST_PSEUDO_REGISTER; r++)
	    if (call_used_regs[r] || global_regs[r])
	      SET_HARD_REG_BIT (res->regs, r);

	  for (link = CALL_INSN_FUNCTION_USAGE (x);
	       link; link = XEXP (link, 1))
	    if (GET_CODE (XEXP (link, 0)) == CLOBBER)
	      mark_set_resources (SET_DEST (XEXP (link, 0)), res, 1,
				  MARK_SRC_DEST);

	  /* Check for a REG_SETJMP.  If it exists, then we must
	     assume that this call can clobber any register.  */
	  if (find_reg_note (x, REG_SETJMP, NULL))
	    SET_HARD_REG_SET (res->regs);
	}

      /* ... and also what its RTL says it modifies, if anything.  */

    case JUMP_INSN:
    case INSN:

	/* An insn consisting of just a CLOBBER (or USE) is just for flow
	   and doesn't actually do anything, so we ignore it.  */

#ifdef INSN_SETS_ARE_DELAYED
      if (mark_type != MARK_SRC_DEST_CALL
	  && INSN_SETS_ARE_DELAYED (x))
	return;
#endif

      x = PATTERN (x);
      if (GET_CODE (x) != USE && GET_CODE (x) != CLOBBER)
	goto restart;
      return;

    case SET:
      /* If the source of a SET is a CALL, this is actually done by
	 the called routine.  So only include it if we are to include the
	 effects of the calling routine.  */

      mark_set_resources (SET_DEST (x), res,
			  (mark_type == MARK_SRC_DEST_CALL
			   || GET_CODE (SET_SRC (x)) != CALL),
			  mark_type);

      mark_set_resources (SET_SRC (x), res, 0, MARK_SRC_DEST);
      return;

    case CLOBBER:
      mark_set_resources (XEXP (x, 0), res, 1, MARK_SRC_DEST);
      return;

    case SEQUENCE:
      for (i = 0; i < XVECLEN (x, 0); i++)
	if (! (INSN_ANNULLED_BRANCH_P (XVECEXP (x, 0, 0))
	       && INSN_FROM_TARGET_P (XVECEXP (x, 0, i))))
	  mark_set_resources (XVECEXP (x, 0, i), res, 0, mark_type);
      return;

    case POST_INC:
    case PRE_INC:
    case POST_DEC:
    case PRE_DEC:
      mark_set_resources (XEXP (x, 0), res, 1, MARK_SRC_DEST);
      return;

    case PRE_MODIFY:
    case POST_MODIFY:
      mark_set_resources (XEXP (x, 0), res, 1, MARK_SRC_DEST);
      mark_set_resources (XEXP (XEXP (x, 1), 0), res, 0, MARK_SRC_DEST);
      mark_set_resources (XEXP (XEXP (x, 1), 1), res, 0, MARK_SRC_DEST);
      return;

    case SIGN_EXTRACT:
    case ZERO_EXTRACT:
      mark_set_resources (XEXP (x, 0), res, in_dest, MARK_SRC_DEST);
      mark_set_resources (XEXP (x, 1), res, 0, MARK_SRC_DEST);
      mark_set_resources (XEXP (x, 2), res, 0, MARK_SRC_DEST);
      return;

    case MEM:
      if (in_dest)
	{
	  res->memory = 1;
	  res->unch_memory |= MEM_READONLY_P (x);
	  res->volatil |= MEM_VOLATILE_P (x);
	}

      mark_set_resources (XEXP (x, 0), res, 0, MARK_SRC_DEST);
      return;

    case SUBREG:
      if (in_dest)
	{
	  if (!REG_P (SUBREG_REG (x)))
	    mark_set_resources (SUBREG_REG (x), res, in_dest, mark_type);
	  else
	    {
	      unsigned int regno = subreg_regno (x);
	      unsigned int last_regno
		= regno + hard_regno_nregs[regno][GET_MODE (x)];

	      gcc_assert (last_regno <= FIRST_PSEUDO_REGISTER);
	      for (r = regno; r < last_regno; r++)
		SET_HARD_REG_BIT (res->regs, r);
	    }
	}
      return;

    case REG:
      if (in_dest)
	{
	  unsigned int regno = REGNO (x);
	  unsigned int last_regno
	    = regno + hard_regno_nregs[regno][GET_MODE (x)];

	  gcc_assert (last_regno <= FIRST_PSEUDO_REGISTER);
	  for (r = regno; r < last_regno; r++)
	    SET_HARD_REG_BIT (res->regs, r);
	}
      return;

    case UNSPEC_VOLATILE:
    case ASM_INPUT:
      /* Traditional asm's are always volatile.  */
      res->volatil = 1;
      return;

    case TRAP_IF:
      res->volatil = 1;
      break;

    case ASM_OPERANDS:
      res->volatil |= MEM_VOLATILE_P (x);

      /* For all ASM_OPERANDS, we must traverse the vector of input operands.
	 We can not just fall through here since then we would be confused
	 by the ASM_INPUT rtx inside ASM_OPERANDS, which do not indicate
	 traditional asms unlike their normal usage.  */

      for (i = 0; i < ASM_OPERANDS_INPUT_LENGTH (x); i++)
	mark_set_resources (ASM_OPERANDS_INPUT (x, i), res, in_dest,
			    MARK_SRC_DEST);
      return;

    default:
      break;
    }

  /* Process each sub-expression and flag what it needs.  */
  format_ptr = GET_RTX_FORMAT (code);
  for (i = 0; i < GET_RTX_LENGTH (code); i++)
    switch (*format_ptr++)
      {
      case 'e':
	mark_set_resources (XEXP (x, i), res, in_dest, mark_type);
	break;

      case 'E':
	for (j = 0; j < XVECLEN (x, i); j++)
	  mark_set_resources (XVECEXP (x, i, j), res, in_dest, mark_type);
	break;
      }
}