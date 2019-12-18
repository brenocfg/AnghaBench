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
typedef  scalar_t__ u16 ;
struct be_rx_page_info {int /*<<< orphan*/  page; } ;
struct be_queue_info {scalar_t__ head; scalar_t__ len; scalar_t__ tail; int /*<<< orphan*/  used; int /*<<< orphan*/  id; } ;
struct be_rx_obj {struct be_adapter* adapter; struct be_queue_info cq; struct be_queue_info q; } ;
struct be_rx_compl_info {scalar_t__ num_rcvd; } ;
struct be_adapter {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (scalar_t__) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  be_cq_notify (struct be_adapter*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ be_hw_error (struct be_adapter*) ; 
 int /*<<< orphan*/  be_rx_compl_discard (struct be_rx_obj*,struct be_rx_compl_info*) ; 
 struct be_rx_compl_info* be_rx_compl_get (struct be_rx_obj*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 struct be_rx_page_info* get_rx_page_info (struct be_rx_obj*,scalar_t__) ; 
 int /*<<< orphan*/  index_inc (scalar_t__*,scalar_t__) ; 
 scalar_t__ lancer_chip (struct be_adapter*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  memset (struct be_rx_page_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void be_rx_cq_clean(struct be_rx_obj *rxo)
{
	struct be_rx_page_info *page_info;
	struct be_queue_info *rxq = &rxo->q;
	struct be_queue_info *rx_cq = &rxo->cq;
	struct be_rx_compl_info *rxcp;
	struct be_adapter *adapter = rxo->adapter;
	int flush_wait = 0;
	u16 tail;

	/* Consume pending rx completions.
	 * Wait for the flush completion (identified by zero num_rcvd)
	 * to arrive. Notify CQ even when there are no more CQ entries
	 * for HW to flush partially coalesced CQ entries.
	 * In Lancer, there is no need to wait for flush compl.
	 */
	for (;;) {
		rxcp = be_rx_compl_get(rxo);
		if (rxcp == NULL) {
			if (lancer_chip(adapter))
				break;

			if (flush_wait++ > 10 || be_hw_error(adapter)) {
				dev_warn(&adapter->pdev->dev,
					 "did not receive flush compl\n");
				break;
			}
			be_cq_notify(adapter, rx_cq->id, true, 0);
			mdelay(1);
		} else {
			be_rx_compl_discard(rxo, rxcp);
			be_cq_notify(adapter, rx_cq->id, false, 1);
			if (rxcp->num_rcvd == 0)
				break;
		}
	}

	/* After cleanup, leave the CQ in unarmed state */
	be_cq_notify(adapter, rx_cq->id, false, 0);

	/* Then free posted rx buffers that were not used */
	tail = (rxq->head + rxq->len - atomic_read(&rxq->used)) % rxq->len;
	for (; atomic_read(&rxq->used) > 0; index_inc(&tail, rxq->len)) {
		page_info = get_rx_page_info(rxo, tail);
		put_page(page_info->page);
		memset(page_info, 0, sizeof(*page_info));
	}
	BUG_ON(atomic_read(&rxq->used));
	rxq->tail = rxq->head = 0;
}