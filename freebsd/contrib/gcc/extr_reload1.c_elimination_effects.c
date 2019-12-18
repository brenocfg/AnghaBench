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
struct elim_table {int ref_outside_mem; int offset; int /*<<< orphan*/  can_eliminate; int /*<<< orphan*/  to_rtx; int /*<<< orphan*/  from_rtx; } ;
typedef  int /*<<< orphan*/  rtx ;
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
#define  ABS 171 
#define  ADDR_DIFF_VEC 170 
#define  ADDR_VEC 169 
#define  ASM_INPUT 168 
#define  BSWAP 167 
#define  CC0 166 
#define  CLOBBER 165 
#define  CLZ 164 
#define  CODE_LABEL 163 
#define  CONST 162 
 int /*<<< orphan*/  CONSTANT_P (int /*<<< orphan*/ ) ; 
#define  CONST_DOUBLE 161 
#define  CONST_INT 160 
#define  CONST_VECTOR 159 
#define  CTZ 158 
#define  FFS 157 
 int FIRST_PSEUDO_REGISTER ; 
#define  FIX 156 
#define  FLOAT 155 
#define  FLOAT_EXTEND 154 
#define  FLOAT_TRUNCATE 153 
 int const GET_CODE (int /*<<< orphan*/ ) ; 
 int GET_MODE (int /*<<< orphan*/ ) ; 
 int GET_MODE_SIZE (int) ; 
 char* GET_RTX_FORMAT (int) ; 
 int GET_RTX_LENGTH (int) ; 
 int INTVAL (int /*<<< orphan*/ ) ; 
#define  MEM 152 
#define  NEG 151 
#define  NOT 150 
 size_t NUM_ELIMINABLE_REGS ; 
#define  PARITY 149 
#define  PC 148 
 int const PLUS ; 
#define  POPCOUNT 147 
#define  POST_DEC 146 
#define  POST_INC 145 
#define  POST_MODIFY 144 
#define  PRE_DEC 143 
#define  PRE_INC 142 
#define  PRE_MODIFY 141 
 int PUSH_ROUNDING (int) ; 
#define  REG 140 
 size_t REGNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_P (int /*<<< orphan*/ ) ; 
#define  RETURN 139 
#define  SET 138 
 int /*<<< orphan*/  SET_DEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_SRC (int /*<<< orphan*/ ) ; 
#define  SIGN_EXTEND 137 
#define  SQRT 136 
#define  STRICT_LOW_PART 135 
#define  SUBREG 134 
 int /*<<< orphan*/  SUBREG_REG (int /*<<< orphan*/ ) ; 
#define  SYMBOL_REF 133 
#define  TRUNCATE 132 
#define  UNSIGNED_FIX 131 
#define  UNSIGNED_FLOAT 130 
#define  USE 129 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int,int) ; 
 int XVECLEN (int /*<<< orphan*/ ,int) ; 
#define  ZERO_EXTEND 128 
 int /*<<< orphan*/  function_invariant_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hard_frame_pointer_rtx ; 
 struct elim_table* reg_eliminate ; 
 int /*<<< orphan*/ * reg_equiv_constant ; 
 int /*<<< orphan*/ * reg_equiv_memory_loc ; 
 int /*<<< orphan*/ * reg_renumber ; 
 int /*<<< orphan*/  stack_pointer_rtx ; 

