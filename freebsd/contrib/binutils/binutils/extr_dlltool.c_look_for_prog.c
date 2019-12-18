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
struct stat {int dummy; } ;

/* Variables and functions */
 char const* EXECUTABLE_SUFFIX ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  inform (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 char* strcat (char*,char const*) ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 
 char* xmalloc (scalar_t__) ; 

__attribute__((used)) static char *
look_for_prog (const char *prog_name, const char *prefix, int end_prefix)
{
  struct stat s;
  char *cmd;

  cmd = xmalloc (strlen (prefix)
		 + strlen (prog_name)
#ifdef HAVE_EXECUTABLE_SUFFIX
		 + strlen (EXECUTABLE_SUFFIX)
#endif
		 + 10);
  strcpy (cmd, prefix);

  sprintf (cmd + end_prefix, "%s", prog_name);

  if (strchr (cmd, '/') != NULL)
    {
      int found;

      found = (stat (cmd, &s) == 0
#ifdef HAVE_EXECUTABLE_SUFFIX
	       || stat (strcat (cmd, EXECUTABLE_SUFFIX), &s) == 0
#endif
	       );

      if (! found)
	{
	  /* xgettext:c-format */
	  inform (_("Tried file: %s"), cmd);
	  free (cmd);
	  return NULL;
	}
    }

  /* xgettext:c-format */
  inform (_("Using file: %s"), cmd);

  return cmd;
}