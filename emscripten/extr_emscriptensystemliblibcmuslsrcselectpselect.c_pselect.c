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
typedef  uintptr_t syscall_arg_t ;
struct timespec {int dummy; } ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_pselect6 ; 
 int _NSIG ; 
 int syscall_cp (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timespec*,uintptr_t*) ; 

int pselect(int n, fd_set *restrict rfds, fd_set *restrict wfds, fd_set *restrict efds, const struct timespec *restrict ts, const sigset_t *restrict mask)
{
	syscall_arg_t data[2] = { (uintptr_t)mask, _NSIG/8 };
	struct timespec ts_tmp;
	if (ts) ts_tmp = *ts;
	return syscall_cp(SYS_pselect6, n, rfds, wfds, efds, ts ? &ts_tmp : 0, data);
}