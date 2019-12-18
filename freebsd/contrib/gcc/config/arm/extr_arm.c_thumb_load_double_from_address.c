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
#define  CONST 131 
 int /*<<< orphan*/  CONSTANT_P (int /*<<< orphan*/ ) ; 
 int const GET_CODE (int /*<<< orphan*/ ) ; 
#define  LABEL_REF 130 
 int const MEM ; 
#define  PLUS 129 
#define  REG 128 
 int REGNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SImode ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  adjust_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  asm_fprintf (int /*<<< orphan*/ ,char*,int,int,...) ; 
 int /*<<< orphan*/  asm_out_file ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  output_asm_insn (char*,int /*<<< orphan*/ *) ; 

const char *
thumb_load_double_from_address (rtx *operands)
{
  rtx addr;
  rtx base;
  rtx offset;
  rtx arg1;
  rtx arg2;

  gcc_assert (GET_CODE (operands[0]) == REG);
  gcc_assert (GET_CODE (operands[1]) == MEM);

  /* Get the memory address.  */
  addr = XEXP (operands[1], 0);

  /* Work out how the memory address is computed.  */
  switch (GET_CODE (addr))
    {
    case REG:
      operands[2] = adjust_address (operands[1], SImode, 4);

      if (REGNO (operands[0]) == REGNO (addr))
	{
	  output_asm_insn ("ldr\t%H0, %2", operands);
	  output_asm_insn ("ldr\t%0, %1", operands);
	}
      else
	{
	  output_asm_insn ("ldr\t%0, %1", operands);
	  output_asm_insn ("ldr\t%H0, %2", operands);
	}
      break;

    case CONST:
      /* Compute <address> + 4 for the high order load.  */
      operands[2] = adjust_address (operands[1], SImode, 4);

      output_asm_insn ("ldr\t%0, %1", operands);
      output_asm_insn ("ldr\t%H0, %2", operands);
      break;

    case PLUS:
      arg1   = XEXP (addr, 0);
      arg2   = XEXP (addr, 1);

      if (CONSTANT_P (arg1))
	base = arg2, offset = arg1;
      else
	base = arg1, offset = arg2;

      gcc_assert (GET_CODE (base) == REG);

      /* Catch the case of <address> = <reg> + <reg> */
      if (GET_CODE (offset) == REG)
	{
	  int reg_offset = REGNO (offset);
	  int reg_base   = REGNO (base);
	  int reg_dest   = REGNO (operands[0]);

	  /* Add the base and offset registers together into the
             higher destination register.  */
	  asm_fprintf (asm_out_file, "\tadd\t%r, %r, %r",
		       reg_dest + 1, reg_base, reg_offset);

	  /* Load the lower destination register from the address in
             the higher destination register.  */
	  asm_fprintf (asm_out_file, "\tldr\t%r, [%r, #0]",
		       reg_dest, reg_dest + 1);

	  /* Load the higher destination register from its own address
             plus 4.  */
	  asm_fprintf (asm_out_file, "\tldr\t%r, [%r, #4]",
		       reg_dest + 1, reg_dest + 1);
	}
      else
	{
	  /* Compute <address> + 4 for the high order load.  */
	  operands[2] = adjust_address (operands[1], SImode, 4);

	  /* If the computed address is held in the low order register
	     then load the high order register first, otherwise always
	     load the low order register first.  */
	  if (REGNO (operands[0]) == REGNO (base))
	    {
	      output_asm_insn ("ldr\t%H0, %2", operands);
	      output_asm_insn ("ldr\t%0, %1", operands);
	    }
	  else
	    {
	      output_asm_insn ("ldr\t%0, %1", operands);
	      output_asm_insn ("ldr\t%H0, %2", operands);
	    }
	}
      break;

    case LABEL_REF:
      /* With no registers to worry about we can just load the value
         directly.  */
      operands[2] = adjust_address (operands[1], SImode, 4);

      output_asm_insn ("ldr\t%H0, %2", operands);
      output_asm_insn ("ldr\t%0, %1", operands);
      break;

    default:
      gcc_unreachable ();
    }

  return "";
}