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
#define  DEFINE_EXPAND 131 
#define  DEFINE_INSN 130 
#define  DEFINE_PEEPHOLE2 129 
#define  DEFINE_SPLIT 128 
 int FATAL_EXIT_CODE ; 
 int GET_CODE (int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCESS_EXIT_CODE ; 
 scalar_t__ ferror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_expand (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gen_insn (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  gen_split (int /*<<< orphan*/ *) ; 
 scalar_t__ init_md_reader_args (int,char**) ; 
 scalar_t__ insn_code_number ; 
 scalar_t__ insn_index_number ; 
 int /*<<< orphan*/  output_add_clobbers () ; 
 int /*<<< orphan*/  output_added_clobbers_hard_reg_p () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* progname ; 
 int /*<<< orphan*/ * read_md_rtx (int*,scalar_t__*) ; 
 char* read_rtx_filename ; 
 int /*<<< orphan*/  stdout ; 

int
main (int argc, char **argv)
{
  rtx desc;

  progname = "genemit";

  if (init_md_reader_args (argc, argv) != SUCCESS_EXIT_CODE)
    return (FATAL_EXIT_CODE);

  /* Assign sequential codes to all entries in the machine description
     in parallel with the tables in insn-output.c.  */

  insn_code_number = 0;
  insn_index_number = 0;

  printf ("/* Generated automatically by the program `genemit'\n\
from the machine description file `md'.  */\n\n");

  printf ("#include \"config.h\"\n");
  printf ("#include \"system.h\"\n");
  printf ("#include \"coretypes.h\"\n");
  printf ("#include \"tm.h\"\n");
  printf ("#include \"rtl.h\"\n");
  printf ("#include \"tm_p.h\"\n");
  printf ("#include \"function.h\"\n");
  printf ("#include \"expr.h\"\n");
  printf ("#include \"optabs.h\"\n");
  printf ("#include \"real.h\"\n");
  printf ("#include \"flags.h\"\n");
  printf ("#include \"output.h\"\n");
  printf ("#include \"insn-config.h\"\n");
  printf ("#include \"hard-reg-set.h\"\n");
  printf ("#include \"recog.h\"\n");
  printf ("#include \"resource.h\"\n");
  printf ("#include \"reload.h\"\n");
  printf ("#include \"toplev.h\"\n");
  printf ("#include \"tm-constrs.h\"\n");
  printf ("#include \"ggc.h\"\n\n");
  printf ("#include \"basic-block.h\"\n\n");
  printf ("#define FAIL return (end_sequence (), _val)\n");
  printf ("#define DONE return (_val = get_insns (), end_sequence (), _val)\n\n");

  /* Read the machine description.  */

  while (1)
    {
      int line_no;

      desc = read_md_rtx (&line_no, &insn_code_number);
      if (desc == NULL)
	break;

      switch (GET_CODE (desc))
	{
	case DEFINE_INSN:
	  gen_insn (desc, line_no);
	  break;

	case DEFINE_EXPAND:
	  printf ("/* %s:%d */\n", read_rtx_filename, line_no);
	  gen_expand (desc);
	  break;

	case DEFINE_SPLIT:
	  printf ("/* %s:%d */\n", read_rtx_filename, line_no);
	  gen_split (desc);
	  break;

	case DEFINE_PEEPHOLE2:
	  printf ("/* %s:%d */\n", read_rtx_filename, line_no);
	  gen_split (desc);
	  break;

	default:
	  break;
	}
      ++insn_index_number;
    }

  /* Write out the routines to add CLOBBERs to a pattern and say whether they
     clobber a hard reg.  */
  output_add_clobbers ();
  output_added_clobbers_hard_reg_p ();

  fflush (stdout);
  return (ferror (stdout) != 0 ? FATAL_EXIT_CODE : SUCCESS_EXIT_CODE);
}