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
struct rlimit {unsigned long rlim_cur; unsigned long rlim_max; } ;

/* Variables and functions */
 scalar_t__ ENOSYS ; 
 int /*<<< orphan*/  FIX (unsigned long) ; 
 unsigned long RLIM_INFINITY ; 
 int /*<<< orphan*/  SYS_getrlimit ; 
 int /*<<< orphan*/  SYS_prlimit64 ; 
 scalar_t__ errno ; 
 scalar_t__ syscall (int /*<<< orphan*/ ,int,...) ; 

int getrlimit(int resource, struct rlimit *rlim)
{
	unsigned long k_rlim[2];
	int ret = syscall(SYS_prlimit64, 0, resource, 0, rlim);
	if (!ret) {
		FIX(rlim->rlim_cur);
		FIX(rlim->rlim_max);
	}
	if (!ret || errno != ENOSYS)
		return ret;
	if (syscall(SYS_getrlimit, resource, k_rlim) < 0)
		return -1;
	rlim->rlim_cur = k_rlim[0] == -1UL ? RLIM_INFINITY : k_rlim[0];
	rlim->rlim_max = k_rlim[1] == -1UL ? RLIM_INFINITY : k_rlim[1];
	FIX(rlim->rlim_cur);
	FIX(rlim->rlim_max);
	return 0;
}