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
typedef  int /*<<< orphan*/  RETSIGTYPE ;

/* Variables and functions */
 int /*<<< orphan*/  _exit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static RETSIGTYPE
parent_exit(int sig)
{
  /*
   * This signal handler is called during Amd initialization.  The parent
   * forks a child to do all the hard automounting work, and waits for a
   * SIGQUIT signal from the child.  When the parent gets the signal it's
   * supposed to call this handler and exit(3), thus completing the
   * daemonizing process.  Alas, on some systems, especially Linux 2.4/2.6
   * with Glibc, exit(3) doesn't always terminate the parent process.
   * Worse, the parent process now refuses to accept any more SIGQUIT
   * signals -- they are blocked.  What's really annoying is that this
   * doesn't happen all the time, suggesting a race condition somewhere.
   * (This happens even if I change the logic to use another signal.)  I
   * traced this to something which exit(3) does in addition to exiting the
   * process, probably some atexit() stuff or other side-effects related to
   * signal handling.  Either way, since at this stage the parent process
   * just needs to terminate, I'm simply calling _exit(2).  Note also that
   * the OpenGroup doesn't list exit(3) as a recommended "Base Interface"
   * but they do list _exit(2) as one.  This fix seems to work reliably all
   * the time. -Erez (2/27/2005)
   */
  _exit(0);
}