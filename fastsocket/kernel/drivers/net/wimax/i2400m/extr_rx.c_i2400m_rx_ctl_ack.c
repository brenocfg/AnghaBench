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
struct wimax_dev {int dummy; } ;
struct sk_buff {int dummy; } ;
struct i2400m {int /*<<< orphan*/  rx_lock; int /*<<< orphan*/  msg_completion; struct sk_buff* ack_skb; struct wimax_dev wimax_dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINPROGRESS ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct sk_buff* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  d_printf (int,struct device*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct device* i2400m_dev (struct i2400m*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct sk_buff* wimax_msg_alloc (struct wimax_dev*,int /*<<< orphan*/ *,void const*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void i2400m_rx_ctl_ack(struct i2400m *i2400m,
		       const void *payload, size_t size)
{
	struct device *dev = i2400m_dev(i2400m);
	struct wimax_dev *wimax_dev = &i2400m->wimax_dev;
	unsigned long flags;
	struct sk_buff *ack_skb;

	/* Anyone waiting for an answer? */
	spin_lock_irqsave(&i2400m->rx_lock, flags);
	if (i2400m->ack_skb != ERR_PTR(-EINPROGRESS)) {
		dev_err(dev, "Huh? reply to command with no waiters\n");
		goto error_no_waiter;
	}
	spin_unlock_irqrestore(&i2400m->rx_lock, flags);

	ack_skb = wimax_msg_alloc(wimax_dev, NULL, payload, size, GFP_KERNEL);

	/* Check waiter didn't time out waiting for the answer... */
	spin_lock_irqsave(&i2400m->rx_lock, flags);
	if (i2400m->ack_skb != ERR_PTR(-EINPROGRESS)) {
		d_printf(1, dev, "Huh? waiter for command reply cancelled\n");
		goto error_waiter_cancelled;
	}
	if (ack_skb == NULL) {
		dev_err(dev, "CMD/GET/SET ack: cannot allocate SKB\n");
		i2400m->ack_skb = ERR_PTR(-ENOMEM);
	} else
		i2400m->ack_skb = ack_skb;
	spin_unlock_irqrestore(&i2400m->rx_lock, flags);
	complete(&i2400m->msg_completion);
	return;

error_waiter_cancelled:
	kfree_skb(ack_skb);
error_no_waiter:
	spin_unlock_irqrestore(&i2400m->rx_lock, flags);
	return;
}