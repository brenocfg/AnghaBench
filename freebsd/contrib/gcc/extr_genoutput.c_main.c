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
#define  DEFINE_ADDRESS_CONSTRAINT 136 
#define  DEFINE_CONSTRAINT 135 
#define  DEFINE_EXPAND 134 
#define  DEFINE_INSN 133 
#define  DEFINE_MEMORY_CONSTRAINT 132 
#define  DEFINE_PEEPHOLE 131 
#define  DEFINE_PEEPHOLE2 130 
#define  DEFINE_REGISTER_CONSTRAINT 129 
#define  DEFINE_SPLIT 128 
 int FATAL_EXIT_CODE ; 
 int GET_CODE (int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCESS_EXIT_CODE ; 
 scalar_t__ ferror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_expand (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  gen_insn (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  gen_peephole (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  gen_split (int /*<<< orphan*/ *,int) ; 
 scalar_t__ have_error ; 
 scalar_t__ init_md_reader_args (int,char**) ; 
 scalar_t__ next_code_number ; 
 scalar_t__ next_index_number ; 
 int /*<<< orphan*/  note_constraint (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  output_get_insn_name () ; 
 int /*<<< orphan*/  output_insn_data () ; 
 int /*<<< orphan*/  output_operand_data () ; 
 int /*<<< orphan*/  output_prologue () ; 
 int /*<<< orphan*/  printf (char*) ; 
 char* progname ; 
 int /*<<< orphan*/ * read_md_rtx (int*,scalar_t__*) ; 
 int /*<<< orphan*/  stdout ; 

int
main (int argc, char **argv)
{
  rtx desc;

  progname = "genoutput";

  if (init_md_reader_args (argc, argv) != SUCCESS_EXIT_CODE)
    return (FATAL_EXIT_CODE);

  output_prologue ();
  next_code_number = 0;
  next_index_number = 0;

  /* Read the machine description.  */

  while (1)
    {
      int line_no;

      desc = read_md_rtx (&line_no, &next_code_number);
      if (desc == NULL)
	break;

      switch (GET_CODE (desc))
	{
	case DEFINE_INSN:
	  gen_insn (desc, line_no);
	  break;

	case DEFINE_PEEPHOLE:
	  gen_peephole (desc, line_no);
	  break;

	case DEFINE_EXPAND:
	  gen_expand (desc, line_no);
	  break;

	case DEFINE_SPLIT:
	case DEFINE_PEEPHOLE2:
	  gen_split (desc, line_no);
	  break;

#ifdef USE_MD_CONSTRAINTS
	case DEFINE_CONSTRAINT:
	case DEFINE_REGISTER_CONSTRAINT:
	case DEFINE_ADDRESS_CONSTRAINT:
	case DEFINE_MEMORY_CONSTRAINT:
	  note_constraint (desc, line_no);
	  break;
#endif

	default:
	  break;
	}
      next_index_number++;
    }

  printf("\n\n");
  output_operand_data ();
  output_insn_data ();
  output_get_insn_name ();

  fflush (stdout);
  return (ferror (stdout) != 0 || have_error
	? FATAL_EXIT_CODE : SUCCESS_EXIT_CODE);
}