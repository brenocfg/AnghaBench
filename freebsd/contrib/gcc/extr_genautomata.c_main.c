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
#define  ABSENCE_SET 139 
#define  AUTOMATA_OPTION 138 
#define  DEFINE_AUTOMATON 137 
#define  DEFINE_BYPASS 136 
#define  DEFINE_CPU_UNIT 135 
#define  DEFINE_INSN_RESERVATION 134 
#define  DEFINE_QUERY_CPU_UNIT 133 
#define  DEFINE_RESERVATION 132 
#define  EXCLUSION_SET 131 
 int FATAL_EXIT_CODE ; 
#define  FINAL_ABSENCE_SET 130 
#define  FINAL_PRESENCE_SET 129 
 int GET_CODE (int /*<<< orphan*/ *) ; 
#define  PRESENCE_SET 128 
 scalar_t__ SUCCESS_EXIT_CODE ; 
 scalar_t__ VEC_length (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decl_t ; 
 int /*<<< orphan*/  decls ; 
 int /*<<< orphan*/  expand_automata () ; 
 scalar_t__ ferror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_absence_set (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gen_automata_option (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gen_automaton (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gen_bypass (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gen_cpu_unit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gen_excl_set (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gen_final_absence_set (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gen_final_presence_set (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gen_insn_reserv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gen_presence_set (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gen_query_cpu_unit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gen_reserv (int /*<<< orphan*/ *) ; 
 scalar_t__ have_error ; 
 scalar_t__ init_md_reader_args (int,char**) ; 
 int /*<<< orphan*/  initiate_automaton_gen (int,char**) ; 
 char* progname ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/ * read_md_rtx (int*,int*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  write_automata () ; 

int
main (int argc, char **argv)
{
  rtx desc;

  progname = "genautomata";

  if (init_md_reader_args (argc, argv) != SUCCESS_EXIT_CODE)
    return (FATAL_EXIT_CODE);

  initiate_automaton_gen (argc, argv);
  while (1)
    {
      int lineno;
      int insn_code_number;

      desc = read_md_rtx (&lineno, &insn_code_number);
      if (desc == NULL)
	break;

      switch (GET_CODE (desc))
	{
	case DEFINE_CPU_UNIT:
	  gen_cpu_unit (desc);
	  break;

	case DEFINE_QUERY_CPU_UNIT:
	  gen_query_cpu_unit (desc);
	  break;

	case DEFINE_BYPASS:
	  gen_bypass (desc);
	  break;

	case EXCLUSION_SET:
	  gen_excl_set (desc);
	  break;

	case PRESENCE_SET:
	  gen_presence_set (desc);
	  break;

	case FINAL_PRESENCE_SET:
	  gen_final_presence_set (desc);
	  break;

	case ABSENCE_SET:
	  gen_absence_set (desc);
	  break;

	case FINAL_ABSENCE_SET:
	  gen_final_absence_set (desc);
	  break;

	case DEFINE_AUTOMATON:
	  gen_automaton (desc);
	  break;

	case AUTOMATA_OPTION:
	  gen_automata_option (desc);
	  break;

	case DEFINE_RESERVATION:
	  gen_reserv (desc);
	  break;

	case DEFINE_INSN_RESERVATION:
	  gen_insn_reserv (desc);
	  break;

	default:
	  break;
	}
    }

  if (have_error)
    return FATAL_EXIT_CODE;

  puts ("/* Generated automatically by the program `genautomata'\n"
	"   from the machine description file `md'.  */\n\n"
	"#include \"config.h\"\n"
	"#include \"system.h\"\n"
	"#include \"coretypes.h\"\n"
	"#include \"tm.h\"\n"
	"#include \"rtl.h\"\n"
	"#include \"tm_p.h\"\n"
	"#include \"insn-config.h\"\n"
	"#include \"recog.h\"\n"
	"#include \"regs.h\"\n"
	"#include \"real.h\"\n"
	"#include \"output.h\"\n"
	"#include \"insn-attr.h\"\n"
	"#include \"toplev.h\"\n"
	"#include \"flags.h\"\n"
	"#include \"function.h\"\n");

  if (VEC_length (decl_t, decls) > 0)
    {
      expand_automata ();
      write_automata ();
    }

  fflush (stdout);
  return (ferror (stdout) != 0 ? FATAL_EXIT_CODE : SUCCESS_EXIT_CODE);
}