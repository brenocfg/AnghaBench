#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int* __bits; } ;
typedef  TYPE_1__ sigset_t ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int SIG_BLOCK ; 
 int /*<<< orphan*/  SYS_rt_sigprocmask ; 
 int _NSIG ; 
 int __syscall (int /*<<< orphan*/ ,int,TYPE_1__ const*,TYPE_1__*,int) ; 

int pthread_sigmask(int how, const sigset_t *restrict set, sigset_t *restrict old)
{
	int ret;
	if ((unsigned)how - SIG_BLOCK > 2U) return EINVAL;
	ret = -__syscall(SYS_rt_sigprocmask, how, set, old, _NSIG/8);
	if (!ret && old) {
		if (sizeof old->__bits[0] == 8) {
			old->__bits[0] &= ~0x380000000ULL;
		} else {
			old->__bits[0] &= ~0x80000000UL;
			old->__bits[1] &= ~0x3UL;
		}
	}
	return ret;
}