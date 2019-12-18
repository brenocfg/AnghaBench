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
struct environ {char** vector; } ;

/* Variables and functions */
 scalar_t__ DEPRECATED_STREQN (char*,char*,int) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  xfree (char*) ; 

void
unset_in_environ (struct environ *e, char *var)
{
  int len = strlen (var);
  char **vector = e->vector;
  char *s;

  for (; (s = *vector) != NULL; vector++)
    {
      if (DEPRECATED_STREQN (s, var, len) && s[len] == '=')
	{
	  xfree (s);
	  /* Walk through the vector, shuffling args down by one, including
	     the NULL terminator.  Can't use memcpy() here since the regions
	     overlap, and memmove() might not be available. */
	  while ((vector[0] = vector[1]) != NULL)
	    {
	      vector++;
	    }
	  break;
	}
    }
}