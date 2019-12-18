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
 scalar_t__ GENERATE_DIVIDE_TRAPS ; 
 scalar_t__ TARGET_CHECK_ZERO_DIV ; 
 scalar_t__ TARGET_FIX_R4000 ; 
 scalar_t__ TARGET_FIX_R4400 ; 
 scalar_t__ TARGET_MIPS16 ; 
 int /*<<< orphan*/  output_asm_insn (char const*,int /*<<< orphan*/ *) ; 

const char *
mips_output_division (const char *division, rtx *operands)
{
  const char *s;

  s = division;
  if (TARGET_FIX_R4000 || TARGET_FIX_R4400)
    {
      output_asm_insn (s, operands);
      s = "nop";
    }
  if (TARGET_CHECK_ZERO_DIV)
    {
      if (TARGET_MIPS16)
	{
	  output_asm_insn (s, operands);
	  s = "bnez\t%2,1f\n\tbreak\t7\n1:";
	}
      else if (GENERATE_DIVIDE_TRAPS)
        {
	  output_asm_insn (s, operands);
	  s = "teq\t%2,%.,7";
        }
      else
	{
	  output_asm_insn ("%(bne\t%2,%.,1f", operands);
	  output_asm_insn (s, operands);
	  s = "break\t7%)\n1:";
	}
    }
  return s;
}