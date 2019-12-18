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
 char* _ (char const* const) ; 
 char** option_help_msgid ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 char* program_name ; 

__attribute__((used)) static void
usage (void)
{
  char const * const *p;

  printf (_("Usage: %s [OPTION]... FILE1 [FILE2 [SKIP1 [SKIP2]]]\n"),
	  program_name);
  printf ("%s\n\n", _("Compare two files byte by byte."));
  for (p = option_help_msgid;  *p;  p++)
    printf ("  %s\n", _(*p));
  printf ("\n%s\n%s\n\n%s\n%s\n\n%s\n",
	  _("SKIP1 and SKIP2 are the number of bytes to skip in each file."),
	  _("SKIP values may be followed by the following multiplicative suffixes:\n\
kB 1000, K 1024, MB 1,000,000, M 1,048,576,\n\
GB 1,000,000,000, G 1,073,741,824, and so on for T, P, E, Z, Y."),
	  _("If a FILE is `-' or missing, read standard input."),
	  _("Exit status is 0 if inputs are the same, 1 if different, 2 if trouble."),
	  _("Report bugs to <bug-gnu-utils@gnu.org>."));
}