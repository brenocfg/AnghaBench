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
typedef  scalar_t__ tree ;
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 char* ASM_COMMENT_START ; 
 int ORIGINAL_REGNO (int /*<<< orphan*/ ) ; 
 int REGNO (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asm_out_file ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ get_mem_expr_from_op (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  print_mem_expr (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
output_asm_operand_names (rtx *operands, int *oporder, int nops)
{
  int wrote = 0;
  int i;

  for (i = 0; i < nops; i++)
    {
      int addressp;
      rtx op = operands[oporder[i]];
      tree expr = get_mem_expr_from_op (op, &addressp);

      fprintf (asm_out_file, "%c%s",
	       wrote ? ',' : '\t', wrote ? "" : ASM_COMMENT_START);
      wrote = 1;
      if (expr)
	{
	  fprintf (asm_out_file, "%s",
		   addressp ? "*" : "");
	  print_mem_expr (asm_out_file, expr);
	  wrote = 1;
	}
      else if (REG_P (op) && ORIGINAL_REGNO (op)
	       && ORIGINAL_REGNO (op) != REGNO (op))
	fprintf (asm_out_file, " tmp%i", ORIGINAL_REGNO (op));
    }
}