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
struct ql_rcv_buf_cb {int /*<<< orphan*/  buf_phy_addr_low; int /*<<< orphan*/  buf_phy_addr_high; } ;
struct ql3_adapter {int num_large_buffers; scalar_t__ lrg_buf_skb_check; scalar_t__ lrg_buf_index; struct ql_rcv_buf_cb* lrg_buf; struct bufq_addr_element* lrg_buf_q_virt_addr; } ;
struct bufq_addr_element {int /*<<< orphan*/  addr_low; int /*<<< orphan*/  addr_high; } ;

/* Variables and functions */

__attribute__((used)) static void ql_init_large_buffers(struct ql3_adapter *qdev)
{
	int i;
	struct ql_rcv_buf_cb *lrg_buf_cb;
	struct bufq_addr_element *buf_addr_ele = qdev->lrg_buf_q_virt_addr;

	for (i = 0; i < qdev->num_large_buffers; i++) {
		lrg_buf_cb = &qdev->lrg_buf[i];
		buf_addr_ele->addr_high = lrg_buf_cb->buf_phy_addr_high;
		buf_addr_ele->addr_low = lrg_buf_cb->buf_phy_addr_low;
		buf_addr_ele++;
	}
	qdev->lrg_buf_index = 0;
	qdev->lrg_buf_skb_check = 0;
}