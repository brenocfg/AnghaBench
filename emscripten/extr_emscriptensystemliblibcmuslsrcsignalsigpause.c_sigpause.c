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
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 int /*<<< orphan*/  sigdelset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int sigsuspend (int /*<<< orphan*/ *) ; 

int sigpause(int sig)
{
	sigset_t mask;
	sigprocmask(0, 0, &mask);
	sigdelset(&mask, sig);
	return sigsuspend(&mask);
}