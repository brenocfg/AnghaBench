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
struct resources {int unch_memory; int memory; int volatil; int cc; int /*<<< orphan*/  regs; } ;
typedef  int /*<<< orphan*/  rtx ;
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;

/* Variables and functions */
#define  ASM_INPUT 148 
#define  ASM_OPERANDS 147 
 int /*<<< orphan*/  ASM_OPERANDS_INPUT (int /*<<< orphan*/ ,int) ; 
 int ASM_OPERANDS_INPUT_LENGTH (int /*<<< orphan*/ ) ; 
#define  CALL 146 
#define  CALL_INSN 145 
 int /*<<< orphan*/  CALL_INSN_FUNCTION_USAGE (int /*<<< orphan*/ ) ; 
#define  CC0 144 
#define  CLOBBER 143 
#define  CONST 142 
#define  CONST_DOUBLE 141 
#define  CONST_INT 140 
#define  CONST_VECTOR 139 
 unsigned int FIRST_PSEUDO_REGISTER ; 
 int FRAME_POINTER_REGNUM ; 
 int const GET_CODE (int /*<<< orphan*/ ) ; 
 size_t GET_MODE (int /*<<< orphan*/ ) ; 
 char* GET_RTX_FORMAT (int) ; 
 int GET_RTX_LENGTH (int) ; 
 int HARD_FRAME_POINTER_REGNUM ; 
#define  INSN 138 
 int /*<<< orphan*/  INSN_REFERENCES_ARE_DELAYED (int /*<<< orphan*/ ) ; 
#define  JUMP_INSN 137 
#define  LABEL_REF 136 
#define  MEM 135 
 int /*<<< orphan*/  MEM_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEM_READONLY_P (int /*<<< orphan*/ ) ; 
 int MEM_VOLATILE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NEXT_INSN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PATTERN (int /*<<< orphan*/ ) ; 
#define  PC 134 
 int /*<<< orphan*/  PREV_INSN (int /*<<< orphan*/ ) ; 
#define  REG 133 
 unsigned int REGNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SETJMP ; 
 int const SEQUENCE ; 
#define  SET 132 
 int /*<<< orphan*/  SET_DEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_HARD_REG_BIT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SET_HARD_REG_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_SRC (int /*<<< orphan*/ ) ; 
 int STACK_POINTER_REGNUM ; 
 int const STRICT_LOW_PART ; 
#define  SUBREG 131 
 int /*<<< orphan*/  SUBREG_REG (int /*<<< orphan*/ ) ; 
