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
struct task_struct {int /*<<< orphan*/  ptrace_entry; int /*<<< orphan*/  real_parent; int /*<<< orphan*/  parent; scalar_t__ ptrace; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptrace_untrace (struct task_struct*) ; 
 scalar_t__ task_is_traced (struct task_struct*) ; 

void __ptrace_unlink(struct task_struct *child)
{
	BUG_ON(!child->ptrace);

	child->ptrace = 0;
	child->parent = child->real_parent;
	list_del_init(&child->ptrace_entry);

	if (task_is_traced(child))
		ptrace_untrace(child);
}