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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* REPORT_BUGS_TO ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  list_supported_targets (char*,int /*<<< orphan*/ *) ; 
 char* program_name ; 

__attribute__((used)) static void
strip_usage (FILE *stream, int exit_status)
{
  fprintf (stream, _("Usage: %s <option(s)> in-file(s)\n"), program_name);
  fprintf (stream, _(" Removes symbols and sections from files\n"));
  fprintf (stream, _(" The options are:\n"));
  fprintf (stream, _("\
  -I --input-target=<bfdname>      Assume input file is in format <bfdname>\n\
  -O --output-target=<bfdname>     Create an output file in format <bfdname>\n\
  -F --target=<bfdname>            Set both input and output format to <bfdname>\n\
  -p --preserve-dates              Copy modified/access timestamps to the output\n\
  -R --remove-section=<name>       Remove section <name> from the output\n\
  -s --strip-all                   Remove all symbol and relocation information\n\
  -g -S -d --strip-debug           Remove all debugging symbols & sections\n\
     --strip-unneeded              Remove all symbols not needed by relocations\n\
     --only-keep-debug             Strip everything but the debug information\n\
  -N --strip-symbol=<name>         Do not copy symbol <name>\n\
  -K --keep-symbol=<name>          Do not strip symbol <name>\n\
     --keep-file-symbols           Do not strip file symbol(s)\n\
  -w --wildcard                    Permit wildcard in symbol comparison\n\
  -x --discard-all                 Remove all non-global symbols\n\
  -X --discard-locals              Remove any compiler-generated symbols\n\
  -v --verbose                     List all object files modified\n\
  -V --version                     Display this program's version number\n\
  -h --help                        Display this output\n\
     --info                        List object formats & architectures supported\n\
  -o <file>                        Place stripped output into <file>\n\
"));

  list_supported_targets (program_name, stream);
  if (REPORT_BUGS_TO[0] && exit_status == 0)
    fprintf (stream, _("Report bugs to %s\n"), REPORT_BUGS_TO);
  exit (exit_status);
}