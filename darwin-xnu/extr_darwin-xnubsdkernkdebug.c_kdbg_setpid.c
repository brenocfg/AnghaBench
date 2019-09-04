#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct proc {int p_kdebug; } ;
typedef  scalar_t__ pid_t ;
struct TYPE_4__ {scalar_t__ value2; scalar_t__ value1; } ;
typedef  TYPE_1__ kd_regtype ;
struct TYPE_5__ {int /*<<< orphan*/  kdebug_flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int ESRCH ; 
 int /*<<< orphan*/  KDBG_PIDCHECK ; 
 int /*<<< orphan*/  KDBG_PIDEXCLUDE ; 
 int /*<<< orphan*/  SLOW_CHECKS ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_3__ kd_ctrl_page ; 
 int /*<<< orphan*/  kdbg_set_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct proc* proc_find (scalar_t__) ; 
 int /*<<< orphan*/  proc_rele (struct proc*) ; 

int
kdbg_setpid(kd_regtype *kdr)
{
	pid_t pid;
	int flag, ret=0;
	struct proc *p;

	pid = (pid_t)kdr->value1;
	flag = (int)kdr->value2;

	if (pid >= 0) {
		if ((p = proc_find(pid)) == NULL)
			ret = ESRCH;
		else {
			if (flag == 1) {
				/*
				 * turn on pid check for this and all pids
				 */
				kd_ctrl_page.kdebug_flags |= KDBG_PIDCHECK;
				kd_ctrl_page.kdebug_flags &= ~KDBG_PIDEXCLUDE;
				kdbg_set_flags(SLOW_CHECKS, 0, TRUE);

				p->p_kdebug = 1;
			} else {
				/*
				 * turn off pid check for this pid value
				 * Don't turn off all pid checking though
				 *
				 * kd_ctrl_page.kdebug_flags &= ~KDBG_PIDCHECK;
				 */   
				p->p_kdebug = 0;
			}
			proc_rele(p);
		}
	}
	else
		ret = EINVAL;

	return(ret);
}