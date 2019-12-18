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
typedef  int /*<<< orphan*/  u_int32_t ;
struct proc {int /*<<< orphan*/  p_fpdrainwait; } ;

/* Variables and functions */
 int /*<<< orphan*/  proc_fdlock (struct proc*) ; 
 int /*<<< orphan*/  proc_fdunlock (struct proc*) ; 
 int seldrop_locked (struct proc*,int /*<<< orphan*/ *,int,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
seldrop(struct proc *p, u_int32_t *ibits, int nfd)
{
	int error;
	int need_wakeup = 0;

	proc_fdlock(p);
	error =  seldrop_locked(p, ibits, nfd, nfd, &need_wakeup, 0);
	proc_fdunlock(p);
	if (need_wakeup) {
		wakeup(&p->p_fpdrainwait);
	}
	return (error);
}