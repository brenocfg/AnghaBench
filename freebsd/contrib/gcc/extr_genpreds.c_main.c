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
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
#define  DEFINE_ADDRESS_CONSTRAINT 133 
#define  DEFINE_CONSTRAINT 132 
#define  DEFINE_MEMORY_CONSTRAINT 131 
#define  DEFINE_PREDICATE 130 
#define  DEFINE_REGISTER_CONSTRAINT 129 
#define  DEFINE_SPECIAL_PREDICATE 128 
 int FATAL_EXIT_CODE ; 
 int GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ SUCCESS_EXIT_CODE ; 
 int /*<<< orphan*/  fatal (char*) ; 
 scalar_t__ fclose (int /*<<< orphan*/ ) ; 
 scalar_t__ ferror (int /*<<< orphan*/ ) ; 
 scalar_t__ fflush (int /*<<< orphan*/ ) ; 
 scalar_t__ gen_constrs ; 
 scalar_t__ gen_header ; 
 scalar_t__ have_error ; 
 scalar_t__ init_md_reader_args_cb (int,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_option ; 
 int /*<<< orphan*/  process_define_constraint (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  process_define_predicate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  process_define_register_constraint (int /*<<< orphan*/ ,int) ; 
 char* progname ; 
 int /*<<< orphan*/  read_md_rtx (int*,int*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  write_insn_preds_c () ; 
 int /*<<< orphan*/  write_tm_constrs_h () ; 
 int /*<<< orphan*/  write_tm_preds_h () ; 

int
main (int argc, char **argv)
{
  rtx defn;
  int pattern_lineno, next_insn_code = 0;

  progname = argv[0];
  if (argc <= 1)
    fatal ("no input file name");
  if (init_md_reader_args_cb (argc, argv, parse_option) != SUCCESS_EXIT_CODE)
    return FATAL_EXIT_CODE;

  while ((defn = read_md_rtx (&pattern_lineno, &next_insn_code)) != 0)
    switch (GET_CODE (defn))
      {
      case DEFINE_PREDICATE:
      case DEFINE_SPECIAL_PREDICATE:
	process_define_predicate (defn, pattern_lineno);
	break;

      case DEFINE_CONSTRAINT:
      case DEFINE_MEMORY_CONSTRAINT:
      case DEFINE_ADDRESS_CONSTRAINT:
	process_define_constraint (defn, pattern_lineno);
	break;

      case DEFINE_REGISTER_CONSTRAINT:
	process_define_register_constraint (defn, pattern_lineno);
	break;

      default:
	break;
      }

  if (gen_header)
    write_tm_preds_h ();
  else if (gen_constrs)
    write_tm_constrs_h ();
  else
    write_insn_preds_c ();

  if (have_error || ferror (stdout) || fflush (stdout) || fclose (stdout))
    return FATAL_EXIT_CODE;

  return SUCCESS_EXIT_CODE;
}