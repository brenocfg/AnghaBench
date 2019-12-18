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
struct decision_head {int dummy; } ;
typedef  int /*<<< orphan*/ * rtx ;

/* Variables and functions */
#define  DEFINE_INSN 132 
#define  DEFINE_PEEPHOLE2 131 
#define  DEFINE_PREDICATE 130 
#define  DEFINE_SPECIAL_PREDICATE 129 
#define  DEFINE_SPLIT 128 
 int FATAL_EXIT_CODE ; 
 int GET_CODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PEEPHOLE2 ; 
 int /*<<< orphan*/  RECOG ; 
 int /*<<< orphan*/  SPLIT ; 
 scalar_t__ SUCCESS_EXIT_CODE ; 
 scalar_t__ error_count ; 
 scalar_t__ ferror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 scalar_t__ have_error ; 
 scalar_t__ init_md_reader_args (int,char**) ; 
 struct decision_head make_insn_sequence (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct decision_head*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  merge_trees (struct decision_head*,struct decision_head*) ; 
 scalar_t__ next_insn_code ; 
 int /*<<< orphan*/  pattern_lineno ; 
 int /*<<< orphan*/  process_define_predicate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  process_tree (struct decision_head*,int /*<<< orphan*/ ) ; 
 char* progname ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/ * read_md_rtx (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  write_header () ; 

int
main (int argc, char **argv)
{
  rtx desc;
  struct decision_head recog_tree, split_tree, peephole2_tree, h;

  progname = "genrecog";

  memset (&recog_tree, 0, sizeof recog_tree);
  memset (&split_tree, 0, sizeof split_tree);
  memset (&peephole2_tree, 0, sizeof peephole2_tree);

  if (init_md_reader_args (argc, argv) != SUCCESS_EXIT_CODE)
    return (FATAL_EXIT_CODE);

  next_insn_code = 0;

  write_header ();

  /* Read the machine description.  */

  while (1)
    {
      desc = read_md_rtx (&pattern_lineno, &next_insn_code);
      if (desc == NULL)
	break;

      switch (GET_CODE (desc))
	{
	case DEFINE_PREDICATE:
	case DEFINE_SPECIAL_PREDICATE:
	  process_define_predicate (desc);
	  break;

	case DEFINE_INSN:
	  h = make_insn_sequence (desc, RECOG);
	  merge_trees (&recog_tree, &h);
	  break;

	case DEFINE_SPLIT:
	  h = make_insn_sequence (desc, SPLIT);
	  merge_trees (&split_tree, &h);
	  break;

	case DEFINE_PEEPHOLE2:
	  h = make_insn_sequence (desc, PEEPHOLE2);
	  merge_trees (&peephole2_tree, &h);

	default:
	  /* do nothing */;
	}
    }

  if (error_count || have_error)
    return FATAL_EXIT_CODE;

  puts ("\n\n");

  process_tree (&recog_tree, RECOG);
  process_tree (&split_tree, SPLIT);
  process_tree (&peephole2_tree, PEEPHOLE2);

  fflush (stdout);
  return (ferror (stdout) != 0 ? FATAL_EXIT_CODE : SUCCESS_EXIT_CODE);
}