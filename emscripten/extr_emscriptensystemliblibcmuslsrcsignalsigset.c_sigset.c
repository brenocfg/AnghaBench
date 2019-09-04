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
struct sigaction {void (* sa_handler ) (int) ;int /*<<< orphan*/  sa_mask; scalar_t__ sa_flags; } ;
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIG_BLOCK ; 
 void SIG_ERR (int) ; 
 void SIG_HOLD (int) ; 
 int /*<<< orphan*/  SIG_UNBLOCK ; 
 scalar_t__ sigaction (int,struct sigaction*,struct sigaction*) ; 
 scalar_t__ sigaddset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 scalar_t__ sigismember (int /*<<< orphan*/ *,int) ; 
 scalar_t__ sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void (*sigset(int sig, void (*handler)(int)))(int)
{
	struct sigaction sa, sa_old;
	sigset_t mask;

	sigemptyset(&mask);
	if (sigaddset(&mask, sig) < 0)
		return SIG_ERR;
	
	if (handler == SIG_HOLD) {
		if (sigaction(sig, 0, &sa_old) < 0)
			return SIG_ERR;
		if (sigprocmask(SIG_BLOCK, &mask, &mask) < 0)
			return SIG_ERR;
	} else {
		sa.sa_handler = handler;
		sa.sa_flags = 0;
		sigemptyset(&sa.sa_mask);
		if (sigaction(sig, &sa, &sa_old) < 0)
			return SIG_ERR;
		if (sigprocmask(SIG_UNBLOCK, &mask, &mask) < 0)
			return SIG_ERR;
	}
	return sigismember(&mask, sig) ? SIG_HOLD : sa_old.sa_handler;
}