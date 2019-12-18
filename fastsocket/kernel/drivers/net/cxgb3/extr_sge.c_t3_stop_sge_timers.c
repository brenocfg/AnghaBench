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
struct TYPE_4__ {scalar_t__ function; } ;
struct sge_qset {TYPE_2__ rx_reclaim_timer; TYPE_2__ tx_reclaim_timer; } ;
struct TYPE_3__ {struct sge_qset* qs; } ;
struct adapter {TYPE_1__ sge; } ;

/* Variables and functions */
 int SGE_QSETS ; 
 int /*<<< orphan*/  del_timer_sync (TYPE_2__*) ; 

void t3_stop_sge_timers(struct adapter *adap)
{
	int i;

	for (i = 0; i < SGE_QSETS; ++i) {
		struct sge_qset *q = &adap->sge.qs[i];

		if (q->tx_reclaim_timer.function)
			del_timer_sync(&q->tx_reclaim_timer);
		if (q->rx_reclaim_timer.function)
			del_timer_sync(&q->rx_reclaim_timer);
	}
}