#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_purgeable_info_t ;
typedef  int /*<<< orphan*/  task_t ;
typedef  int /*<<< orphan*/ * purgeable_q_t ;
struct TYPE_3__ {int /*<<< orphan*/  obsolete_data; int /*<<< orphan*/ * lifo_data; int /*<<< orphan*/ * fifo_data; } ;

/* Variables and functions */
 int NUM_VOLATILE_GROUPS ; 
 size_t PURGEABLE_Q_TYPE_FIFO ; 
 size_t PURGEABLE_Q_TYPE_LIFO ; 
 size_t PURGEABLE_Q_TYPE_OBSOLETE ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * purgeable_queues ; 
 int /*<<< orphan*/  vm_purgeable_queue_lock ; 
 int /*<<< orphan*/  vm_purgeable_stats_helper (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

void
vm_purgeable_stats(vm_purgeable_info_t info, task_t target_task)
{
	purgeable_q_t	queue;
	int             group;

	lck_mtx_lock(&vm_purgeable_queue_lock);
	
	/* Populate fifo_data */
	queue = &purgeable_queues[PURGEABLE_Q_TYPE_FIFO];
	for (group = 0; group < NUM_VOLATILE_GROUPS; group++)
		vm_purgeable_stats_helper(&(info->fifo_data[group]), queue, group, target_task);
	
	/* Populate lifo_data */
	queue = &purgeable_queues[PURGEABLE_Q_TYPE_LIFO];
	for (group = 0; group < NUM_VOLATILE_GROUPS; group++)
		vm_purgeable_stats_helper(&(info->lifo_data[group]), queue, group, target_task);

	/* Populate obsolete data */
	queue = &purgeable_queues[PURGEABLE_Q_TYPE_OBSOLETE];
	vm_purgeable_stats_helper(&(info->obsolete_data), queue, 0, target_task);

	lck_mtx_unlock(&vm_purgeable_queue_lock);
	return;
}