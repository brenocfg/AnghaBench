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
 int /*<<< orphan*/ * signal_names ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int sys_nsig ; 
 int /*<<< orphan*/ ** sys_siglist ; 

const char *
strsignal (int signo)
{
  const char *msg;
  static char buf[32];

#ifndef HAVE_SYS_SIGLIST

  if (signal_names == NULL)
    {
      init_signal_tables ();
    }

#endif

  if ((signo < 0) || (signo >= sys_nsig))
    {
      /* Out of range, just return NULL */
      msg = NULL;
    }
  else if ((sys_siglist == NULL) || (sys_siglist[signo] == NULL))
    {
      /* In range, but no sys_siglist or no entry at this index. */
      sprintf (buf, "Signal %d", signo);
      msg = (const char *) buf;
    }
  else
    {
      /* In range, and a valid message.  Just return the message. */
      msg = (const char *) sys_siglist[signo];
    }
  
  return (msg);
}