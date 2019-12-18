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
struct sk_buff {int* data; } ;
struct irlap_cb {int vs; int window; int /*<<< orphan*/  caddr; int /*<<< orphan*/  ack_required; int /*<<< orphan*/  wx_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int I_FRAME ; 
 int /*<<< orphan*/  RSP_FRAME ; 
 int /*<<< orphan*/  irlap_send_i_frame (struct irlap_cb*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irlap_send_ui_frame (struct irlap_cb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_get (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 

void irlap_send_data_secondary(struct irlap_cb *self, struct sk_buff *skb)
{
	struct sk_buff *tx_skb = NULL;

	/* Is this reliable or unreliable data? */
	if (skb->data[1] == I_FRAME) {

		/*
		 *  Insert frame sequence number (Vs) in control field before
		 *  inserting into transmit window queue.
		 */
		skb->data[1] = I_FRAME | (self->vs << 1);

		/*
		 *  Insert frame in store, in case of retransmissions
		 *  Increase skb reference count, see irlap_do_event()
		 */
		skb_get(skb);
		skb_queue_tail(&self->wx_list, skb);

		tx_skb = skb_clone(skb, GFP_ATOMIC);
		if (tx_skb == NULL) {
			return;
		}

		self->vs = (self->vs + 1) % 8;
		self->ack_required = FALSE;
		self->window -= 1;

		irlap_send_i_frame(self, tx_skb, RSP_FRAME);
	} else {
		irlap_send_ui_frame(self, skb_get(skb), self->caddr, RSP_FRAME);
		self->window -= 1;
	}
}