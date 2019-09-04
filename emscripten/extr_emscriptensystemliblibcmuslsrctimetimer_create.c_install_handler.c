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
struct sigaction {int sa_flags; int /*<<< orphan*/  sa_sigaction; } ;

/* Variables and functions */
 int SA_RESTART ; 
 int SA_SIGINFO ; 
 int /*<<< orphan*/  SIGTIMER ; 
 int /*<<< orphan*/  __libc_sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_handler ; 

__attribute__((used)) static void install_handler()
{
	struct sigaction sa = {
		.sa_sigaction = timer_handler,
		.sa_flags = SA_SIGINFO | SA_RESTART
	};
	__libc_sigaction(SIGTIMER, &sa, 0);
}