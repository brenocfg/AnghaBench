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
 char* strchr (char*,char) ; 

__attribute__((used)) static void
breakup_args (char *scratch, char **argv)
{
  char *cp = scratch;

  for (;;)
    {

      /* Scan past leading separators */
      while (*cp == ' ' || *cp == '\t' || *cp == '\n')
	{
	  cp++;
	}

      /* Break if at end of string */
      if (*cp == '\0')
	break;

      /* Take an arg */
      *argv++ = cp;

      /* Scan for next arg separator */
      cp = strchr (cp, ' ');
      if (cp == NULL)
	cp = strchr (cp, '\t');
      if (cp == NULL)
	cp = strchr (cp, '\n');

      /* No separators => end of string => break */
      if (cp == NULL)
	break;

      /* Replace the separator with a terminator */
      *cp++ = '\0';
    }

  /* execv requires a null-terminated arg vector */
  *argv = NULL;

}