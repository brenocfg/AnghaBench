#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct task_struct {TYPE_1__* sighand; struct signal_struct* signal; } ;
struct signal_struct {TYPE_2__* it; } ;
typedef  int /*<<< orphan*/  cputime_t ;
struct TYPE_4__ {int /*<<< orphan*/  expires; } ;
struct TYPE_3__ {int /*<<< orphan*/  siglock; } ;

/* Variables and functions */
 size_t CPUCLOCK_PROF ; 
 scalar_t__ cputime_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cputime_gt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cputime_zero ; 
 int /*<<< orphan*/  secs_to_cputime (unsigned long) ; 
 int /*<<< orphan*/  set_process_cpu_timer (struct task_struct*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void update_rlimit_cpu(struct task_struct *task, unsigned long rlim_new)
{
	cputime_t cputime = secs_to_cputime(rlim_new);
	struct signal_struct *const sig = task->signal;

	if (cputime_eq(sig->it[CPUCLOCK_PROF].expires, cputime_zero) ||
	    cputime_gt(sig->it[CPUCLOCK_PROF].expires, cputime)) {
		spin_lock_irq(&task->sighand->siglock);
		set_process_cpu_timer(task, CPUCLOCK_PROF, &cputime, NULL);
		spin_unlock_irq(&task->sighand->siglock);
	}
}