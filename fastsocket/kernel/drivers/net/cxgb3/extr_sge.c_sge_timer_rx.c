#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_11__ {int cntxt_id; int /*<<< orphan*/  restarted; scalar_t__ credits; int /*<<< orphan*/  starved; int /*<<< orphan*/  lock; } ;
struct sge_qset {int /*<<< orphan*/  rx_reclaim_timer; TYPE_6__* fl; TYPE_5__ rspq; int /*<<< orphan*/  napi; int /*<<< orphan*/  netdev; } ;
struct port_info {struct adapter* adapter; } ;
struct TYPE_10__ {int rev; } ;
struct TYPE_9__ {TYPE_2__* qs; } ;
struct adapter {TYPE_4__ params; TYPE_3__ sge; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
struct TYPE_12__ {scalar_t__ credits; scalar_t__ size; } ;
struct TYPE_7__ {int /*<<< orphan*/  lock; } ;
struct TYPE_8__ {TYPE_1__ rspq; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_SG_RSPQ_FL_STATUS ; 
 scalar_t__ RX_RECLAIM_PERIOD ; 
 int /*<<< orphan*/  __refill_fl (struct adapter*,TYPE_6__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ napi_is_scheduled (int /*<<< orphan*/ *) ; 
 struct port_info* netdev_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refill_rspq (struct adapter*,TYPE_5__*,int) ; 
 int /*<<< orphan*/  spin_trylock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int t3_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t3_write_reg (struct adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sge_timer_rx(unsigned long data)
{
	spinlock_t *lock;
	struct sge_qset *qs = (struct sge_qset *)data;
	struct port_info *pi = netdev_priv(qs->netdev);
	struct adapter *adap = pi->adapter;
	u32 status;

	lock = adap->params.rev > 0 ?
	       &qs->rspq.lock : &adap->sge.qs[0].rspq.lock;

	if (!spin_trylock_irq(lock))
		goto out;

	if (napi_is_scheduled(&qs->napi))
		goto unlock;

	if (adap->params.rev < 4) {
		status = t3_read_reg(adap, A_SG_RSPQ_FL_STATUS);

		if (status & (1 << qs->rspq.cntxt_id)) {
			qs->rspq.starved++;
			if (qs->rspq.credits) {
				qs->rspq.credits--;
				refill_rspq(adap, &qs->rspq, 1);
				qs->rspq.restarted++;
				t3_write_reg(adap, A_SG_RSPQ_FL_STATUS,
					     1 << qs->rspq.cntxt_id);
			}
		}
	}

	if (qs->fl[0].credits < qs->fl[0].size)
		__refill_fl(adap, &qs->fl[0]);
	if (qs->fl[1].credits < qs->fl[1].size)
		__refill_fl(adap, &qs->fl[1]);

unlock:
	spin_unlock_irq(lock);
out:
	mod_timer(&qs->rx_reclaim_timer, jiffies + RX_RECLAIM_PERIOD);
}