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
 int /*<<< orphan*/  SUCCESS_EXIT_CODE ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fnotice (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stdout ; 
 char* version_string ; 

__attribute__((used)) static void
print_version (void)
{
  fnotice (stdout, "gcov (GCC) %s\n", version_string);
  fprintf (stdout, "Copyright %s 2006 Free Software Foundation, Inc.\n",
	   _("(C)"));
  fnotice (stdout, "%s",
	   _("This is free software; see the source for copying conditions.\n"
	     "There is NO warranty; not even for MERCHANTABILITY or \n"
	     "FITNESS FOR A PARTICULAR PURPOSE.\n\n"));
  exit (SUCCESS_EXIT_CODE);
}