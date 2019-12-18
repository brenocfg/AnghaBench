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
struct TYPE_3__ {int /*<<< orphan*/ * psets; } ;

/* Variables and functions */
 int /*<<< orphan*/  corpse_tasks ; 
 int /*<<< orphan*/  cpu_to_processor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  master_cpu ; 
 int /*<<< orphan*/  master_processor ; 
 int /*<<< orphan*/  processor_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  processor_list_lock ; 
 int /*<<< orphan*/  pset0 ; 
 int /*<<< orphan*/  pset_init (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__ pset_node0 ; 
 int /*<<< orphan*/  pset_node_lock ; 
 int /*<<< orphan*/  queue_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_lock_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasks ; 
 int /*<<< orphan*/  terminated_tasks ; 
 int /*<<< orphan*/  threads ; 

void
processor_bootstrap(void)
{
	pset_init(&pset0, &pset_node0);
	pset_node0.psets = &pset0;

	simple_lock_init(&pset_node_lock, 0);

	queue_init(&tasks);
	queue_init(&terminated_tasks);
	queue_init(&threads);
	queue_init(&corpse_tasks);

	simple_lock_init(&processor_list_lock, 0);

	master_processor = cpu_to_processor(master_cpu);

	processor_init(master_processor, master_cpu, &pset0);
}