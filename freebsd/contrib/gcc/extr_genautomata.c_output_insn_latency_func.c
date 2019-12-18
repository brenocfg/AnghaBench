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
 char* INSN2_PARAMETER_NAME ; 
 char* INSN_LATENCY_FUNC_NAME ; 
 char* INSN_PARAMETER_NAME ; 
 char* INTERNAL_INSN2_CODE_NAME ; 
 char* INTERNAL_INSN_CODE_NAME ; 
 char* INTERNAL_INSN_LATENCY_FUNC_NAME ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*,...) ; 
 int /*<<< orphan*/  output_file ; 
 int /*<<< orphan*/  output_internal_insn_code_evaluation (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
output_insn_latency_func (void)
{
  fprintf (output_file, "int\n%s (rtx %s, rtx %s)\n",
	   INSN_LATENCY_FUNC_NAME, INSN_PARAMETER_NAME, INSN2_PARAMETER_NAME);
  fprintf (output_file, "{\n  int %s, %s;\n",
	   INTERNAL_INSN_CODE_NAME, INTERNAL_INSN2_CODE_NAME);
  output_internal_insn_code_evaluation (INSN_PARAMETER_NAME,
					INTERNAL_INSN_CODE_NAME, 0);
  output_internal_insn_code_evaluation (INSN2_PARAMETER_NAME,
					INTERNAL_INSN2_CODE_NAME, 0);
  fprintf (output_file, "  return %s (%s, %s, %s, %s);\n}\n\n",
	   INTERNAL_INSN_LATENCY_FUNC_NAME,
	   INTERNAL_INSN_CODE_NAME, INTERNAL_INSN2_CODE_NAME,
	   INSN_PARAMETER_NAME, INSN2_PARAMETER_NAME);
}