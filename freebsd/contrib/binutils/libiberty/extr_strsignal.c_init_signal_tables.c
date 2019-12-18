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
struct signal_info {char const* name; int value; char const* msg; } ;

/* Variables and functions */
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (char const**,int /*<<< orphan*/ ,int) ; 
 int num_signal_names ; 
 char const** signal_names ; 
 struct signal_info* signal_table ; 
 int sys_nsig ; 
 char const** sys_siglist ; 

__attribute__((used)) static void
init_signal_tables (void)
{
  const struct signal_info *eip;
  int nbytes;

  /* If we haven't already scanned the signal_table once to find the maximum
     signal value, then go find it now. */

  if (num_signal_names == 0)
    {
      for (eip = signal_table; eip -> name != NULL; eip++)
	{
	  if (eip -> value >= num_signal_names)
	    {
	      num_signal_names = eip -> value + 1;
	    }
	}
    }

  /* Now attempt to allocate the signal_names table, zero it out, and then
     initialize it from the statically initialized signal_table. */

  if (signal_names == NULL)
    {
      nbytes = num_signal_names * sizeof (char *);
      if ((signal_names = (const char **) malloc (nbytes)) != NULL)
	{
	  memset (signal_names, 0, nbytes);
	  for (eip = signal_table; eip -> name != NULL; eip++)
	    {
	      signal_names[eip -> value] = eip -> name;
	    }
	}
    }

#ifndef HAVE_SYS_SIGLIST

  /* Now attempt to allocate the sys_siglist table, zero it out, and then
     initialize it from the statically initialized signal_table. */

  if (sys_siglist == NULL)
    {
      nbytes = num_signal_names * sizeof (char *);
      if ((sys_siglist = (const char **) malloc (nbytes)) != NULL)
	{
	  memset (sys_siglist, 0, nbytes);
	  sys_nsig = num_signal_names;
	  for (eip = signal_table; eip -> name != NULL; eip++)
	    {
	      sys_siglist[eip -> value] = eip -> msg;
	    }
	}
    }

#endif

}