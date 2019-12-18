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
 char* _ (char*) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 char* programname ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  verbose_flag ; 

__attribute__((used)) static void
display_help (void)
{
  printf (_("Usage: %s [options] file...\n"), programname);
  fputs (_("Options:\n"), stdout);

  fputs (_("  -pass-exit-codes         Exit with highest error code from a phase\n"), stdout);
  fputs (_("  --help                   Display this information\n"), stdout);
  fputs (_("  --target-help            Display target specific command line options\n"), stdout);
  if (! verbose_flag)
    fputs (_("  (Use '-v --help' to display command line options of sub-processes)\n"), stdout);
  fputs (_("  -dumpspecs               Display all of the built in spec strings\n"), stdout);
  fputs (_("  -dumpversion             Display the version of the compiler\n"), stdout);
  fputs (_("  -dumpmachine             Display the compiler's target processor\n"), stdout);
  fputs (_("  -print-search-dirs       Display the directories in the compiler's search path\n"), stdout);
  fputs (_("  -print-libgcc-file-name  Display the name of the compiler's companion library\n"), stdout);
  fputs (_("  -print-file-name=<lib>   Display the full path to library <lib>\n"), stdout);
  fputs (_("  -print-prog-name=<prog>  Display the full path to compiler component <prog>\n"), stdout);
  fputs (_("  -print-multi-directory   Display the root directory for versions of libgcc\n"), stdout);
  fputs (_("\
  -print-multi-lib         Display the mapping between command line options and\n\
                           multiple library search directories\n"), stdout);
  fputs (_("  -print-multi-os-directory Display the relative path to OS libraries\n"), stdout);
  fputs (_("  -Wa,<options>            Pass comma-separated <options> on to the assembler\n"), stdout);
  fputs (_("  -Wp,<options>            Pass comma-separated <options> on to the preprocessor\n"), stdout);
  fputs (_("  -Wl,<options>            Pass comma-separated <options> on to the linker\n"), stdout);
  fputs (_("  -Xassembler <arg>        Pass <arg> on to the assembler\n"), stdout);
  fputs (_("  -Xpreprocessor <arg>     Pass <arg> on to the preprocessor\n"), stdout);
  fputs (_("  -Xlinker <arg>           Pass <arg> on to the linker\n"), stdout);
  fputs (_("  -combine                 Pass multiple source files to compiler at once\n"), stdout);
  fputs (_("  -save-temps              Do not delete intermediate files\n"), stdout);
  fputs (_("  -pipe                    Use pipes rather than intermediate files\n"), stdout);
  fputs (_("  -time                    Time the execution of each subprocess\n"), stdout);
  fputs (_("  -specs=<file>            Override built-in specs with the contents of <file>\n"), stdout);
  fputs (_("  -std=<standard>          Assume that the input sources are for <standard>\n"), stdout);
  fputs (_("\
  --sysroot=<directory>    Use <directory> as the root directory for headers\n\
                           and libraries\n"), stdout);
  fputs (_("  -B <directory>           Add <directory> to the compiler's search paths\n"), stdout);
  fputs (_("  -b <machine>             Run gcc for target <machine>, if installed\n"), stdout);
  fputs (_("  -V <version>             Run gcc version number <version>, if installed\n"), stdout);
  fputs (_("  -v                       Display the programs invoked by the compiler\n"), stdout);
  fputs (_("  -###                     Like -v but options quoted and commands not executed\n"), stdout);
  fputs (_("  -E                       Preprocess only; do not compile, assemble or link\n"), stdout);
  fputs (_("  -S                       Compile only; do not assemble or link\n"), stdout);
  fputs (_("  -c                       Compile and assemble, but do not link\n"), stdout);
  fputs (_("  -o <file>                Place the output into <file>\n"), stdout);
  fputs (_("\
  -x <language>            Specify the language of the following input files\n\
                           Permissible languages include: c c++ assembler none\n\
                           'none' means revert to the default behavior of\n\
                           guessing the language based on the file's extension\n\
"), stdout);

  printf (_("\
\nOptions starting with -g, -f, -m, -O, -W, or --param are automatically\n\
 passed on to the various sub-processes invoked by %s.  In order to pass\n\
 other options on to these processes the -W<letter> options must be used.\n\
"), programname);

  /* The rest of the options are displayed by invocations of the various
     sub-processes.  */
}