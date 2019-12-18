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
struct thread_info {int /*<<< orphan*/  system_timer; int /*<<< orphan*/  user_timer; } ;
struct task_struct {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  system_timer; int /*<<< orphan*/  user_timer; } ;

/* Variables and functions */
 TYPE_1__ S390_lowcore ; 
 int /*<<< orphan*/  do_account_vtime (struct task_struct*,int /*<<< orphan*/ ) ; 
 struct thread_info* task_thread_info (struct task_struct*) ; 

void account_vtime(struct task_struct *prev, struct task_struct *next)
{
	struct thread_info *ti;

	do_account_vtime(prev, 0);
	ti = task_thread_info(prev);
	ti->user_timer = S390_lowcore.user_timer;
	ti->system_timer = S390_lowcore.system_timer;
	ti = task_thread_info(next);
	S390_lowcore.user_timer = ti->user_timer;
	S390_lowcore.system_timer = ti->system_timer;
}