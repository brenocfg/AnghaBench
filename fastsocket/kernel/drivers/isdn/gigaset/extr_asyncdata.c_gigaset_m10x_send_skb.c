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
struct sk_buff {unsigned int len; } ;
struct bc_state {scalar_t__ proto2; TYPE_1__* cs; int /*<<< orphan*/  squeue; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  write_tasklet; scalar_t__ connected; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct sk_buff* HDLC_Encode (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HW_HDR_LEN ; 
 scalar_t__ ISDN_PROTO_L2_HDLC ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct sk_buff* iraw_encode (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

int gigaset_m10x_send_skb(struct bc_state *bcs, struct sk_buff *skb)
{
	unsigned len = skb->len;
	unsigned long flags;

	if (bcs->proto2 == ISDN_PROTO_L2_HDLC)
		skb = HDLC_Encode(skb, HW_HDR_LEN, 0);
	else
		skb = iraw_encode(skb, HW_HDR_LEN, 0);
	if (!skb) {
		dev_err(bcs->cs->dev,
			"unable to allocate memory for encoding!\n");
		return -ENOMEM;
	}

	skb_queue_tail(&bcs->squeue, skb);
	spin_lock_irqsave(&bcs->cs->lock, flags);
	if (bcs->cs->connected)
		tasklet_schedule(&bcs->cs->write_tasklet);
	spin_unlock_irqrestore(&bcs->cs->lock, flags);

	return len;	/* ok so far */
}