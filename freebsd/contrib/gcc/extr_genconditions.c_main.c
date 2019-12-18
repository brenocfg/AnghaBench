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
#define  DEFINE_EXPAND 132 
#define  DEFINE_INSN 131 
#define  DEFINE_PEEPHOLE 130 
#define  DEFINE_PEEPHOLE2 129 
#define  DEFINE_SPLIT 128 
 int FATAL_EXIT_CODE ; 
 int GET_CODE (int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCESS_EXIT_CODE ; 
 int /*<<< orphan*/  XSTR (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  add_c_test (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ferror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 scalar_t__ init_md_reader_args (int,char**) ; 
 char* progname ; 
 int /*<<< orphan*/ * read_md_rtx (int*,int*) ; 
 int saw_eh_return ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  write_conditions () ; 
 int /*<<< orphan*/  write_header () ; 
 int /*<<< orphan*/  write_writer () ; 

int
main (int argc, char **argv)
{
  rtx desc;
  int pattern_lineno; /* not used */
  int code;

  progname = "genconditions";

  if (init_md_reader_args (argc, argv) != SUCCESS_EXIT_CODE)
    return (FATAL_EXIT_CODE);

  /* Read the machine description.  */
  while (1)
    {
      desc = read_md_rtx (&pattern_lineno, &code);
      if (desc == NULL)
	break;

      /* N.B. define_insn_and_split, define_cond_exec are handled
	 entirely within read_md_rtx; we never see them.  */
      switch (GET_CODE (desc))
	{
	default:
	  break;

	case DEFINE_INSN:
	case DEFINE_EXPAND:
	  add_c_test (XSTR (desc, 2), -1);
	  /* except.h needs to know whether there is an eh_return
	     pattern in the machine description.  */
	  if (!strcmp (XSTR (desc, 0), "eh_return"))
	    saw_eh_return = 1;
	  break;

	case DEFINE_SPLIT:
	case DEFINE_PEEPHOLE:
	case DEFINE_PEEPHOLE2:
	  add_c_test (XSTR (desc, 1), -1);
	  break;
	}
    }

  write_header ();
  write_conditions ();
  write_writer ();

  fflush (stdout);
  return (ferror (stdout) != 0 ? FATAL_EXIT_CODE : SUCCESS_EXIT_CODE);
}