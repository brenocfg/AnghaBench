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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/ * len; int /*<<< orphan*/ * addr; } ;
struct veth_msg {int /*<<< orphan*/  token; TYPE_1__ data; int /*<<< orphan*/ * skb; int /*<<< orphan*/  dev; scalar_t__ in_use; } ;
struct veth_lpar_connection {int state; int /*<<< orphan*/  remote_lp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int VETH_STATE_OPEN ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  veth_error (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  veth_stack_push (struct veth_lpar_connection*,struct veth_msg*) ; 

__attribute__((used)) static void veth_recycle_msg(struct veth_lpar_connection *cnx,
			     struct veth_msg *msg)
{
	u32 dma_address, dma_length;

	if (msg->in_use) {
		msg->in_use = 0;
		dma_address = msg->data.addr[0];
		dma_length = msg->data.len[0];

		if (!dma_mapping_error(msg->dev, dma_address))
			dma_unmap_single(msg->dev, dma_address, dma_length,
					DMA_TO_DEVICE);

		if (msg->skb) {
			dev_kfree_skb_any(msg->skb);
			msg->skb = NULL;
		}

		memset(&msg->data, 0, sizeof(msg->data));
		veth_stack_push(cnx, msg);
	} else if (cnx->state & VETH_STATE_OPEN) {
		veth_error("Non-pending frame (# %d) acked by LPAR %d.\n",
				cnx->remote_lp, msg->token);
	}
}