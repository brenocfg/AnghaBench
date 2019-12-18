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
typedef  int /*<<< orphan*/  HOST_WIDE_INT ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ASM_OUTPUT_SKIP (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Pmode ; 
 scalar_t__ TARGET_64BIT ; 
 int TRAMPOLINE_SIZE ; 
 int /*<<< orphan*/  gen_rtx_REG (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  output_asm_insn (char*,int /*<<< orphan*/ *) ; 

void
s390_trampoline_template (FILE *file)
{
  rtx op[2];
  op[0] = gen_rtx_REG (Pmode, 0);
  op[1] = gen_rtx_REG (Pmode, 1);

  if (TARGET_64BIT)
    {
      output_asm_insn ("basr\t%1,0", op);
      output_asm_insn ("lmg\t%0,%1,14(%1)", op);
      output_asm_insn ("br\t%1", op);
      ASM_OUTPUT_SKIP (file, (HOST_WIDE_INT)(TRAMPOLINE_SIZE - 10));
    }
  else
    {
      output_asm_insn ("basr\t%1,0", op);
      output_asm_insn ("lm\t%0,%1,6(%1)", op);
      output_asm_insn ("br\t%1", op);
      ASM_OUTPUT_SKIP (file, (HOST_WIDE_INT)(TRAMPOLINE_SIZE - 8));
    }
}