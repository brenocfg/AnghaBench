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
struct urb {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  data; scalar_t__ cb; void* dev; } ;
struct bfusb_data_scb {struct urb* urb; } ;
struct bfusb_data {int /*<<< orphan*/  pending_q; TYPE_1__* hdev; int /*<<< orphan*/  udev; int /*<<< orphan*/  bulk_in_ep; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct bfusb_data*,struct urb*) ; 
 int /*<<< orphan*/  BT_ERR (char*,int /*<<< orphan*/ ,struct urb*,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int HCI_MAX_FRAME_SIZE ; 
 int /*<<< orphan*/  bfusb_rx_complete ; 
 struct sk_buff* bt_skb_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_unlink (struct sk_buff*,int /*<<< orphan*/ *) ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (struct urb*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int usb_rcvbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bfusb_rx_submit(struct bfusb_data *data, struct urb *urb)
{
	struct bfusb_data_scb *scb;
	struct sk_buff *skb;
	int err, pipe, size = HCI_MAX_FRAME_SIZE + 32;

	BT_DBG("bfusb %p urb %p", data, urb);

	if (!urb && !(urb = usb_alloc_urb(0, GFP_ATOMIC)))
		return -ENOMEM;

	skb = bt_skb_alloc(size, GFP_ATOMIC);
	if (!skb) {
		usb_free_urb(urb);
		return -ENOMEM;
	}

	skb->dev = (void *) data;

	scb = (struct bfusb_data_scb *) skb->cb;
	scb->urb = urb;

	pipe = usb_rcvbulkpipe(data->udev, data->bulk_in_ep);

	usb_fill_bulk_urb(urb, data->udev, pipe, skb->data, size,
			bfusb_rx_complete, skb);

	skb_queue_tail(&data->pending_q, skb);

	err = usb_submit_urb(urb, GFP_ATOMIC);
	if (err) {
		BT_ERR("%s bulk rx submit failed urb %p err %d",
					data->hdev->name, urb, err);
		skb_unlink(skb, &data->pending_q);
		kfree_skb(skb);
		usb_free_urb(urb);
	}

	return err;
}