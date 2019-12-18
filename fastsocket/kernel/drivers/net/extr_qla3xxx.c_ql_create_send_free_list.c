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
struct ql_tx_buf_cb {int /*<<< orphan*/ * oal; struct ob_mac_iocb_req* queue_entry; int /*<<< orphan*/ * skb; } ;
struct ql3_adapter {struct ql_tx_buf_cb* tx_buf; struct ob_mac_iocb_req* req_q_virt_addr; } ;
struct ob_mac_iocb_req {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int NUM_REQ_Q_ENTRIES ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ql_create_send_free_list(struct ql3_adapter *qdev)
{
	struct ql_tx_buf_cb *tx_cb;
	int i;
	struct ob_mac_iocb_req *req_q_curr =
					qdev->req_q_virt_addr;

	/* Create free list of transmit buffers */
	for (i = 0; i < NUM_REQ_Q_ENTRIES; i++) {

		tx_cb = &qdev->tx_buf[i];
		tx_cb->skb = NULL;
		tx_cb->queue_entry = req_q_curr;
		req_q_curr++;
		tx_cb->oal = kmalloc(512, GFP_KERNEL);
		if (tx_cb->oal == NULL)
			return -1;
	}
	return 0;
}