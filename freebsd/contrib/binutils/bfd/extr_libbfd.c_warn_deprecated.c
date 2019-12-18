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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/  stderr ; 

void
warn_deprecated (const char *what,
		 const char *file,
		 int line,
		 const char *func)
{
  /* Poor man's tracking of functions we've already warned about.  */
  static size_t mask = 0;

  if (~(size_t) func & ~mask)
    {
      /* Note: separate sentences in order to allow
	 for translation into other languages.  */
      if (func)
	fprintf (stderr, _("Deprecated %s called at %s line %d in %s\n"),
		 what, file, line, func);
      else
	fprintf (stderr, _("Deprecated %s called\n"), what);
      mask |= ~(size_t) func;
    }
}