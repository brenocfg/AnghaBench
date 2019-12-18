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
struct pid_namespace {scalar_t__ level; struct pid_namespace* parent; } ;
struct nsproxy {int /*<<< orphan*/  pid_ns; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  get_pid_ns (struct pid_namespace*) ; 
 int /*<<< orphan*/  put_pid_ns (int /*<<< orphan*/ ) ; 
 struct pid_namespace* task_active_pid_ns (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pidns_install(struct nsproxy *nsproxy, void *ns)
{
	struct pid_namespace *active = task_active_pid_ns(current);
	struct pid_namespace *ancestor, *new = ns;

	/*
	 * Only allow entering the current active pid namespace
	 * or a child of the current active pid namespace.
	 *
	 * This is required for fork to return a usable pid value and
	 * this maintains the property that processes and their
	 * children can not escape their current pid namespace.
	 */
	if (new->level < active->level)
		return -EINVAL;

	ancestor = new;
	while (ancestor->level > active->level)
		ancestor = ancestor->parent;
	if (ancestor != active)
		return -EINVAL;

	put_pid_ns(nsproxy->pid_ns);
	nsproxy->pid_ns = get_pid_ns(new);
	return 0;
}