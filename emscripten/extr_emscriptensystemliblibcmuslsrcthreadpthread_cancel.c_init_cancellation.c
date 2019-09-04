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
struct sigaction {int sa_flags; int /*<<< orphan*/  sa_mask; int /*<<< orphan*/  sa_sigaction; } ;

/* Variables and functions */
 int SA_RESTART ; 
 int SA_SIGINFO ; 
 int /*<<< orphan*/  SIGCANCEL ; 
 int _NSIG ; 
 int /*<<< orphan*/  __libc_sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_handler ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void init_cancellation()
{
	struct sigaction sa = {
		.sa_flags = SA_SIGINFO | SA_RESTART,
		.sa_sigaction = cancel_handler
	};
	memset(&sa.sa_mask, -1, _NSIG/8);
	__libc_sigaction(SIGCANCEL, &sa, 0);
}