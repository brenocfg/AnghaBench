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
struct cfq_data {int /*<<< orphan*/  unplug_work; int /*<<< orphan*/  queue; scalar_t__ busy_queues; } ;

/* Variables and functions */
 int /*<<< orphan*/  cfq_log (struct cfq_data*,char*) ; 
 int /*<<< orphan*/  kblockd_schedule_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void cfq_schedule_dispatch(struct cfq_data *cfqd)
{
	if (cfqd->busy_queues) {
		cfq_log(cfqd, "schedule dispatch");
		kblockd_schedule_work(cfqd->queue, &cfqd->unplug_work);
	}
}