__attribute__((used)) static void
elimination_effects (rtx x, enum machine_mode mem_mode)
{
  enum rtx_code code = GET_CODE (x);
  struct elim_table *ep;
  int regno;
  int i, j;
  const char *fmt;

  switch (code)
    {
    case CONST_INT:
    case CONST_DOUBLE:
    case CONST_VECTOR:
    case CONST:
    case SYMBOL_REF:
    case CODE_LABEL:
    case PC:
    case CC0:
    case ASM_INPUT:
    case ADDR_VEC:
    case ADDR_DIFF_VEC:
    case RETURN:
      return;

    case REG:
      regno = REGNO (x);

      /* First handle the case where we encounter a bare register that
	 is eliminable.  Replace it with a PLUS.  */
      if (regno < FIRST_PSEUDO_REGISTER)
	{
	  for (ep = reg_eliminate; ep < &reg_eliminate[NUM_ELIMINABLE_REGS];
	       ep++)
	    if (ep->from_rtx == x && ep->can_eliminate)
	      {
		if (! mem_mode)
		  ep->ref_outside_mem = 1;
		return;
	      }

	}
      else if (reg_renumber[regno] < 0 && reg_equiv_constant
	       && reg_equiv_constant[regno]
	       && ! function_invariant_p (reg_equiv_constant[regno]))
	elimination_effects (reg_equiv_constant[regno], mem_mode);
      return;

    case PRE_INC:
    case POST_INC:
    case PRE_DEC:
    case POST_DEC:
    case POST_MODIFY:
    case PRE_MODIFY:
      for (ep = reg_eliminate; ep < &reg_eliminate[NUM_ELIMINABLE_REGS]; ep++)
	if (ep->to_rtx == XEXP (x, 0))
	  {
	    int size = GET_MODE_SIZE (mem_mode);

	    /* If more bytes than MEM_MODE are pushed, account for them.  */
#ifdef PUSH_ROUNDING
	    if (ep->to_rtx == stack_pointer_rtx)
	      size = PUSH_ROUNDING (size);
#endif
	    if (code == PRE_DEC || code == POST_DEC)
	      ep->offset += size;
	    else if (code == PRE_INC || code == POST_INC)
	      ep->offset -= size;
	    else if ((code == PRE_MODIFY || code == POST_MODIFY)
		     && GET_CODE (XEXP (x, 1)) == PLUS
		     && XEXP (x, 0) == XEXP (XEXP (x, 1), 0)
		     && CONSTANT_P (XEXP (XEXP (x, 1), 1)))
	      ep->offset -= INTVAL (XEXP (XEXP (x, 1), 1));
	  }

      /* These two aren't unary operators.  */
      if (code == POST_MODIFY || code == PRE_MODIFY)
	break;

      /* Fall through to generic unary operation case.  */
    case STRICT_LOW_PART:
    case NEG:          case NOT:
    case SIGN_EXTEND:  case ZERO_EXTEND:
    case TRUNCATE:     case FLOAT_EXTEND: case FLOAT_TRUNCATE:
    case FLOAT:        case FIX:
    case UNSIGNED_FIX: case UNSIGNED_FLOAT:
    case ABS:
    case SQRT:
    case FFS:
    case CLZ:
    case CTZ:
    case POPCOUNT:
    case PARITY:
    case BSWAP:
      elimination_effects (XEXP (x, 0), mem_mode);
      return;

    case SUBREG:
      if (REG_P (SUBREG_REG (x))
	  && (GET_MODE_SIZE (GET_MODE (x))
	      <= GET_MODE_SIZE (GET_MODE (SUBREG_REG (x))))
	  && reg_equiv_memory_loc != 0
	  && reg_equiv_memory_loc[REGNO (SUBREG_REG (x))] != 0)
	return;

      elimination_effects (SUBREG_REG (x), mem_mode);
      return;

    case USE:
      /* If using a register that is the source of an eliminate we still
	 think can be performed, note it cannot be performed since we don't
	 know how this register is used.  */
      for (ep = reg_eliminate; ep < &reg_eliminate[NUM_ELIMINABLE_REGS]; ep++)
	if (ep->from_rtx == XEXP (x, 0))
	  ep->can_eliminate = 0;

      elimination_effects (XEXP (x, 0), mem_mode);
      return;

    case CLOBBER:
      /* If clobbering a register that is the replacement register for an
	 elimination we still think can be performed, note that it cannot
	 be performed.  Otherwise, we need not be concerned about it.  */
      for (ep = reg_eliminate; ep < &reg_eliminate[NUM_ELIMINABLE_REGS]; ep++)
	if (ep->to_rtx == XEXP (x, 0))
	  ep->can_eliminate = 0;

      elimination_effects (XEXP (x, 0), mem_mode);
      return;

    case SET:
      /* Check for setting a register that we know about.  */
      if (REG_P (SET_DEST (x)))
	{
	  /* See if this is setting the replacement register for an
	     elimination.

	     If DEST is the hard frame pointer, we do nothing because we
	     assume that all assignments to the frame pointer are for
	     non-local gotos and are being done at a time when they are valid
	     and do not disturb anything else.  Some machines want to
	     eliminate a fake argument pointer (or even a fake frame pointer)
	     with either the real frame or the stack pointer.  Assignments to
	     the hard frame pointer must not prevent this elimination.  */

	  for (ep = reg_eliminate; ep < &reg_eliminate[NUM_ELIMINABLE_REGS];
	       ep++)
	    if (ep->to_rtx == SET_DEST (x)
		&& SET_DEST (x) != hard_frame_pointer_rtx)
	      {
		/* If it is being incremented, adjust the offset.  Otherwise,
		   this elimination can't be done.  */
		rtx src = SET_SRC (x);

		if (GET_CODE (src) == PLUS
		    && XEXP (src, 0) == SET_DEST (x)
		    && GET_CODE (XEXP (src, 1)) == CONST_INT)
		  ep->offset -= INTVAL (XEXP (src, 1));
		else
		  ep->can_eliminate = 0;
	      }
	}

      elimination_effects (SET_DEST (x), 0);
      elimination_effects (SET_SRC (x), 0);
      return;

    case MEM:
      /* Our only special processing is to pass the mode of the MEM to our
	 recursive call.  */
      elimination_effects (XEXP (x, 0), GET_MODE (x));
      return;

    default:
      break;
    }

  fmt = GET_RTX_FORMAT (code);
  for (i = 0; i < GET_RTX_LENGTH (code); i++, fmt++)
    {
      if (*fmt == 'e')
	elimination_effects (XEXP (x, i), mem_mode);
      else if (*fmt == 'E')
	for (j = 0; j < XVECLEN (x, i); j++)
	  elimination_effects (XVECEXP (x, i, j), mem_mode);
    }
}