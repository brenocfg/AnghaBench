#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  processor_t ;
struct TYPE_4__ {int count; } ;
struct TYPE_3__ {int count; } ;

/* Variables and functions */
 TYPE_2__* multiq_bound_runq (int /*<<< orphan*/ ) ; 
 TYPE_1__* multiq_main_entryq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sched_multiq_runq_count(processor_t processor)
{
	/*
	 *  TODO: Decide whether to keep a count of runnable threads in the pset
	 *  or just return something less than the true count.
	 *
	 *  This needs to be fast, so no iterating the whole runq.
	 *
	 *  Another possible decision is to remove this - with global runq
	 *  it doesn't make much sense.
	 */
	return multiq_main_entryq(processor)->count + multiq_bound_runq(processor)->count;
}