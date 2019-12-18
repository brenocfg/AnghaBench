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
 int GET_CODE (int /*<<< orphan*/ ) ; 
#define  GEU 131 
#define  GTU 130 
#define  LEU 129 
#define  LTU 128 
 char* MIPS_BRANCH (char*,char*) ; 
 char const* mips_output_conditional_branch (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,char const*) ; 

const char *
mips_output_order_conditional_branch (rtx insn, rtx *operands, bool inverted_p)
{
  const char *branch[2];

  /* Make BRANCH[1] branch to OPERANDS[1] when the condition is true.
     Make BRANCH[0] branch on the inverse condition.  */
  switch (GET_CODE (operands[0]))
    {
      /* These cases are equivalent to comparisons against zero.  */
    case LEU:
      inverted_p = !inverted_p;
      /* Fall through.  */
    case GTU:
      branch[!inverted_p] = MIPS_BRANCH ("bne", "%2,%.,%1");
      branch[inverted_p] = MIPS_BRANCH ("beq", "%2,%.,%1");
      break;

      /* These cases are always true or always false.  */
    case LTU:
      inverted_p = !inverted_p;
      /* Fall through.  */
    case GEU:
      branch[!inverted_p] = MIPS_BRANCH ("beq", "%.,%.,%1");
      branch[inverted_p] = MIPS_BRANCH ("bne", "%.,%.,%1");
      break;

    default:
      branch[!inverted_p] = MIPS_BRANCH ("b%C0z", "%2,%1");
      branch[inverted_p] = MIPS_BRANCH ("b%N0z", "%2,%1");
      break;
    }
  return mips_output_conditional_branch (insn, operands, branch[1], branch[0]);
}