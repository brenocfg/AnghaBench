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
 char* program_name ; 

__attribute__((used)) static void
show_usage (FILE *file, int status)
{
  fprintf (file, _("Usage: %s [option(s)] in-file\n"), program_name);
  fprintf (file, _(" Print a human readable interpretation of a SYSROFF object file\n"));
  fprintf (file, _(" The options are:\n\
  @<file>                Read options from <file>\n\
  -h --help              Display this information\n\
  -v --version           Display the program's version\n\
\n"));

  if (REPORT_BUGS_TO[0] && status == 0)
    fprintf (file, _("Report bugs to %s\n"), REPORT_BUGS_TO);

  exit (status);
}