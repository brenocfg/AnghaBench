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
typedef  scalar_t__ handler_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int NSIG ; 
 int SIGKILL ; 
 int SIGSTOP ; 
 scalar_t__ SIG_ERR ; 
 unsigned int blocked_set ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__* old_handlers ; 
 scalar_t__ signal (int,scalar_t__) ; 

handler_t
rpl_signal (int sig, handler_t handler)
{
  /* We must provide a wrapper, so that a user can query what handler
     they installed even if that signal is currently blocked.  */
  if (sig >= 0 && sig < NSIG && sig != SIGKILL && sig != SIGSTOP
      && handler != SIG_ERR)
    {
      #ifdef SIGABRT_COMPAT
      if (sig == SIGABRT_COMPAT)
        sig = SIGABRT;
      #endif

      if (blocked_set & (1U << sig))
        {
          /* POSIX states that sigprocmask and signal are both
             async-signal-safe.  This is not true of our
             implementation - there is a slight data race where an
             asynchronous interrupt on signal A can occur after we
             install blocked_handler but before we have updated
             old_handlers for signal B, such that handler A can see
             stale information if it calls signal(B).  Oh well -
             signal handlers really shouldn't try to manipulate the
             installed handlers of unrelated signals.  */
          handler_t result = old_handlers[sig];
          old_handlers[sig] = handler;
          return result;
        }
      else
        return signal (sig, handler);
    }
  else
    {
      errno = EINVAL;
      return SIG_ERR;
    }
}