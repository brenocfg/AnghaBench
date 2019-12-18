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
 int /*<<< orphan*/  REGNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  output_asm_insn (char*,int /*<<< orphan*/ *) ; 

const char *
thumb_output_move_mem_multiple (int n, rtx *operands)
{
  rtx tmp;

  switch (n)
    {
    case 2:
      if (REGNO (operands[4]) > REGNO (operands[5]))
	{
	  tmp = operands[4];
	  operands[4] = operands[5];
	  operands[5] = tmp;
	}
      output_asm_insn ("ldmia\t%1!, {%4, %5}", operands);
      output_asm_insn ("stmia\t%0!, {%4, %5}", operands);
      break;

    case 3:
      if (REGNO (operands[4]) > REGNO (operands[5]))
	{
	  tmp = operands[4];
	  operands[4] = operands[5];
	  operands[5] = tmp;
	}
      if (REGNO (operands[5]) > REGNO (operands[6]))
	{
	  tmp = operands[5];
	  operands[5] = operands[6];
	  operands[6] = tmp;
	}
      if (REGNO (operands[4]) > REGNO (operands[5]))
	{
	  tmp = operands[4];
	  operands[4] = operands[5];
	  operands[5] = tmp;
	}

      output_asm_insn ("ldmia\t%1!, {%4, %5, %6}", operands);
      output_asm_insn ("stmia\t%0!, {%4, %5, %6}", operands);
      break;

    default:
      gcc_unreachable ();
    }

  return "";
}