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
struct thread_info {scalar_t__ system_timer; } ;
struct task_struct {int dummy; } ;
typedef  scalar_t__ __u64 ;
struct TYPE_2__ {scalar_t__ system_timer; int /*<<< orphan*/  steal_timer; scalar_t__ last_update_timer; } ;

/* Variables and functions */
 TYPE_1__ S390_lowcore ; 
 int /*<<< orphan*/  account_system_time (struct task_struct*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ get_vtimer () ; 
 struct thread_info* task_thread_info (struct task_struct*) ; 

void account_system_vtime(struct task_struct *tsk)
{
	struct thread_info *ti = task_thread_info(tsk);
	__u64 timer, system;

	timer = S390_lowcore.last_update_timer;
	S390_lowcore.last_update_timer = get_vtimer();
	S390_lowcore.system_timer += timer - S390_lowcore.last_update_timer;

	system = S390_lowcore.system_timer - ti->system_timer;
	S390_lowcore.steal_timer -= system;
	ti->system_timer = S390_lowcore.system_timer;
	account_system_time(tsk, 0, system, system);
}