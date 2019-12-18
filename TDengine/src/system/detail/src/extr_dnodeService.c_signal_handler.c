#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  si_pid; } ;
typedef  TYPE_1__ siginfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int SIGUSR1 ; 
 int SIGUSR2 ; 
 int /*<<< orphan*/  closelog () ; 
 int /*<<< orphan*/  dPrint (char*,...) ; 
 int /*<<< orphan*/  dnodeCleanUpSystem () ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  tsCfgDynamicOptions (char*) ; 

void signal_handler(int signum, siginfo_t *sigInfo, void *context) {
  if (signum == SIGUSR1) {
    tsCfgDynamicOptions("debugFlag 135");
    return;
  }
  if (signum == SIGUSR2) {
    tsCfgDynamicOptions("resetlog");
    return;
  }
  syslog(LOG_INFO, "Shut down signal is %d", signum);
  syslog(LOG_INFO, "Shutting down TDengine service...");
  // clean the system.
  dPrint("shut down signal is %d, sender PID:%d", signum, sigInfo->si_pid);
  dnodeCleanUpSystem();
  // close the syslog
  syslog(LOG_INFO, "Shut down TDengine service successfully");
  dPrint("TDengine is shut down!");
  closelog();
  exit(EXIT_SUCCESS);
}