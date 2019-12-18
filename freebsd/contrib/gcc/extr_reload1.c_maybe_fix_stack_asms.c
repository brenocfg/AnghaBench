#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct insn_chain {int /*<<< orphan*/  dead_or_set; int /*<<< orphan*/  live_throughout; int /*<<< orphan*/  insn; struct insn_chain* next; } ;
typedef  int /*<<< orphan*/  rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
struct TYPE_2__ {int /*<<< orphan*/  operand_loc; int /*<<< orphan*/  operand; } ;
typedef  int /*<<< orphan*/  HARD_REG_SET ;

/* Variables and functions */
 int /*<<< orphan*/  ADDRESS ; 
 int /*<<< orphan*/  AND_HARD_REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLEAR_HARD_REG_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLEAR_REGNO_REG_SET (int /*<<< orphan*/ *,int) ; 
 scalar_t__ CLOBBER ; 
 int /*<<< orphan*/  CONSTRAINT_LEN (char,char const*) ; 
 int /*<<< orphan*/  EXTRA_ADDRESS_CONSTRAINT (char,char const*) ; 
 int FIRST_PSEUDO_REGISTER ; 
 scalar_t__ GENERAL_REGS ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSN_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IOR_HARD_REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MAX_RECOG_OPERANDS ; 
 int NO_REGS ; 
 scalar_t__ PARALLEL ; 
 int /*<<< orphan*/  PATTERN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REGNO (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_CLASS_FROM_CONSTRAINT (char,char const*) ; 
 int /*<<< orphan*/  SCRATCH ; 
 int /*<<< orphan*/  SET_HARD_REG_BIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ STACK_REG_P (int /*<<< orphan*/ ) ; 
 scalar_t__ TEST_HARD_REG_BIT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int XVECLEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int asm_noperands (int /*<<< orphan*/ ) ; 
 scalar_t__ base_reg_class (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decode_asm_operands (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const**,int*) ; 
 TYPE_1__ recog_data ; 
 int /*<<< orphan*/ * reg_class_contents ; 
 scalar_t__** reg_class_subunion ; 
 struct insn_chain* reload_insn_chain ; 

__attribute__((used)) static void
maybe_fix_stack_asms (void)
{
#ifdef STACK_REGS
  const char *constraints[MAX_RECOG_OPERANDS];
  enum machine_mode operand_mode[MAX_RECOG_OPERANDS];
  struct insn_chain *chain;

  for (chain = reload_insn_chain; chain != 0; chain = chain->next)
    {
      int i, noperands;
      HARD_REG_SET clobbered, allowed;
      rtx pat;

      if (! INSN_P (chain->insn)
	  || (noperands = asm_noperands (PATTERN (chain->insn))) < 0)
	continue;
      pat = PATTERN (chain->insn);
      if (GET_CODE (pat) != PARALLEL)
	continue;

      CLEAR_HARD_REG_SET (clobbered);
      CLEAR_HARD_REG_SET (allowed);

      /* First, make a mask of all stack regs that are clobbered.  */
      for (i = 0; i < XVECLEN (pat, 0); i++)
	{
	  rtx t = XVECEXP (pat, 0, i);
	  if (GET_CODE (t) == CLOBBER && STACK_REG_P (XEXP (t, 0)))
	    SET_HARD_REG_BIT (clobbered, REGNO (XEXP (t, 0)));
	}

      /* Get the operand values and constraints out of the insn.  */
      decode_asm_operands (pat, recog_data.operand, recog_data.operand_loc,
			   constraints, operand_mode);

      /* For every operand, see what registers are allowed.  */
      for (i = 0; i < noperands; i++)
	{
	  const char *p = constraints[i];
	  /* For every alternative, we compute the class of registers allowed
	     for reloading in CLS, and merge its contents into the reg set
	     ALLOWED.  */
	  int cls = (int) NO_REGS;

	  for (;;)
	    {
	      char c = *p;

	      if (c == '\0' || c == ',' || c == '#')
		{
		  /* End of one alternative - mark the regs in the current
		     class, and reset the class.  */
		  IOR_HARD_REG_SET (allowed, reg_class_contents[cls]);
		  cls = NO_REGS;
		  p++;
		  if (c == '#')
		    do {
		      c = *p++;
		    } while (c != '\0' && c != ',');
		  if (c == '\0')
		    break;
		  continue;
		}

	      switch (c)
		{
		case '=': case '+': case '*': case '%': case '?': case '!':
		case '0': case '1': case '2': case '3': case '4': case 'm':
		case '<': case '>': case 'V': case 'o': case '&': case 'E':
		case 'F': case 's': case 'i': case 'n': case 'X': case 'I':
		case 'J': case 'K': case 'L': case 'M': case 'N': case 'O':
		case 'P':
		  break;

		case 'p':
		  cls = (int) reg_class_subunion[cls]
		      [(int) base_reg_class (VOIDmode, ADDRESS, SCRATCH)];
		  break;

		case 'g':
		case 'r':
		  cls = (int) reg_class_subunion[cls][(int) GENERAL_REGS];
		  break;

		default:
		  if (EXTRA_ADDRESS_CONSTRAINT (c, p))
		    cls = (int) reg_class_subunion[cls]
		      [(int) base_reg_class (VOIDmode, ADDRESS, SCRATCH)];
		  else
		    cls = (int) reg_class_subunion[cls]
		      [(int) REG_CLASS_FROM_CONSTRAINT (c, p)];
		}
	      p += CONSTRAINT_LEN (c, p);
	    }
	}
      /* Those of the registers which are clobbered, but allowed by the
	 constraints, must be usable as reload registers.  So clear them
	 out of the life information.  */
      AND_HARD_REG_SET (allowed, clobbered);
      for (i = 0; i < FIRST_PSEUDO_REGISTER; i++)
	if (TEST_HARD_REG_BIT (allowed, i))
	  {
	    CLEAR_REGNO_REG_SET (&chain->live_throughout, i);
	    CLEAR_REGNO_REG_SET (&chain->dead_or_set, i);
	  }
    }

#endif
}