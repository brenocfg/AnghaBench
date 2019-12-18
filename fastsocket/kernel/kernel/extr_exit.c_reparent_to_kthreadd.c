#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  usage; } ;
struct TYPE_15__ {TYPE_2__* signal; } ;
struct TYPE_14__ {int /*<<< orphan*/  children; } ;
struct TYPE_13__ {TYPE_1__* signal; int /*<<< orphan*/  exit_signal; TYPE_6__* real_parent; int /*<<< orphan*/  sibling; TYPE_6__* parent; } ;
struct TYPE_12__ {int /*<<< orphan*/  rlim; } ;
struct TYPE_11__ {int /*<<< orphan*/  rlim; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGCHLD ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  commit_creds (TYPE_8__*) ; 
 TYPE_3__* current ; 
 TYPE_8__ init_cred ; 
 TYPE_7__ init_task ; 
 TYPE_6__* kthreadd_task ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ptrace_unlink (TYPE_3__*) ; 
 int /*<<< orphan*/  set_user_nice (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ task_nice (TYPE_3__*) ; 
 int /*<<< orphan*/  tasklist_lock ; 
 int /*<<< orphan*/  write_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void reparent_to_kthreadd(void)
{
	write_lock_irq(&tasklist_lock);

	ptrace_unlink(current);
	/* Reparent to init */
	current->real_parent = current->parent = kthreadd_task;
	list_move_tail(&current->sibling, &current->real_parent->children);

	/* Set the exit signal to SIGCHLD so we signal init on exit */
	current->exit_signal = SIGCHLD;

	if (task_nice(current) < 0)
		set_user_nice(current, 0);
	/* cpus_allowed? */
	/* rt_priority? */
	/* signals? */
	memcpy(current->signal->rlim, init_task.signal->rlim,
	       sizeof(current->signal->rlim));

	atomic_inc(&init_cred.usage);
	commit_creds(&init_cred);
	write_unlock_irq(&tasklist_lock);
}