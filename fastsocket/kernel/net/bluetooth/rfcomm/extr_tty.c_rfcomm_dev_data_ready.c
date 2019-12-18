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
struct rfcomm_dlc {struct rfcomm_dev* owner; } ;
struct rfcomm_dev {int /*<<< orphan*/  pending; struct tty_struct* tty; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct rfcomm_dlc*,struct tty_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_insert_flip_string (struct tty_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rfcomm_dev_data_ready(struct rfcomm_dlc *dlc, struct sk_buff *skb)
{
	struct rfcomm_dev *dev = dlc->owner;
	struct tty_struct *tty;

	if (!dev) {
		kfree_skb(skb);
		return;
	}

	if (!(tty = dev->tty) || !skb_queue_empty(&dev->pending)) {
		skb_queue_tail(&dev->pending, skb);
		return;
	}

	BT_DBG("dlc %p tty %p len %d", dlc, tty, skb->len);

	tty_insert_flip_string(tty, skb->data, skb->len);
	tty_flip_buffer_push(tty);

	kfree_skb(skb);
}