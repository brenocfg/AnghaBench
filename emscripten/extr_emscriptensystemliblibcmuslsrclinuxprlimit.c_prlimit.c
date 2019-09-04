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
struct rlimit {int /*<<< orphan*/  rlim_max; int /*<<< orphan*/  rlim_cur; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  FIX (int /*<<< orphan*/ ) ; 
 scalar_t__ RLIM_INFINITY ; 
 scalar_t__ SYSCALL_RLIM_INFINITY ; 
 int /*<<< orphan*/  SYS_prlimit64 ; 
 int syscall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct rlimit const*,struct rlimit*) ; 

int prlimit(pid_t pid, int resource, const struct rlimit *new_limit, struct rlimit *old_limit)
{
	struct rlimit tmp;
	int r;
	if (new_limit && SYSCALL_RLIM_INFINITY != RLIM_INFINITY) {
		tmp = *new_limit;
		FIX(tmp.rlim_cur);
		FIX(tmp.rlim_max);
		new_limit = &tmp;
	}
	r = syscall(SYS_prlimit64, pid, resource, new_limit, old_limit);
	if (!r && old_limit && SYSCALL_RLIM_INFINITY != RLIM_INFINITY) {
		FIX(old_limit->rlim_cur);
		FIX(old_limit->rlim_max);
	}
	return r;
}