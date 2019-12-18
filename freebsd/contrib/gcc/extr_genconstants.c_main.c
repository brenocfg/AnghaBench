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
 int FATAL_EXIT_CODE ; 
 scalar_t__ SUCCESS_EXIT_CODE ; 
 scalar_t__ fclose (int /*<<< orphan*/ ) ; 
 scalar_t__ ferror (int /*<<< orphan*/ ) ; 
 scalar_t__ fflush (int /*<<< orphan*/ ) ; 
 scalar_t__ init_md_reader_args (int,char**) ; 
 int /*<<< orphan*/  print_md_constant ; 
 char* progname ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  traverse_md_constants (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
main (int argc, char **argv)
{
  progname = "genconstants";

  if (init_md_reader_args (argc, argv) != SUCCESS_EXIT_CODE)
    return (FATAL_EXIT_CODE);

  /* Initializing the MD reader has the side effect of loading up
     the constants table that we wish to scan.  */

  puts ("/* Generated automatically by the program `genconstants'");
  puts ("   from the machine description file `md'.  */\n");
  puts ("#ifndef GCC_INSN_CONSTANTS_H");
  puts ("#define GCC_INSN_CONSTANTS_H\n");

  traverse_md_constants (print_md_constant, stdout);

  puts ("\n#endif /* GCC_INSN_CONSTANTS_H */");

  if (ferror (stdout) || fflush (stdout) || fclose (stdout))
    return FATAL_EXIT_CODE;

  return SUCCESS_EXIT_CODE;
}