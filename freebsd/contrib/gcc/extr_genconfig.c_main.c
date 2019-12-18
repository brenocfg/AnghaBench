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
 scalar_t__ fclose (int /*<<< orphan*/ ) ; 
 scalar_t__ ferror (int /*<<< orphan*/ ) ; 
 scalar_t__ fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_expand (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gen_insn (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gen_peephole (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gen_peephole2 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gen_split (int /*<<< orphan*/ *) ; 
 scalar_t__ have_cc0_flag ; 
 scalar_t__ have_cmove_flag ; 
 scalar_t__ have_cond_exec_flag ; 
 scalar_t__ have_lo_sum_flag ; 
 int have_peephole2_flag ; 
 int have_peephole_flag ; 
 scalar_t__ init_md_reader_args (int,char**) ; 
 int max_dup_operands ; 
 int max_insns_per_peep2 ; 
 int max_insns_per_split ; 
 int max_recog_operands ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* progname ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/ * read_md_rtx (int*,int*) ; 
 int /*<<< orphan*/  stdout ; 

int
main (int argc, char **argv)
{
  rtx desc;

  progname = "genconfig";

  if (init_md_reader_args (argc, argv) != SUCCESS_EXIT_CODE)
    return (FATAL_EXIT_CODE);

  puts ("/* Generated automatically by the program `genconfig'");
  puts ("   from the machine description file `md'.  */\n");
  puts ("#ifndef GCC_INSN_CONFIG_H");
  puts ("#define GCC_INSN_CONFIG_H\n");

  /* Allow at least 30 operands for the sake of asm constructs.  */
  /* ??? We *really* ought to reorganize things such that there
     is no fixed upper bound.  */
  max_recog_operands = 29;  /* We will add 1 later.  */
  max_dup_operands = 1;

  /* Read the machine description.  */

  while (1)
    {
      int line_no, insn_code_number = 0;

      desc = read_md_rtx (&line_no, &insn_code_number);
      if (desc == NULL)
	break;
	
      switch (GET_CODE (desc)) 
	{
  	  case DEFINE_INSN:
	    gen_insn (desc);
	    break;
	  
	  case DEFINE_EXPAND:
	    gen_expand (desc);
	    break;

	  case DEFINE_SPLIT:
	    gen_split (desc);
	    break;

	  case DEFINE_PEEPHOLE2:
	    have_peephole2_flag = 1;
	    gen_peephole2 (desc);
	    break;

	  case DEFINE_PEEPHOLE:
	    have_peephole_flag = 1;
	    gen_peephole (desc);
	    break;

	  default:
	    break;
	}
    }

  printf ("#define MAX_RECOG_OPERANDS %d\n", max_recog_operands + 1);
  printf ("#define MAX_DUP_OPERANDS %d\n", max_dup_operands);

  /* This is conditionally defined, in case the user writes code which emits
     more splits than we can readily see (and knows s/he does it).  */
  printf ("#ifndef MAX_INSNS_PER_SPLIT\n");
  printf ("#define MAX_INSNS_PER_SPLIT %d\n", max_insns_per_split);
  printf ("#endif\n");

  if (have_cc0_flag)
    {
      printf ("#define HAVE_cc0 1\n");
      printf ("#define CC0_P(X) ((X) == cc0_rtx)\n");
    }
  else
    {
      /* We output CC0_P this way to make sure that X is declared
	 somewhere.  */
      printf ("#define CC0_P(X) ((X) ? 0 : 0)\n");
    }

  if (have_cmove_flag)
    printf ("#define HAVE_conditional_move 1\n");

  if (have_cond_exec_flag)
    printf ("#define HAVE_conditional_execution 1\n");

  if (have_lo_sum_flag)
    printf ("#define HAVE_lo_sum 1\n");

  if (have_peephole_flag)
    printf ("#define HAVE_peephole 1\n");

  if (have_peephole2_flag)
    {
      printf ("#define HAVE_peephole2 1\n");
      printf ("#define MAX_INSNS_PER_PEEP2 %d\n", max_insns_per_peep2);
    }

  puts("\n#endif /* GCC_INSN_CONFIG_H */");

  if (ferror (stdout) || fflush (stdout) || fclose (stdout))
    return FATAL_EXIT_CODE;

  return SUCCESS_EXIT_CODE;
}