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
 int FATAL_EXIT_CODE ; 
 int SUCCESS_EXIT_CODE ; 
 int /*<<< orphan*/  bug_report_url ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fnotice (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/ * stderr ; 
 int /*<<< orphan*/ * stdout ; 

__attribute__((used)) static void
print_usage (int error_p)
{
  FILE *file = error_p ? stderr : stdout;
  int status = error_p ? FATAL_EXIT_CODE : SUCCESS_EXIT_CODE;

  fnotice (file, "Usage: gcov [OPTION]... SOURCEFILE\n\n");
  fnotice (file, "Print code coverage information.\n\n");
  fnotice (file, "  -h, --help                      Print this help, then exit\n");
  fnotice (file, "  -v, --version                   Print version number, then exit\n");
  fnotice (file, "  -a, --all-blocks                Show information for every basic block\n");
  fnotice (file, "  -b, --branch-probabilities      Include branch probabilities in output\n");
  fnotice (file, "  -c, --branch-counts             Given counts of branches taken\n\
                                    rather than percentages\n");
  fnotice (file, "  -n, --no-output                 Do not create an output file\n");
  fnotice (file, "  -l, --long-file-names           Use long output file names for included\n\
                                    source files\n");
  fnotice (file, "  -f, --function-summaries        Output summaries for each function\n");
  fnotice (file, "  -o, --object-directory DIR|FILE Search for object files in DIR or called FILE\n");
  fnotice (file, "  -p, --preserve-paths            Preserve all pathname components\n");
  fnotice (file, "  -u, --unconditional-branches    Show unconditional branch counts too\n");
  fnotice (file, "\nFor bug reporting instructions, please see:\n%s.\n",
	   bug_report_url);
  exit (status);
}