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
typedef  int RTX_CODE ;

/* Variables and functions */
#define  ADDR_DIFF_VEC 141 
#define  ADDR_VEC 140 
 unsigned int ARG_POINTER_REGNUM ; 
#define  ASM_INPUT 139 
#define  CC0 138 
#define  CLOBBER 137 
#define  CONST 136 
#define  CONST_DOUBLE 135 
#define  CONST_INT 134 
#define  CONST_VECTOR 133 
 unsigned int FIRST_PSEUDO_REGISTER ; 
 unsigned int FRAME_POINTER_REGNUM ; 
 int GET_CODE (int /*<<< orphan*/ ) ; 
 size_t GET_MODE (int /*<<< orphan*/ ) ; 
 char* GET_RTX_FORMAT (int) ; 
 int GET_RTX_LENGTH (int) ; 
 unsigned int HARD_FRAME_POINTER_REGNUM ; 
#define  LABEL_REF 132 
 int /*<<< orphan*/  MEM_P (int /*<<< orphan*/ ) ; 
#define  PC 131 
#define  REG 130 
 unsigned int REGNO (int /*<<< orphan*/ ) ; 
#define  SET 129 
 int /*<<< orphan*/  SET_DEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_HARD_REG_BIT (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  SET_SRC (int /*<<< orphan*/ ) ; 
 unsigned int STACK_POINTER_REGNUM ; 
 int STRICT_LOW_PART ; 
 int SUBREG ; 
#define  SYMBOL_REF 128 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int,int) ; 
 int XVECLEN (int /*<<< orphan*/ ,int) ; 
 int ZERO_EXTRACT ; 
 int /*<<< orphan*/ * fixed_regs ; 
 int /*<<< orphan*/ ** hard_regno_nregs ; 
 int /*<<< orphan*/  newpat_used_regs ; 

__attribute__((used)) static void
mark_used_regs_combine (rtx x)
{
  RTX_CODE code = GET_CODE (x);
  unsigned int regno;
  int i;

  switch (code)
    {
    case LABEL_REF:
    case SYMBOL_REF:
    case CONST_INT:
    case CONST:
    case CONST_DOUBLE:
    case CONST_VECTOR:
    case PC:
    case ADDR_VEC:
    case ADDR_DIFF_VEC:
    case ASM_INPUT:
#ifdef HAVE_cc0
    /* CC0 must die in the insn after it is set, so we don't need to take
       special note of it here.  */
    case CC0:
#endif
      return;

    case CLOBBER:
      /* If we are clobbering a MEM, mark any hard registers inside the
	 address as used.  */
      if (MEM_P (XEXP (x, 0)))
	mark_used_regs_combine (XEXP (XEXP (x, 0), 0));
      return;

    case REG:
      regno = REGNO (x);
      /* A hard reg in a wide mode may really be multiple registers.
	 If so, mark all of them just like the first.  */
      if (regno < FIRST_PSEUDO_REGISTER)
	{
	  unsigned int endregno, r;

	  /* None of this applies to the stack, frame or arg pointers.  */
	  if (regno == STACK_POINTER_REGNUM
#if FRAME_POINTER_REGNUM != HARD_FRAME_POINTER_REGNUM
	      || regno == HARD_FRAME_POINTER_REGNUM
#endif
#if FRAME_POINTER_REGNUM != ARG_POINTER_REGNUM
	      || (regno == ARG_POINTER_REGNUM && fixed_regs[regno])
#endif
	      || regno == FRAME_POINTER_REGNUM)
	    return;

	  endregno = regno + hard_regno_nregs[regno][GET_MODE (x)];
	  for (r = regno; r < endregno; r++)
	    SET_HARD_REG_BIT (newpat_used_regs, r);
	}
      return;

    case SET:
      {
	/* If setting a MEM, or a SUBREG of a MEM, then note any hard regs in
	   the address.  */
	rtx testreg = SET_DEST (x);

	while (GET_CODE (testreg) == SUBREG
	       || GET_CODE (testreg) == ZERO_EXTRACT
	       || GET_CODE (testreg) == STRICT_LOW_PART)
	  testreg = XEXP (testreg, 0);

	if (MEM_P (testreg))
	  mark_used_regs_combine (XEXP (testreg, 0));

	mark_used_regs_combine (SET_SRC (x));
      }
      return;

    default:
      break;
    }

  /* Recursively scan the operands of this expression.  */

  {
    const char *fmt = GET_RTX_FORMAT (code);

    for (i = GET_RTX_LENGTH (code) - 1; i >= 0; i--)
      {
	if (fmt[i] == 'e')
	  mark_used_regs_combine (XEXP (x, i));
	else if (fmt[i] == 'E')
	  {
	    int j;

	    for (j = 0; j < XVECLEN (x, i); j++)
	      mark_used_regs_combine (XVECEXP (x, i, j));
	  }
      }
  }
}