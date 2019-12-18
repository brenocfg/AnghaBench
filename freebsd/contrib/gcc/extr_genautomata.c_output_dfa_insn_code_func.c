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
 char* DFA_INSN_CODES_LENGTH_VARIABLE_NAME ; 
 char* DFA_INSN_CODES_VARIABLE_NAME ; 
 char* DFA_INSN_CODE_FUNC_NAME ; 
 char* INSN_PARAMETER_NAME ; 
 char* INTERNAL_DFA_INSN_CODE_FUNC_NAME ; 
 char* INTERNAL_INSN_CODE_NAME ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  output_file ; 

__attribute__((used)) static void
output_dfa_insn_code_func (void)
{
  /* Emacs c-mode gets really confused if there's a { or } in column 0
     inside a string, so don't do that.  */
  fprintf (output_file, "\
static void\n\
dfa_insn_code_enlarge (int uid)\n\
{\n\
  int i = %s;\n\
  %s = 2 * uid;\n\
  %s = xrealloc (%s,\n\
                 %s * sizeof(int));\n\
  for (; i < %s; i++)\n\
    %s[i] = -1;\n}\n\n",
	   DFA_INSN_CODES_LENGTH_VARIABLE_NAME,
	   DFA_INSN_CODES_LENGTH_VARIABLE_NAME,
	   DFA_INSN_CODES_VARIABLE_NAME, DFA_INSN_CODES_VARIABLE_NAME,
	   DFA_INSN_CODES_LENGTH_VARIABLE_NAME,
	   DFA_INSN_CODES_LENGTH_VARIABLE_NAME,
	   DFA_INSN_CODES_VARIABLE_NAME);
  fprintf (output_file, "\
static inline int\n%s (rtx %s)\n\
{\n\
  int uid = INSN_UID (%s);\n\
  int %s;\n\n",
	   DFA_INSN_CODE_FUNC_NAME, INSN_PARAMETER_NAME,
	   INSN_PARAMETER_NAME, INTERNAL_INSN_CODE_NAME);

  fprintf (output_file,
	   "  if (uid >= %s)\n    dfa_insn_code_enlarge (uid);\n\n",
	   DFA_INSN_CODES_LENGTH_VARIABLE_NAME);
  fprintf (output_file, "  %s = %s[uid];\n",
	   INTERNAL_INSN_CODE_NAME, DFA_INSN_CODES_VARIABLE_NAME);
  fprintf (output_file, "\
  if (%s < 0)\n\
    {\n\
      %s = %s (%s);\n\
      %s[uid] = %s;\n\
    }\n",
	   INTERNAL_INSN_CODE_NAME,
	   INTERNAL_INSN_CODE_NAME,
	   INTERNAL_DFA_INSN_CODE_FUNC_NAME, INSN_PARAMETER_NAME,
	   DFA_INSN_CODES_VARIABLE_NAME, INTERNAL_INSN_CODE_NAME);
  fprintf (output_file, "  return %s;\n}\n\n", INTERNAL_INSN_CODE_NAME);
}