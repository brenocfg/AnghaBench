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
typedef  void* u64 ;
struct qib_ibport {int /*<<< orphan*/  lock; int /*<<< orphan*/  pma_sample_interval; } ;
struct qib_pportdata {struct qib_ibport ibport_data; TYPE_1__* dd; } ;
struct qib_chip_specific {scalar_t__ pma_sample_status; void* sword; void* rword; void* spkts; void* rpkts; void* xmit_wait; int /*<<< orphan*/  pma_timer; } ;
struct TYPE_2__ {struct qib_chip_specific* cspec; } ;

/* Variables and functions */
 scalar_t__ IB_PMA_SAMPLE_STATUS_DONE ; 
 scalar_t__ IB_PMA_SAMPLE_STATUS_RUNNING ; 
 scalar_t__ IB_PMA_SAMPLE_STATUS_STARTED ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  qib_snapshot_counters (struct qib_pportdata*,void**,void**,void**,void**,void**) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ usecs_to_jiffies (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pma_6120_timer(unsigned long data)
{
	struct qib_pportdata *ppd = (struct qib_pportdata *)data;
	struct qib_chip_specific *cs = ppd->dd->cspec;
	struct qib_ibport *ibp = &ppd->ibport_data;
	unsigned long flags;

	spin_lock_irqsave(&ibp->lock, flags);
	if (cs->pma_sample_status == IB_PMA_SAMPLE_STATUS_STARTED) {
		cs->pma_sample_status = IB_PMA_SAMPLE_STATUS_RUNNING;
		qib_snapshot_counters(ppd, &cs->sword, &cs->rword,
				      &cs->spkts, &cs->rpkts, &cs->xmit_wait);
		mod_timer(&cs->pma_timer,
			  jiffies + usecs_to_jiffies(ibp->pma_sample_interval));
	} else if (cs->pma_sample_status == IB_PMA_SAMPLE_STATUS_RUNNING) {
		u64 ta, tb, tc, td, te;

		cs->pma_sample_status = IB_PMA_SAMPLE_STATUS_DONE;
		qib_snapshot_counters(ppd, &ta, &tb, &tc, &td, &te);

		cs->sword = ta - cs->sword;
		cs->rword = tb - cs->rword;
		cs->spkts = tc - cs->spkts;
		cs->rpkts = td - cs->rpkts;
		cs->xmit_wait = te - cs->xmit_wait;
	}
	spin_unlock_irqrestore(&ibp->lock, flags);
}