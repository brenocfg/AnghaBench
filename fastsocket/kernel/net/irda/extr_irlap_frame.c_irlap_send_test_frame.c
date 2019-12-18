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
struct test_frame {int control; scalar_t__ caddr; void* daddr; void* saddr; } ;
struct sk_buff {int len; int /*<<< orphan*/  data; } ;
struct irlap_cb {int /*<<< orphan*/  qos_tx; int /*<<< orphan*/  saddr; } ;
typedef  scalar_t__ __u8 ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 scalar_t__ CBROADCAST ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int LAP_ADDR_HEADER ; 
 int LAP_CTRL_HEADER ; 
 int PF_BIT ; 
 int TEST_RSP ; 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irlap_queue_xmit (struct irlap_cb*,struct sk_buff*) ; 
 int /*<<< orphan*/  irlap_wait_min_turn_around (struct irlap_cb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__* skb_put (struct sk_buff*,int) ; 

void irlap_send_test_frame(struct irlap_cb *self, __u8 caddr, __u32 daddr,
			   struct sk_buff *cmd)
{
	struct sk_buff *tx_skb;
	struct test_frame *frame;
	__u8 *info;

	tx_skb = alloc_skb(cmd->len + sizeof(struct test_frame), GFP_ATOMIC);
	if (!tx_skb)
		return;

	/* Broadcast frames must include saddr and daddr fields */
	if (caddr == CBROADCAST) {
		frame = (struct test_frame *)
			skb_put(tx_skb, sizeof(struct test_frame));

		/* Insert the swapped addresses */
		frame->saddr = cpu_to_le32(self->saddr);
		frame->daddr = cpu_to_le32(daddr);
	} else
		frame = (struct test_frame *) skb_put(tx_skb, LAP_ADDR_HEADER + LAP_CTRL_HEADER);

	frame->caddr = caddr;
	frame->control = TEST_RSP | PF_BIT;

	/* Copy info */
	info = skb_put(tx_skb, cmd->len);
	memcpy(info, cmd->data, cmd->len);

	/* Return to sender */
	irlap_wait_min_turn_around(self, &self->qos_tx);
	irlap_queue_xmit(self, tx_skb);
}