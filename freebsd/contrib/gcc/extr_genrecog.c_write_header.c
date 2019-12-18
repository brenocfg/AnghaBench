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
write_header (void)
{
  puts ("\
/* Generated automatically by the program `genrecog' from the target\n\
   machine description file.  */\n\
\n\
#include \"config.h\"\n\
#include \"system.h\"\n\
#include \"coretypes.h\"\n\
#include \"tm.h\"\n\
#include \"rtl.h\"\n\
#include \"tm_p.h\"\n\
#include \"function.h\"\n\
#include \"insn-config.h\"\n\
#include \"recog.h\"\n\
#include \"real.h\"\n\
#include \"output.h\"\n\
#include \"flags.h\"\n\
#include \"hard-reg-set.h\"\n\
#include \"resource.h\"\n\
#include \"toplev.h\"\n\
#include \"reload.h\"\n\
#include \"tm-constrs.h\"\n\
\n");

  puts ("\n\
/* `recog' contains a decision tree that recognizes whether the rtx\n\
   X0 is a valid instruction.\n\
\n\
   recog returns -1 if the rtx is not valid.  If the rtx is valid, recog\n\
   returns a nonnegative number which is the insn code number for the\n\
   pattern that matched.  This is the same as the order in the machine\n\
   description of the entry that matched.  This number can be used as an\n\
   index into `insn_data' and other tables.\n");
  puts ("\
   The third argument to recog is an optional pointer to an int.  If\n\
   present, recog will accept a pattern if it matches except for missing\n\
   CLOBBER expressions at the end.  In that case, the value pointed to by\n\
   the optional pointer will be set to the number of CLOBBERs that need\n\
   to be added (it should be initialized to zero by the caller).  If it");
  puts ("\
   is set nonzero, the caller should allocate a PARALLEL of the\n\
   appropriate size, copy the initial entries, and call add_clobbers\n\
   (found in insn-emit.c) to fill in the CLOBBERs.\n\
");

  puts ("\n\
   The function split_insns returns 0 if the rtl could not\n\
   be split or the split rtl as an INSN list if it can be.\n\
\n\
   The function peephole2_insns returns 0 if the rtl could not\n\
   be matched. If there was a match, the new rtl is returned in an INSN list,\n\
   and LAST_INSN will point to the last recognized insn in the old sequence.\n\
*/\n\n");
}