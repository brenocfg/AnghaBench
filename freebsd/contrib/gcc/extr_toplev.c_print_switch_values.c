#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int flags; char* opt_text; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int CL_REPORT ; 
 char* _ (char*) ; 
 TYPE_1__* cl_options ; 
 size_t cl_options_count ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char const*) ; 
 scalar_t__ option_enabled (size_t) ; 
 int print_single_switch (int /*<<< orphan*/ *,int,int,char const*,char const*,char const*,char const*,char*) ; 
 int /*<<< orphan*/  randomize () ; 
 char** save_argv ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static void
print_switch_values (FILE *file, int pos, int max,
		     const char *indent, const char *sep, const char *term)
{
  size_t j;
  const char **p;

  /* Fill in the -frandom-seed option, if the user didn't pass it, so
     that it can be printed below.  This helps reproducibility.  */
  randomize ();

  /* Print the options as passed.  */
  pos = print_single_switch (file, pos, max, indent, *indent ? " " : "", term,
			     _("options passed: "), "");

  for (p = &save_argv[1]; *p != NULL; p++)
    if (**p == '-')
      {
	/* Ignore these.  */
	if (strcmp (*p, "-o") == 0)
	  {
	    if (p[1] != NULL)
	      p++;
	    continue;
	  }
	if (strcmp (*p, "-quiet") == 0)
	  continue;
	if (strcmp (*p, "-version") == 0)
	  continue;
	if ((*p)[1] == 'd')
	  continue;

	pos = print_single_switch (file, pos, max, indent, sep, term, *p, "");
      }
  if (pos > 0)
    fprintf (file, "%s", term);

  /* Print the -f and -m options that have been enabled.
     We don't handle language specific options but printing argv
     should suffice.  */

  pos = print_single_switch (file, 0, max, indent, *indent ? " " : "", term,
			     _("options enabled: "), "");

  for (j = 0; j < cl_options_count; j++)
    if ((cl_options[j].flags & CL_REPORT)
	&& option_enabled (j) > 0)
      pos = print_single_switch (file, pos, max, indent, sep, term,
				 "", cl_options[j].opt_text);

  fprintf (file, "%s", term);
}