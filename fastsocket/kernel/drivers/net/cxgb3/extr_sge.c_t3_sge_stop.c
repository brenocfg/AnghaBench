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
struct sge_qset {TYPE_2__* txq; } ;
struct TYPE_3__ {struct sge_qset* qs; } ;
struct adapter {TYPE_1__ sge; } ;
struct TYPE_4__ {int /*<<< orphan*/  qresume_tsk; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_SG_CONTROL ; 
 int /*<<< orphan*/  F_GLOBALENABLE ; 
 int SGE_QSETS ; 
 size_t TXQ_CTRL ; 
 size_t TXQ_OFLD ; 
 int /*<<< orphan*/  in_interrupt () ; 
 int /*<<< orphan*/  t3_set_reg_field (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

void t3_sge_stop(struct adapter *adap)
{
	t3_set_reg_field(adap, A_SG_CONTROL, F_GLOBALENABLE, 0);
	if (!in_interrupt()) {
		int i;

		for (i = 0; i < SGE_QSETS; ++i) {
			struct sge_qset *qs = &adap->sge.qs[i];

			tasklet_kill(&qs->txq[TXQ_OFLD].qresume_tsk);
			tasklet_kill(&qs->txq[TXQ_CTRL].qresume_tsk);
		}
	}
}