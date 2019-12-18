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
struct urb {int dummy; } ;
struct sk_buff {scalar_t__ cb; } ;
struct bfusb_data_scb {struct urb* urb; } ;
struct bfusb_data {int /*<<< orphan*/  completed_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct bfusb_data*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct urb *bfusb_get_completed(struct bfusb_data *data)
{
	struct sk_buff *skb;
	struct urb *urb = NULL;

	BT_DBG("bfusb %p", data);

	skb = skb_dequeue(&data->completed_q);
	if (skb) {
		urb = ((struct bfusb_data_scb *) skb->cb)->urb;
		kfree_skb(skb);
	}

	return urb;
}