#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* thread_t ;
struct TYPE_5__ {int /*<<< orphan*/  options; } ;

/* Variables and functions */
 scalar_t__ MAX_VM_BIND_GROUP_COUNT ; 
 int /*<<< orphan*/  THREAD_CONTINUE_NULL ; 
 int /*<<< orphan*/  TH_OPT_SCHED_VM_GROUP ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* current_thread () ; 
 int /*<<< orphan*/  master_processor ; 
 int /*<<< orphan*/  sched_vm_group_list_lock ; 
 scalar_t__ sched_vm_group_thread_count ; 
 TYPE_1__** sched_vm_group_thread_list ; 
 int /*<<< orphan*/  simple_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_bind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_block (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_reference_internal (TYPE_1__*) ; 

void
thread_vm_bind_group_add(void)
{
	thread_t self = current_thread();

	thread_reference_internal(self);
	self->options |= TH_OPT_SCHED_VM_GROUP;

	simple_lock(&sched_vm_group_list_lock);
	assert(sched_vm_group_thread_count < MAX_VM_BIND_GROUP_COUNT);
	sched_vm_group_thread_list[sched_vm_group_thread_count++] = self;
	simple_unlock(&sched_vm_group_list_lock);

	thread_bind(master_processor);

	/* Switch to bound processor if not already there */
	thread_block(THREAD_CONTINUE_NULL);
}