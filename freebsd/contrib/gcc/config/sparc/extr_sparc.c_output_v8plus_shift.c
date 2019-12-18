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
 scalar_t__ CONST_INT ; 
 int /*<<< orphan*/  GEN_INT (int) ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int INTVAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_asm_insn (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ sparc_check_64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char const* strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int which_alternative ; 

const char *
output_v8plus_shift (rtx *operands, rtx insn, const char *opcode)
{
  static char asm_code[60];

  /* The scratch register is only required when the destination
     register is not a 64-bit global or out register.  */
  if (which_alternative != 2)
    operands[3] = operands[0];

  /* We can only shift by constants <= 63. */
  if (GET_CODE (operands[2]) == CONST_INT)
    operands[2] = GEN_INT (INTVAL (operands[2]) & 0x3f);

  if (GET_CODE (operands[1]) == CONST_INT)
    {
      output_asm_insn ("mov\t%1, %3", operands);
    }
  else
    {
      output_asm_insn ("sllx\t%H1, 32, %3", operands);
      if (sparc_check_64 (operands[1], insn) <= 0)
	output_asm_insn ("srl\t%L1, 0, %L1", operands);
      output_asm_insn ("or\t%L1, %3, %3", operands);
    }

  strcpy(asm_code, opcode);

  if (which_alternative != 2)
    return strcat (asm_code, "\t%0, %2, %L0\n\tsrlx\t%L0, 32, %H0");
  else
    return strcat (asm_code, "\t%3, %2, %3\n\tsrlx\t%3, 32, %H0\n\tmov\t%3, %L0");
}