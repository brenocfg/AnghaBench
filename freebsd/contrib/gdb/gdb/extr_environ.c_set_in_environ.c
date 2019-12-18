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
struct environ {char** vector; int allocated; } ;

/* Variables and functions */
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char*,char const*,int) ; 
 int /*<<< orphan*/  xfree (char*) ; 
 scalar_t__ xmalloc (int) ; 
 scalar_t__ xrealloc (char*,int) ; 

void
set_in_environ (struct environ *e, const char *var, const char *value)
{
  int i;
  int len = strlen (var);
  char **vector = e->vector;
  char *s;

  for (i = 0; (s = vector[i]) != NULL; i++)
    if (strncmp (s, var, len) == 0 && s[len] == '=')
      break;

  if (s == 0)
    {
      if (i == e->allocated)
	{
	  e->allocated += 10;
	  vector = (char **) xrealloc ((char *) vector,
				       (e->allocated + 1) * sizeof (char *));
	  e->vector = vector;
	}
      vector[i + 1] = 0;
    }
  else
    xfree (s);

  s = (char *) xmalloc (len + strlen (value) + 2);
  strcpy (s, var);
  strcat (s, "=");
  strcat (s, value);
  vector[i] = s;

  /* This used to handle setting the PATH and GNUTARGET variables
     specially.  The latter has been replaced by "set gnutarget"
     (which has worked since GDB 4.11).  The former affects searching
     the PATH to find SHELL, and searching the PATH to find the
     argument of "symbol-file" or "exec-file".  Maybe we should have
     some kind of "set exec-path" for that.  But in any event, having
     "set env" affect anything besides the inferior is a bad idea.
     What if we want to change the environment we pass to the program
     without afecting GDB's behavior?  */

  return;
}