#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct task_struct {TYPE_1__* signal; } ;
struct TYPE_2__ {scalar_t__ leader; } ;

/* Variables and functions */
 struct task_struct* current ; 
 int /*<<< orphan*/  disassociate_ctty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  proc_clear_tty (struct task_struct*) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

void no_tty(void)
{
	struct task_struct *tsk = current;
	lock_kernel();
	if (tsk->signal->leader)
		disassociate_ctty(0);
	unlock_kernel();
	proc_clear_tty(tsk);
}