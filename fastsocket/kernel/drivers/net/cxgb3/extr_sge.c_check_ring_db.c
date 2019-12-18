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
struct sge_txq {scalar_t__ cleaned; scalar_t__ in_use; scalar_t__ processed; int /*<<< orphan*/  cntxt_id; int /*<<< orphan*/  flags; } ;
struct sge_qset {struct sge_txq* txq; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_SG_KDOORBELL ; 
 unsigned int F_RSPD_TXQ0_GTS ; 
 unsigned int F_RSPD_TXQ1_GTS ; 
 int F_SELEGRCNTX ; 
 size_t TXQ_ETH ; 
 int /*<<< orphan*/  TXQ_LAST_PKT_DB ; 
 size_t TXQ_OFLD ; 
 int /*<<< orphan*/  TXQ_RUNNING ; 
 int V_EGRCNTX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t3_write_reg (struct adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void check_ring_db(struct adapter *adap, struct sge_qset *qs,
			  unsigned int sleeping)
{
	if (sleeping & F_RSPD_TXQ0_GTS) {
		struct sge_txq *txq = &qs->txq[TXQ_ETH];

		if (txq->cleaned + txq->in_use != txq->processed &&
		    !test_and_set_bit(TXQ_LAST_PKT_DB, &txq->flags)) {
			set_bit(TXQ_RUNNING, &txq->flags);
			t3_write_reg(adap, A_SG_KDOORBELL, F_SELEGRCNTX |
				     V_EGRCNTX(txq->cntxt_id));
		}
	}

	if (sleeping & F_RSPD_TXQ1_GTS) {
		struct sge_txq *txq = &qs->txq[TXQ_OFLD];

		if (txq->cleaned + txq->in_use != txq->processed &&
		    !test_and_set_bit(TXQ_LAST_PKT_DB, &txq->flags)) {
			set_bit(TXQ_RUNNING, &txq->flags);
			t3_write_reg(adap, A_SG_KDOORBELL, F_SELEGRCNTX |
				     V_EGRCNTX(txq->cntxt_id));
		}
	}
}