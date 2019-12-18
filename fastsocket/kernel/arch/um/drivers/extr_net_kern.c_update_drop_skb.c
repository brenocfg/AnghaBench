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

/* Variables and functions */
 int ENOMEM ; 
 struct sk_buff* dev_alloc_skb (int) ; 
 int /*<<< orphan*/  drop_lock ; 
 int drop_max ; 
 struct sk_buff* drop_skb ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int update_drop_skb(int max)
{
	struct sk_buff *new;
	unsigned long flags;
	int err = 0;

	spin_lock_irqsave(&drop_lock, flags);

	if (max <= drop_max)
		goto out;

	err = -ENOMEM;
	new = dev_alloc_skb(max);
	if (new == NULL)
		goto out;

	skb_put(new, max);

	kfree_skb(drop_skb);
	drop_skb = new;
	drop_max = max;
	err = 0;
out:
	spin_unlock_irqrestore(&drop_lock, flags);

	return err;
}