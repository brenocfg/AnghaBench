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
struct sigaction {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int _NSIG ; 
 int __libc_sigaction (int,struct sigaction const*,struct sigaction*) ; 
 int /*<<< orphan*/  errno ; 

int __sigaction(int sig, const struct sigaction *restrict sa, struct sigaction *restrict old)
{
	if (sig-32U < 3 || sig-1U >= _NSIG-1) {
		errno = EINVAL;
		return -1;
	}
	return __libc_sigaction(sig, sa, old);
}