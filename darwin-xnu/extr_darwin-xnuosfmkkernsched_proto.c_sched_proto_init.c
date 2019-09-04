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

/* Variables and functions */
 int /*<<< orphan*/ * global_runq ; 
 int /*<<< orphan*/  global_runq_lock ; 
 int /*<<< orphan*/  global_runq_storage ; 
 int /*<<< orphan*/  master_processor ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  proto_processor ; 
 int proto_quantum_us ; 
 int /*<<< orphan*/  run_queue_init (int /*<<< orphan*/ *) ; 
 scalar_t__ runqueue_generation ; 
 int /*<<< orphan*/  simple_lock_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sched_proto_init(void)
{
	proto_quantum_us = 10*1000;
	
	printf("standard proto timeslicing quantum is %d us\n", proto_quantum_us);

	simple_lock_init(&global_runq_lock, 0);
	global_runq = &global_runq_storage;
	run_queue_init(global_runq);
	runqueue_generation = 0;
	
	proto_processor = master_processor;
}