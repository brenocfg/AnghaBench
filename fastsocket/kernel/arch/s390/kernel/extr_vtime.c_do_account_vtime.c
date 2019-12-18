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
struct thread_info {scalar_t__ system_timer; scalar_t__ user_timer; } ;
struct task_struct {int dummy; } ;
typedef  scalar_t__ s64 ;
typedef  scalar_t__ __u64 ;
struct TYPE_2__ {scalar_t__ steal_timer; scalar_t__ system_timer; scalar_t__ user_timer; scalar_t__ last_update_clock; scalar_t__ last_update_timer; } ;

/* Variables and functions */
 TYPE_1__ S390_lowcore ; 
 int /*<<< orphan*/  account_steal_time (scalar_t__) ; 
 int /*<<< orphan*/  account_system_time (struct task_struct*,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  account_user_time (struct task_struct*,scalar_t__,scalar_t__) ; 
 struct thread_info* task_thread_info (struct task_struct*) ; 

__attribute__((used)) static void do_account_vtime(struct task_struct *tsk, int hardirq_offset)
{
	struct thread_info *ti = task_thread_info(tsk);
	__u64 timer, clock, user, system, steal;

	timer = S390_lowcore.last_update_timer;
	clock = S390_lowcore.last_update_clock;
	asm volatile ("  STPT %0\n"    /* Store current cpu timer value */
		      "  STCK %1"      /* Store current tod clock value */
		      : "=m" (S390_lowcore.last_update_timer),
		        "=m" (S390_lowcore.last_update_clock) );
	S390_lowcore.system_timer += timer - S390_lowcore.last_update_timer;
	S390_lowcore.steal_timer += S390_lowcore.last_update_clock - clock;

	user = S390_lowcore.user_timer - ti->user_timer;
	S390_lowcore.steal_timer -= user;
	ti->user_timer = S390_lowcore.user_timer;
	account_user_time(tsk, user, user);

	system = S390_lowcore.system_timer - ti->system_timer;
	S390_lowcore.steal_timer -= system;
	ti->system_timer = S390_lowcore.system_timer;
	account_system_time(tsk, hardirq_offset, system, system);

	steal = S390_lowcore.steal_timer;
	if ((s64) steal > 0) {
		S390_lowcore.steal_timer = 0;
		account_steal_time(steal);
	}
}