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
struct task_struct {int dummy; } ;
typedef  enum freezer_state { ____Placeholder_freezer_state } freezer_state ;
struct TYPE_2__ {int state; } ;

/* Variables and functions */
 int CGROUP_FREEZING ; 
 int CGROUP_FROZEN ; 
 TYPE_1__* task_freezer (struct task_struct*) ; 

__attribute__((used)) static inline int __cgroup_freezing_or_frozen(struct task_struct *task)
{
	enum freezer_state state = task_freezer(task)->state;
	return (state == CGROUP_FREEZING) || (state == CGROUP_FROZEN);
}