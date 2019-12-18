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
 scalar_t__ RX_RECLAIM_PERIOD ; 
 int SGE_QSETS ; 
 scalar_t__ TX_RECLAIM_PERIOD ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (TYPE_2__*,scalar_t__) ; 

void t3_start_sge_timers(struct adapter *adap)
{
	int i;

	for (i = 0; i < SGE_QSETS; ++i) {
		struct sge_qset *q = &adap->sge.qs[i];

	if (q->tx_reclaim_timer.function)
		mod_timer(&q->tx_reclaim_timer, jiffies + TX_RECLAIM_PERIOD);

	if (q->rx_reclaim_timer.function)
		mod_timer(&q->rx_reclaim_timer, jiffies + RX_RECLAIM_PERIOD);
	}
}