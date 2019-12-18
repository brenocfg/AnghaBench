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
struct cfq_queue {TYPE_1__* cfqg; } ;
struct cfq_data {int /*<<< orphan*/  idle_slice_timer; } ;
struct TYPE_2__ {int /*<<< orphan*/  blkg; } ;

/* Variables and functions */
 int /*<<< orphan*/  cfq_blkiocg_update_idle_time_stats (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void cfq_del_timer(struct cfq_data *cfqd, struct cfq_queue *cfqq)
{
	del_timer(&cfqd->idle_slice_timer);
	cfq_blkiocg_update_idle_time_stats(&cfqq->cfqg->blkg);
}