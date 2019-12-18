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
 int FATAL_EXIT_CODE ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCESS_EXIT_CODE ; 
 scalar_t__ fclose (int /*<<< orphan*/ ) ; 
 scalar_t__ ferror (int /*<<< orphan*/ ) ; 
 scalar_t__ fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_insn (int /*<<< orphan*/ *,int) ; 
 scalar_t__ init_md_reader_args (int,char**) ; 
 scalar_t__ insn_elision ; 
 char* progname ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/ * read_md_rtx (int*,int*) ; 
 int /*<<< orphan*/  stdout ; 

int
main (int argc, char **argv)
{
  rtx desc;

  progname = "gencodes";

  /* We need to see all the possibilities.  Elided insns may have
     direct references to CODE_FOR_xxx in C code.  */
  insn_elision = 0;

  if (init_md_reader_args (argc, argv) != SUCCESS_EXIT_CODE)
    return (FATAL_EXIT_CODE);

  puts ("\
/* Generated automatically by the program `gencodes'\n\
   from the machine description file `md'.  */\n\
\n\
#ifndef GCC_INSN_CODES_H\n\
#define GCC_INSN_CODES_H\n\
\n\
enum insn_code {");

  /* Read the machine description.  */

  while (1)
    {
      int line_no;
      int insn_code_number;

      desc = read_md_rtx (&line_no, &insn_code_number);
      if (desc == NULL)
	break;

      if (GET_CODE (desc) == DEFINE_INSN || GET_CODE (desc) == DEFINE_EXPAND)
	gen_insn (desc, insn_code_number);
    }

  puts ("  CODE_FOR_nothing\n\
};\n\
\n\
#endif /* GCC_INSN_CODES_H */");

  if (ferror (stdout) || fflush (stdout) || fclose (stdout))
    return FATAL_EXIT_CODE;

  return SUCCESS_EXIT_CODE;
}