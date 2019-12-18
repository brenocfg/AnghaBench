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
struct thread {int dummy; } ;
struct TYPE_2__ {struct machine* machine; } ;
struct machine {int /*<<< orphan*/ * root_dir; scalar_t__ pid; TYPE_1__ kmaps; int /*<<< orphan*/ * last_match; int /*<<< orphan*/  dead_threads; int /*<<< orphan*/  threads; int /*<<< orphan*/  kernel_dsos; int /*<<< orphan*/  user_dsos; int /*<<< orphan*/  rb_node; } ;
typedef  scalar_t__ pid_t ;
typedef  int /*<<< orphan*/  comm ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ HOST_KERNEL_ID ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RB_CLEAR_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RB_ROOT ; 
 struct thread* machine__findnew_thread (struct machine*,scalar_t__) ; 
 int /*<<< orphan*/  map_groups__init (TYPE_1__*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,scalar_t__) ; 
 int /*<<< orphan*/ * strdup (char const*) ; 
 int /*<<< orphan*/  thread__set_comm (struct thread*,char*) ; 

int machine__init(struct machine *machine, const char *root_dir, pid_t pid)
{
	map_groups__init(&machine->kmaps);
	RB_CLEAR_NODE(&machine->rb_node);
	INIT_LIST_HEAD(&machine->user_dsos);
	INIT_LIST_HEAD(&machine->kernel_dsos);

	machine->threads = RB_ROOT;
	INIT_LIST_HEAD(&machine->dead_threads);
	machine->last_match = NULL;

	machine->kmaps.machine = machine;
	machine->pid = pid;

	machine->root_dir = strdup(root_dir);
	if (machine->root_dir == NULL)
		return -ENOMEM;

	if (pid != HOST_KERNEL_ID) {
		struct thread *thread = machine__findnew_thread(machine, pid);
		char comm[64];

		if (thread == NULL)
			return -ENOMEM;

		snprintf(comm, sizeof(comm), "[guest/%d]", pid);
		thread__set_comm(thread, comm);
	}

	return 0;
}