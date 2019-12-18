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
struct task_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sched_move_task (struct task_struct*) ; 

__attribute__((used)) static inline void sched_switch_user(struct task_struct *p)
{
#ifdef CONFIG_USER_SCHED
	sched_move_task(p);
#endif	/* CONFIG_USER_SCHED */
}