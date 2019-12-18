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
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct hidp_session {int /*<<< orphan*/  intr_transmit; int /*<<< orphan*/  intr_sock; int /*<<< orphan*/  ctrl_transmit; int /*<<< orphan*/  ctrl_sock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct hidp_session*) ; 
 scalar_t__ hidp_send_frame (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hidp_set_timer (struct hidp_session*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head (int /*<<< orphan*/ *,struct sk_buff*) ; 

__attribute__((used)) static void hidp_process_transmit(struct hidp_session *session)
{
	struct sk_buff *skb;

	BT_DBG("session %p", session);

	while ((skb = skb_dequeue(&session->ctrl_transmit))) {
		if (hidp_send_frame(session->ctrl_sock, skb->data, skb->len) < 0) {
			skb_queue_head(&session->ctrl_transmit, skb);
			break;
		}

		hidp_set_timer(session);
		kfree_skb(skb);
	}

	while ((skb = skb_dequeue(&session->intr_transmit))) {
		if (hidp_send_frame(session->intr_sock, skb->data, skb->len) < 0) {
			skb_queue_head(&session->intr_transmit, skb);
			break;
		}

		hidp_set_timer(session);
		kfree_skb(skb);
	}
}