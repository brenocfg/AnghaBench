#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  cntxt_id; scalar_t__ desc; int /*<<< orphan*/  sdesc; int /*<<< orphan*/  in_use; } ;
struct sge_ofld_txq {TYPE_2__ q; int /*<<< orphan*/  sendq; int /*<<< orphan*/  qresume_tsk; } ;
struct TYPE_7__ {scalar_t__ desc; } ;
struct sge_ofld_rxq {int /*<<< orphan*/  fl; TYPE_4__ rspq; } ;
struct sge_eth_txq {TYPE_2__ q; } ;
struct sge_eth_rxq {int /*<<< orphan*/  fl; TYPE_4__ rspq; } ;
struct sge_ctrl_txq {TYPE_2__ q; int /*<<< orphan*/  sendq; int /*<<< orphan*/  qresume_tsk; } ;
struct TYPE_5__ {int ethqsets; int ofldqsets; int rdmaqs; int /*<<< orphan*/  egr_map; TYPE_4__ intrq; TYPE_4__ fw_evtq; struct sge_ofld_txq* ctrlq; struct sge_ofld_txq* ofldtxq; struct sge_ofld_rxq* rdmarxq; struct sge_ofld_rxq* ofldrxq; struct sge_eth_txq* ethtxq; struct sge_eth_rxq* ethrxq; } ;
struct adapter {TYPE_1__ sge; int /*<<< orphan*/  fn; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct sge_ofld_txq*) ; 
 int /*<<< orphan*/  __skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_rspq_fl (struct adapter*,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_tx_desc (struct adapter*,TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free_txq (struct adapter*,TYPE_2__*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  t4_ctrl_eq_free (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_eth_eq_free (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_ofld_eq_free (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

void t4_free_sge_resources(struct adapter *adap)
{
	int i;
	struct sge_eth_rxq *eq = adap->sge.ethrxq;
	struct sge_eth_txq *etq = adap->sge.ethtxq;
	struct sge_ofld_rxq *oq = adap->sge.ofldrxq;

	/* clean up Ethernet Tx/Rx queues */
	for (i = 0; i < adap->sge.ethqsets; i++, eq++, etq++) {
		if (eq->rspq.desc)
			free_rspq_fl(adap, &eq->rspq, &eq->fl);
		if (etq->q.desc) {
			t4_eth_eq_free(adap, adap->fn, adap->fn, 0,
				       etq->q.cntxt_id);
			free_tx_desc(adap, &etq->q, etq->q.in_use, true);
			kfree(etq->q.sdesc);
			free_txq(adap, &etq->q);
		}
	}

	/* clean up RDMA and iSCSI Rx queues */
	for (i = 0; i < adap->sge.ofldqsets; i++, oq++) {
		if (oq->rspq.desc)
			free_rspq_fl(adap, &oq->rspq, &oq->fl);
	}
	for (i = 0, oq = adap->sge.rdmarxq; i < adap->sge.rdmaqs; i++, oq++) {
		if (oq->rspq.desc)
			free_rspq_fl(adap, &oq->rspq, &oq->fl);
	}

	/* clean up offload Tx queues */
	for (i = 0; i < ARRAY_SIZE(adap->sge.ofldtxq); i++) {
		struct sge_ofld_txq *q = &adap->sge.ofldtxq[i];

		if (q->q.desc) {
			tasklet_kill(&q->qresume_tsk);
			t4_ofld_eq_free(adap, adap->fn, adap->fn, 0,
					q->q.cntxt_id);
			free_tx_desc(adap, &q->q, q->q.in_use, false);
			kfree(q->q.sdesc);
			__skb_queue_purge(&q->sendq);
			free_txq(adap, &q->q);
		}
	}

	/* clean up control Tx queues */
	for (i = 0; i < ARRAY_SIZE(adap->sge.ctrlq); i++) {
		struct sge_ctrl_txq *cq = &adap->sge.ctrlq[i];

		if (cq->q.desc) {
			tasklet_kill(&cq->qresume_tsk);
			t4_ctrl_eq_free(adap, adap->fn, adap->fn, 0,
					cq->q.cntxt_id);
			__skb_queue_purge(&cq->sendq);
			free_txq(adap, &cq->q);
		}
	}

	if (adap->sge.fw_evtq.desc)
		free_rspq_fl(adap, &adap->sge.fw_evtq, NULL);

	if (adap->sge.intrq.desc)
		free_rspq_fl(adap, &adap->sge.intrq, NULL);

	/* clear the reverse egress queue map */
	memset(adap->sge.egr_map, 0, sizeof(adap->sge.egr_map));
}