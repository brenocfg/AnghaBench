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
usage (FILE *stream, int status)
{
  fprintf (stream, _("Usage: %s [option(s)] [addr(s)]\n"), program_name);
  fprintf (stream, _(" Convert addresses into line number/file name pairs.\n"));
  fprintf (stream, _(" If no addresses are specified on the command line, they will be read from stdin\n"));
  fprintf (stream, _(" The options are:\n\
  @<file>                Read options from <file>\n\
  -b --target=<bfdname>  Set the binary file format\n\
  -e --exe=<executable>  Set the input file name (default is a.out)\n\
  -i --inlines           Unwind inlined functions\n\
  -j --section=<name>    Read section-relative offsets instead of addresses\n\
  -s --basenames         Strip directory names\n\
  -f --functions         Show function names\n\
  -C --demangle[=style]  Demangle function names\n\
  -h --help              Display this information\n\
  -v --version           Display the program's version\n\
\n"));

  list_supported_targets (program_name, stream);
  if (REPORT_BUGS_TO[0] && status == 0)
    fprintf (stream, _("Report bugs to %s\n"), REPORT_BUGS_TO);
  exit (status);
}