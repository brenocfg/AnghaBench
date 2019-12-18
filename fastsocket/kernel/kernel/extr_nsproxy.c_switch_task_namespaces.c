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
struct task_struct {struct nsproxy* nsproxy; } ;
struct nsproxy {int /*<<< orphan*/  count; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_nsproxy (struct nsproxy*) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  rcu_assign_pointer (struct nsproxy*,struct nsproxy*) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

void switch_task_namespaces(struct task_struct *p, struct nsproxy *new)
{
	struct nsproxy *ns;

	might_sleep();

	ns = p->nsproxy;

	rcu_assign_pointer(p->nsproxy, new);

	if (ns && atomic_dec_and_test(&ns->count)) {
		/*
		 * wait for others to get what they want from this nsproxy.
		 *
		 * cannot release this nsproxy via the call_rcu() since
		 * put_mnt_ns() will want to sleep
		 */
		synchronize_rcu();
		free_nsproxy(ns);
	}
}