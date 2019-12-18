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
struct sk_buff {unsigned int len; int /*<<< orphan*/  data; scalar_t__ cb; } ;
struct cmtp_session {unsigned int mtu; int /*<<< orphan*/  transmit; } ;
struct cmtp_scb {scalar_t__ id; scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct cmtp_session*) ; 
 int /*<<< orphan*/  BT_ERR (char*) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct sk_buff* alloc_skb (unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ cmtp_alloc_block_id (struct cmtp_session*) ; 
 int /*<<< orphan*/  cmtp_free_block_id (struct cmtp_session*,int) ; 
 int /*<<< orphan*/  cmtp_send_frame (struct cmtp_session*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 unsigned int min_t (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  skb_copy_from_linear_data (struct sk_buff*,unsigned char*,unsigned int) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,unsigned int) ; 
 unsigned char* skb_put (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  skb_queue_head (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uint ; 

__attribute__((used)) static void cmtp_process_transmit(struct cmtp_session *session)
{
	struct sk_buff *skb, *nskb;
	unsigned char *hdr;
	unsigned int size, tail;

	BT_DBG("session %p", session);

	if (!(nskb = alloc_skb(session->mtu, GFP_ATOMIC))) {
		BT_ERR("Can't allocate memory for new frame");
		return;
	}

	while ((skb = skb_dequeue(&session->transmit))) {
		struct cmtp_scb *scb = (void *) skb->cb;

		if ((tail = (session->mtu - nskb->len)) < 5) {
			cmtp_send_frame(session, nskb->data, nskb->len);
			skb_trim(nskb, 0);
			tail = session->mtu;
		}

		size = min_t(uint, ((tail < 258) ? (tail - 2) : (tail - 3)), skb->len);

		if ((scb->id < 0) && ((scb->id = cmtp_alloc_block_id(session)) < 0)) {
			skb_queue_head(&session->transmit, skb);
			break;
		}

		if (size < 256) {
			hdr = skb_put(nskb, 2);
			hdr[0] = 0x40
				| ((scb->id << 2) & 0x3c)
				| ((skb->len == size) ? 0x00 : 0x01);
			hdr[1] = size;
		} else {
			hdr = skb_put(nskb, 3);
			hdr[0] = 0x80
				| ((scb->id << 2) & 0x3c)
				| ((skb->len == size) ? 0x00 : 0x01);
			hdr[1] = size & 0xff;
			hdr[2] = size >> 8;
		}

		skb_copy_from_linear_data(skb, skb_put(nskb, size), size);
		skb_pull(skb, size);

		if (skb->len > 0) {
			skb_queue_head(&session->transmit, skb);
		} else {
			cmtp_free_block_id(session, scb->id);
			if (scb->data) {
				cmtp_send_frame(session, nskb->data, nskb->len);
				skb_trim(nskb, 0);
			}
			kfree_skb(skb);
		}
	}

	cmtp_send_frame(session, nskb->data, nskb->len);

	kfree_skb(nskb);
}