#define  SYMBOL_REF 130 
#define  TRAP_IF 129 
#define  UNSPEC_VOLATILE 128 
 int const USE ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int,int) ; 
 int XVECLEN (int /*<<< orphan*/ ,int) ; 
 int const ZERO_EXTRACT ; 
 int /*<<< orphan*/  find_reg_note (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  frame_pointer_needed ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/ * global_regs ; 
 int /*<<< orphan*/ ** hard_regno_nregs ; 
 int /*<<< orphan*/  rtx_equal_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int subreg_regno (int /*<<< orphan*/ ) ; 

void
mark_referenced_resources (rtx x, struct resources *res,
			   int include_delayed_effects)
{
  enum rtx_code code = GET_CODE (x);
  int i, j;
  unsigned int r;
  const char *format_ptr;

  /* Handle leaf items for which we set resource flags.  Also, special-case
     CALL, SET and CLOBBER operators.  */
  switch (code)
    {
    case CONST:
    case CONST_INT:
    case CONST_DOUBLE:
    case CONST_VECTOR:
    case PC:
    case SYMBOL_REF:
    case LABEL_REF:
      return;

    case SUBREG:
      if (!REG_P (SUBREG_REG (x)))
	mark_referenced_resources (SUBREG_REG (x), res, 0);
      else
	{
	  unsigned int regno = subreg_regno (x);
	  unsigned int last_regno
	    = regno + hard_regno_nregs[regno][GET_MODE (x)];

	  gcc_assert (last_regno <= FIRST_PSEUDO_REGISTER);
	  for (r = regno; r < last_regno; r++)
	    SET_HARD_REG_BIT (res->regs, r);
	}
      return;

    case REG:
	{
	  unsigned int regno = REGNO (x);
	  unsigned int last_regno
	    = regno + hard_regno_nregs[regno][GET_MODE (x)];

	  gcc_assert (last_regno <= FIRST_PSEUDO_REGISTER);
	  for (r = regno; r < last_regno; r++)
	    SET_HARD_REG_BIT (res->regs, r);
	}
      return;

    case MEM:
      /* If this memory shouldn't change, it really isn't referencing
	 memory.  */
      if (MEM_READONLY_P (x))
	res->unch_memory = 1;
      else
	res->memory = 1;
      res->volatil |= MEM_VOLATILE_P (x);

      /* Mark registers used to access memory.  */
      mark_referenced_resources (XEXP (x, 0), res, 0);
      return;

    case CC0:
      res->cc = 1;
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
	mark_referenced_resources (ASM_OPERANDS_INPUT (x, i), res, 0);
      return;

    case CALL:
      /* The first operand will be a (MEM (xxx)) but doesn't really reference
	 memory.  The second operand may be referenced, though.  */
      mark_referenced_resources (XEXP (XEXP (x, 0), 0), res, 0);
      mark_referenced_resources (XEXP (x, 1), res, 0);
      return;

    case SET:
      /* Usually, the first operand of SET is set, not referenced.  But
	 registers used to access memory are referenced.  SET_DEST is
	 also referenced if it is a ZERO_EXTRACT.  */

      mark_referenced_resources (SET_SRC (x), res, 0);

      x = SET_DEST (x);
      if (GET_CODE (x) == ZERO_EXTRACT
	  || GET_CODE (x) == STRICT_LOW_PART)
	mark_referenced_resources (x, res, 0);
      else if (GET_CODE (x) == SUBREG)
	x = SUBREG_REG (x);
      if (MEM_P (x))
	mark_referenced_resources (XEXP (x, 0), res, 0);
      return;

    case CLOBBER:
      return;

    case CALL_INSN:
      if (include_delayed_effects)
	{
	  /* A CALL references memory, the frame pointer if it exists, the
	     stack pointer, any global registers and any registers given in
	     USE insns immediately in front of the CALL.

	     However, we may have moved some of the parameter loading insns
	     into the delay slot of this CALL.  If so, the USE's for them
	     don't count and should be skipped.  */
	  rtx insn = PREV_INSN (x);
	  rtx sequence = 0;
	  int seq_size = 0;
	  int i;

	  /* If we are part of a delay slot sequence, point at the SEQUENCE.  */
	  if (NEXT_INSN (insn) != x)
	    {
	      sequence = PATTERN (NEXT_INSN (insn));
	      seq_size = XVECLEN (sequence, 0);
	      gcc_assert (GET_CODE (sequence) == SEQUENCE);
	    }

	  res->memory = 1;
	  SET_HARD_REG_BIT (res->regs, STACK_POINTER_REGNUM);
	  if (frame_pointer_needed)
	    {
	      SET_HARD_REG_BIT (res->regs, FRAME_POINTER_REGNUM);
#if FRAME_POINTER_REGNUM != HARD_FRAME_POINTER_REGNUM
	      SET_HARD_REG_BIT (res->regs, HARD_FRAME_POINTER_REGNUM);
#endif
	    }

	  for (i = 0; i < FIRST_PSEUDO_REGISTER; i++)
	    if (global_regs[i])
	      SET_HARD_REG_BIT (res->regs, i);

	  /* Check for a REG_SETJMP.  If it exists, then we must
	     assume that this call can need any register.

	     This is done to be more conservative about how we handle setjmp.
	     We assume that they both use and set all registers.  Using all
	     registers ensures that a register will not be considered dead
	     just because it crosses a setjmp call.  A register should be
	     considered dead only if the setjmp call returns nonzero.  */
	  if (find_reg_note (x, REG_SETJMP, NULL))
	    SET_HARD_REG_SET (res->regs);

	  {
	    rtx link;

	    for (link = CALL_INSN_FUNCTION_USAGE (x);
		 link;
		 link = XEXP (link, 1))
	      if (GET_CODE (XEXP (link, 0)) == USE)
		{
		  for (i = 1; i < seq_size; i++)
		    {
		      rtx slot_pat = PATTERN (XVECEXP (sequence, 0, i));
		      if (GET_CODE (slot_pat) == SET
			  && rtx_equal_p (SET_DEST (slot_pat),
					  XEXP (XEXP (link, 0), 0)))
			break;
		    }
		  if (i >= seq_size)
		    mark_referenced_resources (XEXP (XEXP (link, 0), 0),
					       res, 0);
		}
	  }
	}

      /* ... fall through to other INSN processing ...  */

    case INSN:
    case JUMP_INSN:

#ifdef INSN_REFERENCES_ARE_DELAYED
      if (! include_delayed_effects
	  && INSN_REFERENCES_ARE_DELAYED (x))
	return;
#endif

      /* No special processing, just speed up.  */
      mark_referenced_resources (PATTERN (x), res, include_delayed_effects);
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
	mark_referenced_resources (XEXP (x, i), res, include_delayed_effects);
	break;

      case 'E':
	for (j = 0; j < XVECLEN (x, i); j++)
	  mark_referenced_resources (XVECEXP (x, i, j), res,
				     include_delayed_effects);
	break;
      }
}