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
 int /*<<< orphan*/  break_command_1 (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isdigit (char) ; 
 int /*<<< orphan*/  printf_filtered (char*) ; 

__attribute__((used)) static void
stopat_command (char *arg, int from_tty)
{
  int badInput = 0;

  if (arg == (char *) NULL || *arg == '*')	/* no line number */
    badInput = 1;
  else
    {
      char *argptr = arg;
      int hasColon = 0;

      /* look for a ':'.  If there is a '::' then get out, otherwise
         it is probably a line number. */
      while (*argptr && !hasColon)
	{
	  hasColon = (*argptr == ':');
	  argptr++;
	}

      if (hasColon)
	badInput = (*argptr == ':');	/* we have class::method */
      else
	badInput = !isdigit (*arg);	/* not a line number */
    }

  if (badInput)
    printf_filtered ("Usage: stop at <line>\n");
  else
    break_command_1 (arg, 0, from_tty, NULL);
}