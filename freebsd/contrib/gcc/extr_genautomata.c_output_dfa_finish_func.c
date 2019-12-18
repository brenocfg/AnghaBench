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
 char* DFA_FINISH_FUNC_NAME ; 
 char* DFA_INSN_CODES_VARIABLE_NAME ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  output_file ; 

__attribute__((used)) static void
output_dfa_finish_func (void)
{
  fprintf (output_file, "void\n%s (void)\n{\n  free (%s);\n}\n\n",
	   DFA_FINISH_FUNC_NAME, DFA_INSN_CODES_VARIABLE_NAME);
}