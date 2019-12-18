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
 char** signal_names ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

const char *
strsigno (int signo)
{
  const char *name;
  static char buf[32];

  if (signal_names == NULL)
    {
      init_signal_tables ();
    }

  if ((signo < 0) || (signo >= num_signal_names))
    {
      /* Out of range, just return NULL */
      name = NULL;
    }
  else if ((signal_names == NULL) || (signal_names[signo] == NULL))
    {
      /* In range, but no signal_names or no entry at this index. */
      sprintf (buf, "Signal %d", signo);
      name = (const char *) buf;
    }
  else
    {
      /* In range, and a valid name.  Just return the name. */
      name = signal_names[signo];
    }

  return (name);
}