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
#define  SIGINT 129 
#define  SIGTERM 128 
 int /*<<< orphan*/  XLOG_WARNING ; 
 int immediate_abort ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  select_intr ; 
 scalar_t__ select_intr_valid ; 
 int /*<<< orphan*/  signal (int,int /*<<< orphan*/  (*) (int)) ; 

__attribute__((used)) static RETSIGTYPE
sigterm(int sig)
{
#ifdef REINSTALL_SIGNAL_HANDLER
  signal(sig, sigterm);
#endif /* REINSTALL_SIGNAL_HANDLER */

  switch (sig) {
  case SIGINT:
    immediate_abort = 15;
    break;

  case SIGTERM:
    immediate_abort = -1;
    /* fall through... */

  default:
    plog(XLOG_WARNING, "WARNING: automounter going down on signal %d", sig);
    break;
  }
  if (select_intr_valid)
    longjmp(select_intr, sig);
}