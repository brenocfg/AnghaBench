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

/* Variables and functions */
 char* ADVANCE_CYCLE_VALUE_NAME ; 
 char* DFA_INSN_CODE_FUNC_NAME ; 
 char* INSN_PARAMETER_NAME ; 
 char* INTERNAL_INSN_CODE_NAME ; 
 char* INTERNAL_MIN_ISSUE_DELAY_FUNC_NAME ; 
 char* MIN_ISSUE_DELAY_FUNC_NAME ; 
 char* STATE_NAME ; 
 char* STATE_TYPE_NAME ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  output_file ; 

__attribute__((used)) static void
output_min_issue_delay_func (void)
{
  fprintf (output_file, "int\n%s (%s %s, rtx %s)\n",
	   MIN_ISSUE_DELAY_FUNC_NAME, STATE_TYPE_NAME, STATE_NAME,
	   INSN_PARAMETER_NAME);
  fprintf (output_file, "{\n  int %s;\n", INTERNAL_INSN_CODE_NAME);
  fprintf (output_file, "\n  if (%s != 0)\n    {\n", INSN_PARAMETER_NAME);
  fprintf (output_file, "      %s = %s (%s);\n", INTERNAL_INSN_CODE_NAME,
	   DFA_INSN_CODE_FUNC_NAME, INSN_PARAMETER_NAME);
  fprintf (output_file, "      if (%s > %s)\n        return 0;\n",
	   INTERNAL_INSN_CODE_NAME, ADVANCE_CYCLE_VALUE_NAME);
  fprintf (output_file, "    }\n  else\n    %s = %s;\n",
	   INTERNAL_INSN_CODE_NAME, ADVANCE_CYCLE_VALUE_NAME);
  fprintf (output_file, "\n  return %s (%s, %s);\n",
	   INTERNAL_MIN_ISSUE_DELAY_FUNC_NAME, INTERNAL_INSN_CODE_NAME,
	   STATE_NAME);
  fprintf (output_file, "}\n\n");
}