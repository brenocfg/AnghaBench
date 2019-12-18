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
 int /*<<< orphan*/  init_signal_tables () ; 
 int num_signal_names ; 
 int /*<<< orphan*/ ** signal_names ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ *) ; 

int
strtosigno (const char *name)
{
  int signo = 0;

  if (name != NULL)
    {
      if (signal_names == NULL)
	{
	  init_signal_tables ();
	}
      for (signo = 0; signo < num_signal_names; signo++)
	{
	  if ((signal_names[signo] != NULL) &&
	      (strcmp (name, signal_names[signo]) == 0))
	    {
	      break;
	    }
	}
      if (signo == num_signal_names)
	{
	  signo = 0;
	}
    }
  return (signo);
}