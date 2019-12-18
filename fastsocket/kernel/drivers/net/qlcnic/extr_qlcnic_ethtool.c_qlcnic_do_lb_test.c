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
typedef  scalar_t__ u8 ;
struct sk_buff {int /*<<< orphan*/  data; } ;
struct qlcnic_recv_context {struct qlcnic_host_sds_ring* sds_rings; } ;
struct qlcnic_host_sds_ring {int dummy; } ;
struct qlcnic_adapter {TYPE_2__* pdev; TYPE_1__* ahw; int /*<<< orphan*/  netdev; int /*<<< orphan*/  mac_addr; struct qlcnic_recv_context* recv_ctx; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {scalar_t__ diag_cnt; } ;

/* Variables and functions */
 scalar_t__ QLCNIC_ILB_MODE ; 
 int /*<<< orphan*/  QLCNIC_ILB_PKT_SIZE ; 
 int /*<<< orphan*/  QLCNIC_LB_PKT_POLL_COUNT ; 
 int /*<<< orphan*/  QLCNIC_LB_PKT_POLL_DELAY_MSEC ; 
 int QLCNIC_NUM_ILB_PKT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 struct sk_buff* netdev_alloc_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_create_loopback_buff (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_process_rcv_ring_diag (struct qlcnic_host_sds_ring*) ; 
 int /*<<< orphan*/  qlcnic_xmit_frame (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int /*<<< orphan*/ ) ; 

int qlcnic_do_lb_test(struct qlcnic_adapter *adapter, u8 mode)
{
	struct qlcnic_recv_context *recv_ctx = adapter->recv_ctx;
	struct qlcnic_host_sds_ring *sds_ring = &recv_ctx->sds_rings[0];
	struct sk_buff *skb;
	int i, loop, cnt = 0;

	for (i = 0; i < QLCNIC_NUM_ILB_PKT; i++) {
		skb = netdev_alloc_skb(adapter->netdev, QLCNIC_ILB_PKT_SIZE);
		qlcnic_create_loopback_buff(skb->data, adapter->mac_addr);
		skb_put(skb, QLCNIC_ILB_PKT_SIZE);

		adapter->ahw->diag_cnt = 0;
		qlcnic_xmit_frame(skb, adapter->netdev);

		loop = 0;
		do {
			msleep(QLCNIC_LB_PKT_POLL_DELAY_MSEC);
			qlcnic_process_rcv_ring_diag(sds_ring);
			if (loop++ > QLCNIC_LB_PKT_POLL_COUNT)
				break;
		} while (!adapter->ahw->diag_cnt);

		dev_kfree_skb_any(skb);

		if (!adapter->ahw->diag_cnt)
			dev_warn(&adapter->pdev->dev,
				 "LB Test: packet #%d was not received\n",
				 i + 1);
		else
			cnt++;
	}
	if (cnt != i) {
		dev_err(&adapter->pdev->dev,
			"LB Test: failed, TX[%d], RX[%d]\n", i, cnt);
		if (mode != QLCNIC_ILB_MODE)
			dev_warn(&adapter->pdev->dev,
				 "WARNING: Please check loopback cable\n");
		return -1;
	}
	return 0;
}