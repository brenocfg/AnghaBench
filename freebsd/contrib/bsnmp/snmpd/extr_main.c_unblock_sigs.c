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
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int /*<<< orphan*/  blocked_sigs ; 
 int /*<<< orphan*/  exit (int) ; 
 int sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
unblock_sigs(void)
{
	if (sigprocmask(SIG_SETMASK, &blocked_sigs, NULL) == -1) {
		syslog(LOG_ERR, "SIG_SETMASK: %m");
		exit(1);
	}
}