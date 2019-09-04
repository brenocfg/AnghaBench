#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* processor_set_t ;
struct TYPE_5__ {int /*<<< orphan*/  runq_stats; int /*<<< orphan*/  queue; scalar_t__ count; } ;
struct TYPE_6__ {TYPE_1__ rt_runq; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  queue_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt_lock_init (TYPE_2__*) ; 

void
pset_rt_init(processor_set_t pset)
{
	rt_lock_init(pset);

	pset->rt_runq.count = 0;
	queue_init(&pset->rt_runq.queue);
	memset(&pset->rt_runq.runq_stats, 0, sizeof pset->rt_runq.runq_stats);
}