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
 int /*<<< orphan*/  puts (char*) ; 

__attribute__((used)) static void
print_header (void)
{
  /* N.B. Code below avoids putting squiggle braces in column 1 inside
     a string, because this confuses some editors' syntax highlighting
     engines.  */

  puts ("\
/* Generated automatically by the program `genextract'\n\
   from the machine description file `md'.  */\n\
\n\
#include \"config.h\"\n\
#include \"system.h\"\n\
#include \"coretypes.h\"\n\
#include \"tm.h\"\n\
#include \"rtl.h\"\n\
#include \"insn-config.h\"\n\
#include \"recog.h\"\n\
#include \"toplev.h\"\n\
\n\
/* This variable is used as the \"location\" of any missing operand\n\
   whose numbers are skipped by a given pattern.  */\n\
static rtx junk ATTRIBUTE_UNUSED;\n");

  puts ("\
void\n\
insn_extract (rtx insn)\n{\n\
  rtx *ro = recog_data.operand;\n\
  rtx **ro_loc = recog_data.operand_loc;\n\
  rtx pat = PATTERN (insn);\n\
  int i ATTRIBUTE_UNUSED; /* only for peepholes */\n\
\n\
#ifdef ENABLE_CHECKING\n\
  memset (ro, 0xab, sizeof (*ro) * MAX_RECOG_OPERANDS);\n\
  memset (ro_loc, 0xab, sizeof (*ro_loc) * MAX_RECOG_OPERANDS);\n\
#endif\n");

  puts ("\
  switch (INSN_CODE (insn))\n\
    {\n\
    default:\n\
      /* Control reaches here if insn_extract has been called with an\n\
         unrecognizable insn (code -1), or an insn whose INSN_CODE\n\
         corresponds to a DEFINE_EXPAND in the machine description;\n\
         either way, a bug.  */\n\
      if (INSN_CODE (insn) < 0)\n\
        fatal_insn (\"unrecognizable insn:\", insn);\n\
      else\n\
        fatal_insn (\"insn with invalid code number:\", insn);\n");
}