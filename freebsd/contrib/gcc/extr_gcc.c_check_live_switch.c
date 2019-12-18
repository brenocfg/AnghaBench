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
struct TYPE_2__ {char* part1; scalar_t__ live_cond; int validated; } ;

/* Variables and functions */
 void* SWITCH_FALSE ; 
 scalar_t__ SWITCH_LIVE ; 
 int n_switches ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 
 TYPE_1__* switches ; 

__attribute__((used)) static int
check_live_switch (int switchnum, int prefix_length)
{
  const char *name = switches[switchnum].part1;
  int i;

  /* In the common case of {<at-most-one-letter>*}, a negating
     switch would always match, so ignore that case.  We will just
     send the conflicting switches to the compiler phase.  */
  if (prefix_length >= 0 && prefix_length <= 1)
    return 1;

  /* If we already processed this switch and determined if it was
     live or not, return our past determination.  */
  if (switches[switchnum].live_cond != 0)
    return switches[switchnum].live_cond > 0;

  /* Now search for duplicate in a manner that depends on the name.  */
  switch (*name)
    {
    case 'O':
      for (i = switchnum + 1; i < n_switches; i++)
	if (switches[i].part1[0] == 'O')
	  {
	    switches[switchnum].validated = 1;
	    switches[switchnum].live_cond = SWITCH_FALSE;
	    return 0;
	  }
      break;

    case 'W':  case 'f':  case 'm':
      if (! strncmp (name + 1, "no-", 3))
	{
	  /* We have Xno-YYY, search for XYYY.  */
	  for (i = switchnum + 1; i < n_switches; i++)
	    if (switches[i].part1[0] == name[0]
		&& ! strcmp (&switches[i].part1[1], &name[4]))
	      {
		switches[switchnum].validated = 1;
		switches[switchnum].live_cond = SWITCH_FALSE;
		return 0;
	      }
	}
      else
	{
	  /* We have XYYY, search for Xno-YYY.  */
	  for (i = switchnum + 1; i < n_switches; i++)
	    if (switches[i].part1[0] == name[0]
		&& switches[i].part1[1] == 'n'
		&& switches[i].part1[2] == 'o'
		&& switches[i].part1[3] == '-'
		&& !strcmp (&switches[i].part1[4], &name[1]))
	      {
		switches[switchnum].validated = 1;
		switches[switchnum].live_cond = SWITCH_FALSE;
		return 0;
	      }
	}
      break;
    }

  /* Otherwise the switch is live.  */
  switches[switchnum].live_cond = SWITCH_LIVE;
  return 1;
}