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
struct TYPE_3__ {scalar_t__ desc; } ;
struct sge_ofld_txq {int /*<<< orphan*/  qresume_tsk; TYPE_1__ q; } ;
struct sge_ctrl_txq {int /*<<< orphan*/  qresume_tsk; TYPE_1__ q; } ;
struct TYPE_4__ {scalar_t__ function; } ;
struct sge {struct sge_ofld_txq* ctrlq; struct sge_ofld_txq* ofldtxq; TYPE_2__ tx_timer; TYPE_2__ rx_timer; } ;
struct adapter {struct sge sge; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct sge_ofld_txq*) ; 
 int /*<<< orphan*/  del_timer_sync (TYPE_2__*) ; 
 scalar_t__ in_interrupt () ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

void t4_sge_stop(struct adapter *adap)
{
	int i;
	struct sge *s = &adap->sge;

	if (in_interrupt())  /* actions below require waiting */
		return;

	if (s->rx_timer.function)
		del_timer_sync(&s->rx_timer);
	if (s->tx_timer.function)
		del_timer_sync(&s->tx_timer);

	for (i = 0; i < ARRAY_SIZE(s->ofldtxq); i++) {
		struct sge_ofld_txq *q = &s->ofldtxq[i];

		if (q->q.desc)
			tasklet_kill(&q->qresume_tsk);
	}
	for (i = 0; i < ARRAY_SIZE(s->ctrlq); i++) {
		struct sge_ctrl_txq *cq = &s->ctrlq[i];

		if (cq->q.desc)
			tasklet_kill(&cq->qresume_tsk);
	}
}