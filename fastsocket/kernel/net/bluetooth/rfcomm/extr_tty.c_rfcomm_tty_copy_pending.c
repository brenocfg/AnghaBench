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
struct tty_struct {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct rfcomm_dev {int /*<<< orphan*/  dlc; int /*<<< orphan*/  pending; struct tty_struct* tty; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct rfcomm_dev*,struct tty_struct*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  rfcomm_dlc_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rfcomm_dlc_unlock (int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (struct tty_struct*) ; 
 scalar_t__ tty_insert_flip_string (struct tty_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rfcomm_tty_copy_pending(struct rfcomm_dev *dev)
{
	struct tty_struct *tty = dev->tty;
	struct sk_buff *skb;
	int inserted = 0;

	if (!tty)
		return;

	BT_DBG("dev %p tty %p", dev, tty);

	rfcomm_dlc_lock(dev->dlc);

	while ((skb = skb_dequeue(&dev->pending))) {
		inserted += tty_insert_flip_string(tty, skb->data, skb->len);
		kfree_skb(skb);
	}

	rfcomm_dlc_unlock(dev->dlc);

	if (inserted > 0)
		tty_flip_buffer_push(tty);
}