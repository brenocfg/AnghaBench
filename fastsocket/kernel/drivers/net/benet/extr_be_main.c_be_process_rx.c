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
typedef  int u32 ;
struct napi_struct {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  used; } ;
struct be_queue_info {int /*<<< orphan*/  id; } ;
struct be_rx_obj {TYPE_1__ q; struct be_queue_info cq; struct be_adapter* adapter; } ;
struct be_rx_compl_info {scalar_t__ num_rcvd; scalar_t__ port; int /*<<< orphan*/  pkt_size; } ;
struct be_adapter {scalar_t__ port_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ RX_FRAGS_REFILL_WM ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  be_cq_notify (struct be_adapter*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  be_post_rx_frags (struct be_rx_obj*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be_rx_compl_discard (struct be_rx_obj*,struct be_rx_compl_info*) ; 
 struct be_rx_compl_info* be_rx_compl_get (struct be_rx_obj*) ; 
 int /*<<< orphan*/  be_rx_compl_process (struct be_rx_obj*,struct be_rx_compl_info*) ; 
 int /*<<< orphan*/  be_rx_compl_process_gro (struct be_rx_obj*,struct napi_struct*,struct be_rx_compl_info*) ; 
 int /*<<< orphan*/  be_rx_stats_update (struct be_rx_obj*,struct be_rx_compl_info*) ; 
 scalar_t__ do_gro (struct be_rx_compl_info*) ; 
 int /*<<< orphan*/  lancer_chip (struct be_adapter*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int be_process_rx(struct be_rx_obj *rxo, struct napi_struct *napi,
			int budget)
{
	struct be_adapter *adapter = rxo->adapter;
	struct be_queue_info *rx_cq = &rxo->cq;
	struct be_rx_compl_info *rxcp;
	u32 work_done;

	for (work_done = 0; work_done < budget; work_done++) {
		rxcp = be_rx_compl_get(rxo);
		if (!rxcp)
			break;

		/* Is it a flush compl that has no data */
		if (unlikely(rxcp->num_rcvd == 0))
			goto loop_continue;

		/* Discard compl with partial DMA Lancer B0 */
		if (unlikely(!rxcp->pkt_size)) {
			be_rx_compl_discard(rxo, rxcp);
			goto loop_continue;
		}

		/* On BE drop pkts that arrive due to imperfect filtering in
		 * promiscuous mode on some skews
		 */
		if (unlikely(rxcp->port != adapter->port_num &&
				!lancer_chip(adapter))) {
			be_rx_compl_discard(rxo, rxcp);
			goto loop_continue;
		}

		if (do_gro(rxcp))
			be_rx_compl_process_gro(rxo, napi, rxcp);
		else
			be_rx_compl_process(rxo, rxcp);
loop_continue:
		be_rx_stats_update(rxo, rxcp);
	}

	if (work_done) {
		be_cq_notify(adapter, rx_cq->id, true, work_done);

		if (atomic_read(&rxo->q.used) < RX_FRAGS_REFILL_WM)
			be_post_rx_frags(rxo, GFP_ATOMIC);
	}

	return work_done;
}