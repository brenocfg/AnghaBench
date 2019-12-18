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
typedef  scalar_t__ rtx ;

/* Variables and functions */
#define  ASHIFT 130 
 int GET_CODE (scalar_t__) ; 
#define  LO_SUM 129 
#define  PLUS 128 
 int SET ; 
 scalar_t__ SET_DEST (scalar_t__) ; 
 scalar_t__ SET_SRC (scalar_t__) ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 int /*<<< orphan*/  asm_out_file ; 
 scalar_t__ const1_rtx ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  output_asm_insn (char*,scalar_t__*) ; 

__attribute__((used)) static void
output_restore (rtx pat)
{
  rtx operands[3];

  if (! pat)
    {
      fputs ("\t restore\n", asm_out_file);
      return;
    }

  gcc_assert (GET_CODE (pat) == SET);

  operands[0] = SET_DEST (pat);
  pat = SET_SRC (pat);

  switch (GET_CODE (pat))
    {
      case PLUS:
	operands[1] = XEXP (pat, 0);
	operands[2] = XEXP (pat, 1);
	output_asm_insn (" restore %r1, %2, %Y0", operands);
	break;
      case LO_SUM:
	operands[1] = XEXP (pat, 0);
	operands[2] = XEXP (pat, 1);
	output_asm_insn (" restore %r1, %%lo(%a2), %Y0", operands);
	break;
      case ASHIFT:
	operands[1] = XEXP (pat, 0);
	gcc_assert (XEXP (pat, 1) == const1_rtx);
	output_asm_insn (" restore %r1, %r1, %Y0", operands);
	break;
      default:
	operands[1] = pat;
	output_asm_insn (" restore %%g0, %1, %Y0", operands);
	break;
    }
}