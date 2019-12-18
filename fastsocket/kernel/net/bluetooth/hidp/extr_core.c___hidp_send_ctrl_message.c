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
struct sk_buff {int dummy; } ;
struct hidp_session {int /*<<< orphan*/  ctrl_transmit; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct hidp_session*,unsigned char*,int) ; 
 int /*<<< orphan*/  BT_ERR (char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 unsigned char* skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 

__attribute__((used)) static int __hidp_send_ctrl_message(struct hidp_session *session,
			unsigned char hdr, unsigned char *data, int size)
{
	struct sk_buff *skb;

	BT_DBG("session %p data %p size %d", session, data, size);

	if (!(skb = alloc_skb(size + 1, GFP_ATOMIC))) {
		BT_ERR("Can't allocate memory for new frame");
		return -ENOMEM;
	}

	*skb_put(skb, 1) = hdr;
	if (data && size > 0)
		memcpy(skb_put(skb, size), data, size);

	skb_queue_tail(&session->ctrl_transmit, skb);

	return 0;
}