#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct urb {unsigned char* transfer_buffer; int actual_length; int /*<<< orphan*/  dev; scalar_t__ status; scalar_t__ context; } ;
struct sk_buff {int /*<<< orphan*/  len; scalar_t__ dev; } ;
struct bfusb_data {int /*<<< orphan*/  lock; TYPE_2__* hdev; int /*<<< orphan*/  udev; int /*<<< orphan*/  pending_q; } ;
struct TYPE_3__ {int byte_rx; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; TYPE_1__ stat; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct bfusb_data*,struct urb*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BT_ERR (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  HCI_RUNNING ; 
 int /*<<< orphan*/  bfusb_recv_block (struct bfusb_data*,int,unsigned char*,int) ; 
 int /*<<< orphan*/  bfusb_rx_submit (struct bfusb_data*,struct urb*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_unlink (struct sk_buff*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bfusb_rx_complete(struct urb *urb)
{
	struct sk_buff *skb = (struct sk_buff *) urb->context;
	struct bfusb_data *data = (struct bfusb_data *) skb->dev;
	unsigned char *buf = urb->transfer_buffer;
	int count = urb->actual_length;
	int err, hdr, len;

	BT_DBG("bfusb %p urb %p skb %p len %d", data, urb, skb, skb->len);

	read_lock(&data->lock);

	if (!test_bit(HCI_RUNNING, &data->hdev->flags))
		goto unlock;

	if (urb->status || !count)
		goto resubmit;

	data->hdev->stat.byte_rx += count;

	skb_put(skb, count);

	while (count) {
		hdr = buf[0] | (buf[1] << 8);

		if (hdr & 0x4000) {
			len = 0;
			count -= 2;
			buf   += 2;
		} else {
			len = (buf[2] == 0) ? 256 : buf[2];
			count -= 3;
			buf   += 3;
		}

		if (count < len) {
			BT_ERR("%s block extends over URB buffer ranges",
					data->hdev->name);
		}

		if ((hdr & 0xe1) == 0xc1)
			bfusb_recv_block(data, hdr, buf, len);

		count -= len;
		buf   += len;
	}

	skb_unlink(skb, &data->pending_q);
	kfree_skb(skb);

	bfusb_rx_submit(data, urb);

	read_unlock(&data->lock);

	return;

resubmit:
	urb->dev = data->udev;

	err = usb_submit_urb(urb, GFP_ATOMIC);
	if (err) {
		BT_ERR("%s bulk resubmit failed urb %p err %d",
					data->hdev->name, urb, err);
	}

unlock:
	read_unlock(&data->lock);
}