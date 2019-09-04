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
struct sigaction {int /*<<< orphan*/  sa_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  SA_RESTART ; 
 int sigaction (int,struct sigaction*,struct sigaction*) ; 

int siginterrupt(int sig, int flag)
{
	struct sigaction sa;

	sigaction(sig, 0, &sa);
	if (flag) sa.sa_flags &= ~SA_RESTART;
	else sa.sa_flags |= SA_RESTART;

	return sigaction(sig, &sa, 0);
}