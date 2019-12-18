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
typedef  int /*<<< orphan*/ * rtx ;

/* Variables and functions */
 scalar_t__ DEFINE_EXPAND ; 
 scalar_t__ DEFINE_INSN ; 
 scalar_t__ DEFINE_PEEPHOLE ; 
 scalar_t__ DEFINE_PEEPHOLE2 ; 
 scalar_t__ DEFINE_SPLIT ; 
 int FATAL_EXIT_CODE ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCESS_EXIT_CODE ; 
 scalar_t__ ferror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_peephole (int /*<<< orphan*/ *) ; 
 scalar_t__ init_md_reader_args (int,char**) ; 
 int /*<<< orphan*/  insn_code_number ; 
 int max_opno ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* progname ; 
 int /*<<< orphan*/ * read_md_rtx (int*,int*) ; 
 int /*<<< orphan*/  stdout ; 

int
main (int argc, char **argv)
{
  rtx desc;

  max_opno = -1;

  progname = "genpeep";

  if (init_md_reader_args (argc, argv) != SUCCESS_EXIT_CODE)
    return (FATAL_EXIT_CODE);

  printf ("/* Generated automatically by the program `genpeep'\n\
from the machine description file `md'.  */\n\n");

  printf ("#include \"config.h\"\n");
  printf ("#include \"system.h\"\n");
  printf ("#include \"coretypes.h\"\n");
  printf ("#include \"tm.h\"\n");
  printf ("#include \"insn-config.h\"\n");
  printf ("#include \"rtl.h\"\n");
  printf ("#include \"tm_p.h\"\n");
  printf ("#include \"regs.h\"\n");
  printf ("#include \"output.h\"\n");
  printf ("#include \"real.h\"\n");
  printf ("#include \"recog.h\"\n");
  printf ("#include \"except.h\"\n");
  printf ("#include \"function.h\"\n");
  printf ("#include \"toplev.h\"\n");
  printf ("#include \"flags.h\"\n");
  printf ("#include \"tm-constrs.h\"\n\n");

  printf ("#ifdef HAVE_peephole\n");
  printf ("extern rtx peep_operand[];\n\n");
  printf ("#define operands peep_operand\n\n");

  printf ("rtx\npeephole (rtx ins1)\n{\n");
  printf ("  rtx insn ATTRIBUTE_UNUSED, x ATTRIBUTE_UNUSED, pat ATTRIBUTE_UNUSED;\n\n");

  /* Early out: no peepholes for insns followed by barriers.  */
  printf ("  if (NEXT_INSN (ins1)\n");
  printf ("      && BARRIER_P (NEXT_INSN (ins1)))\n");
  printf ("    return 0;\n\n");

  /* Read the machine description.  */

  while (1)
    {
      int line_no, rtx_number = 0;

      desc = read_md_rtx (&line_no, &rtx_number);
      if (desc == NULL)
	break;

       if (GET_CODE (desc) == DEFINE_PEEPHOLE)
	{
	  gen_peephole (desc);
	  insn_code_number++;
	}
      if (GET_CODE (desc) == DEFINE_INSN
	  || GET_CODE (desc) == DEFINE_EXPAND
	  || GET_CODE (desc) == DEFINE_SPLIT
	  || GET_CODE (desc) == DEFINE_PEEPHOLE2)
	{
	  insn_code_number++;
	}
    }

  printf ("  return 0;\n}\n\n");

  if (max_opno == -1)
    max_opno = 1;

  printf ("rtx peep_operand[%d];\n", max_opno + 1);
  printf ("#endif\n");

  fflush (stdout);
  return (ferror (stdout) != 0 ? FATAL_EXIT_CODE : SUCCESS_EXIT_CODE);
}