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
struct task_struct {TYPE_1__* pids; } ;
typedef  enum pid_type { ____Placeholder_pid_type } pid_type ;
struct TYPE_2__ {int /*<<< orphan*/  node; int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  hlist_replace_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void transfer_pid(struct task_struct *old, struct task_struct *new,
			   enum pid_type type)
{
	new->pids[type].pid = old->pids[type].pid;
	hlist_replace_rcu(&old->pids[type].node, &new->pids[type].node);
}