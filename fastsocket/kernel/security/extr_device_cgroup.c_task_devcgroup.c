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
struct dev_cgroup {int dummy; } ;

/* Variables and functions */
 struct dev_cgroup* css_to_devcgroup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devices_subsys_id ; 
 int /*<<< orphan*/  task_subsys_state (struct task_struct*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct dev_cgroup *task_devcgroup(struct task_struct *task)
{
	return css_to_devcgroup(task_subsys_state(task, devices_subsys_id));
}