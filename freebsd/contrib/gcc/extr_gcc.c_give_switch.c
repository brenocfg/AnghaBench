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
struct TYPE_2__ {scalar_t__ live_cond; char* part1; char** args; int validated; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_DIR_SEPARATOR (char const) ; 
 scalar_t__ SWITCH_IGNORE ; 
 int /*<<< orphan*/  do_spec_1 (char const*,int,int /*<<< orphan*/ *) ; 
 unsigned int strlen (char const*) ; 
 char* suffix_subst ; 
 TYPE_1__* switches ; 

__attribute__((used)) static void
give_switch (int switchnum, int omit_first_word)
{
  if (switches[switchnum].live_cond == SWITCH_IGNORE)
    return;

  if (!omit_first_word)
    {
      do_spec_1 ("-", 0, NULL);
      do_spec_1 (switches[switchnum].part1, 1, NULL);
    }

  if (switches[switchnum].args != 0)
    {
      const char **p;
      for (p = switches[switchnum].args; *p; p++)
	{
	  const char *arg = *p;

	  do_spec_1 (" ", 0, NULL);
	  if (suffix_subst)
	    {
	      unsigned length = strlen (arg);
	      int dot = 0;

	      while (length-- && !IS_DIR_SEPARATOR (arg[length]))
		if (arg[length] == '.')
		  {
		    ((char *)arg)[length] = 0;
		    dot = 1;
		    break;
		  }
	      do_spec_1 (arg, 1, NULL);
	      if (dot)
		((char *)arg)[length] = '.';
	      do_spec_1 (suffix_subst, 1, NULL);
	    }
	  else
	    do_spec_1 (arg, 1, NULL);
	}
    }

  do_spec_1 (" ", 0, NULL);
  switches[switchnum].validated = 1;
}