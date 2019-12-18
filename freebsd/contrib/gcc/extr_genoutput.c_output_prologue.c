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
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void
output_prologue (void)
{
  printf ("/* Generated automatically by the program `genoutput'\n\
   from the machine description file `md'.  */\n\n");

  printf ("#include \"config.h\"\n");
  printf ("#include \"system.h\"\n");
  printf ("#include \"coretypes.h\"\n");
  printf ("#include \"tm.h\"\n");
  printf ("#include \"flags.h\"\n");
  printf ("#include \"ggc.h\"\n");
  printf ("#include \"rtl.h\"\n");
  printf ("#include \"expr.h\"\n");
  printf ("#include \"insn-codes.h\"\n");
  printf ("#include \"tm_p.h\"\n");
  printf ("#include \"function.h\"\n");
  printf ("#include \"regs.h\"\n");
  printf ("#include \"hard-reg-set.h\"\n");
  printf ("#include \"real.h\"\n");
  printf ("#include \"insn-config.h\"\n\n");
  printf ("#include \"conditions.h\"\n");
  printf ("#include \"insn-attr.h\"\n\n");
  printf ("#include \"recog.h\"\n\n");
  printf ("#include \"toplev.h\"\n");
  printf ("#include \"output.h\"\n");
  printf ("#include \"target.h\"\n");
  printf ("#include \"tm-constrs.h\"\n");
}