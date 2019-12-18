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
 char* DFA_CLEAN_INSN_CACHE_FUNC_NAME ; 
 char* DFA_CLEAR_SINGLE_INSN_CACHE_FUNC_NAME ; 
 char* DFA_INSN_CODES_LENGTH_VARIABLE_NAME ; 
 char* DFA_INSN_CODES_VARIABLE_NAME ; 
 char* INSN_PARAMETER_NAME ; 
 char* I_VARIABLE_NAME ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*,...) ; 
 int /*<<< orphan*/  output_file ; 

__attribute__((used)) static void
output_dfa_clean_insn_cache_func (void)
{
  fprintf (output_file,
	   "void\n%s (void)\n{\n  int %s;\n\n",
	   DFA_CLEAN_INSN_CACHE_FUNC_NAME, I_VARIABLE_NAME);
  fprintf (output_file,
	   "  for (%s = 0; %s < %s; %s++)\n    %s [%s] = -1;\n}\n\n",
	   I_VARIABLE_NAME, I_VARIABLE_NAME,
	   DFA_INSN_CODES_LENGTH_VARIABLE_NAME, I_VARIABLE_NAME,
	   DFA_INSN_CODES_VARIABLE_NAME, I_VARIABLE_NAME);

  fprintf (output_file,
           "void\n%s (rtx %s)\n{\n  int %s;\n\n",
           DFA_CLEAR_SINGLE_INSN_CACHE_FUNC_NAME, INSN_PARAMETER_NAME,
	   I_VARIABLE_NAME);
  fprintf (output_file,
           "  %s = INSN_UID (%s);\n  if (%s < %s)\n    %s [%s] = -1;\n}\n\n",
           I_VARIABLE_NAME, INSN_PARAMETER_NAME, I_VARIABLE_NAME,
	   DFA_INSN_CODES_LENGTH_VARIABLE_NAME, DFA_INSN_CODES_VARIABLE_NAME,
	   I_VARIABLE_NAME);
}