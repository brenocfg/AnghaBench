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
 char* _ (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char const*,char const*) ; 
 scalar_t__ initial_tab ; 
 int /*<<< orphan*/ * outfile ; 
 int /*<<< orphan*/  output_1_line (char const*,char const*,char const*,char const*) ; 

void
print_1_line (char const *line_flag, char const *const *line)
{
  char const *base = line[0], *limit = line[1]; /* Help the compiler.  */
  FILE *out = outfile; /* Help the compiler some more.  */
  char const *flag_format = 0;

  /* If -T was specified, use a Tab between the line-flag and the text.
     Otherwise use a Space (as Unix diff does).
     Print neither space nor tab if line-flags are empty.  */

  if (line_flag && *line_flag)
    {
      flag_format = initial_tab ? "%s\t" : "%s ";
      fprintf (out, flag_format, line_flag);
    }

  output_1_line (base, limit, flag_format, line_flag);

  if ((!line_flag || line_flag[0]) && limit[-1] != '\n')
    fprintf (out, "\n\\ %s\n", _("No newline at end of file"));
}