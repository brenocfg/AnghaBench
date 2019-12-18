#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct usb_ctrlrequest {int /*<<< orphan*/  wLength; int /*<<< orphan*/  wValue; int /*<<< orphan*/  wIndex; int /*<<< orphan*/  bRequest; int /*<<< orphan*/  bRequestType; } ;
struct urb {unsigned int pipe; int /*<<< orphan*/  setup_packet; int /*<<< orphan*/  transfer_buffer_length; int /*<<< orphan*/  transfer_buffer; int /*<<< orphan*/  transfer_flags; int /*<<< orphan*/  interval; int /*<<< orphan*/  complete; struct sk_buff* context; int /*<<< orphan*/  dev; } ;
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; scalar_t__ dev; } ;
struct TYPE_9__ {int /*<<< orphan*/  sco_tx; int /*<<< orphan*/  acl_tx; int /*<<< orphan*/  cmd_tx; } ;
struct TYPE_7__ {int acl_num; int sco_num; } ;
struct hci_dev {int /*<<< orphan*/  name; TYPE_4__ stat; TYPE_2__ conn_hash; int /*<<< orphan*/  flags; struct btusb_data* driver_data; } ;
struct btusb_data {int /*<<< orphan*/  udev; int /*<<< orphan*/  tx_anchor; int /*<<< orphan*/  waker; int /*<<< orphan*/  deferred; TYPE_3__* isoc_tx_ep; TYPE_1__* bulk_tx_ep; int /*<<< orphan*/  cmdreq_type; } ;
struct TYPE_10__ {int pkt_type; } ;
struct TYPE_8__ {int /*<<< orphan*/  wMaxPacketSize; int /*<<< orphan*/  bInterval; int /*<<< orphan*/  bEndpointAddress; } ;
struct TYPE_6__ {int /*<<< orphan*/  bEndpointAddress; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTUSB_MAX_ISOC_FRAMES ; 
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BT_ERR (char*,int /*<<< orphan*/ ,struct urb*) ; 
 int EBUSY ; 
 int EILSEQ ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
#define  HCI_ACLDATA_PKT 130 
#define  HCI_COMMAND_PKT 129 
 int /*<<< orphan*/  HCI_RUNNING ; 
#define  HCI_SCODATA_PKT 128 
 int /*<<< orphan*/  URB_ISO_ASAP ; 
 int /*<<< orphan*/  __cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __fill_isoc_descriptor (struct urb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__* bt_cb (struct sk_buff*) ; 
 int /*<<< orphan*/  btusb_isoc_tx_complete ; 
 int /*<<< orphan*/  btusb_tx_complete ; 
 int inc_tx (struct btusb_data*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct usb_ctrlrequest* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_anchor_urb (struct urb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (struct urb*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  usb_fill_control_urb (struct urb*,int /*<<< orphan*/ ,unsigned int,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_mark_last_busy (int /*<<< orphan*/ ) ; 
 unsigned int usb_sndbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int usb_sndctrlpipe (int /*<<< orphan*/ ,int) ; 
 unsigned int usb_sndisocpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_unanchor_urb (struct urb*) ; 

__attribute__((used)) static int btusb_send_frame(struct sk_buff *skb)
{
	struct hci_dev *hdev = (struct hci_dev *) skb->dev;
	struct btusb_data *data = hdev->driver_data;
	struct usb_ctrlrequest *dr;
	struct urb *urb;
	unsigned int pipe;
	int err;

	BT_DBG("%s", hdev->name);

	if (!test_bit(HCI_RUNNING, &hdev->flags))
		return -EBUSY;

	switch (bt_cb(skb)->pkt_type) {
	case HCI_COMMAND_PKT:
		urb = usb_alloc_urb(0, GFP_ATOMIC);
		if (!urb)
			return -ENOMEM;

		dr = kmalloc(sizeof(*dr), GFP_ATOMIC);
		if (!dr) {
			usb_free_urb(urb);
			return -ENOMEM;
		}

		dr->bRequestType = data->cmdreq_type;
		dr->bRequest     = 0;
		dr->wIndex       = 0;
		dr->wValue       = 0;
		dr->wLength      = __cpu_to_le16(skb->len);

		pipe = usb_sndctrlpipe(data->udev, 0x00);

		usb_fill_control_urb(urb, data->udev, pipe, (void *) dr,
				skb->data, skb->len, btusb_tx_complete, skb);

		hdev->stat.cmd_tx++;
		break;

	case HCI_ACLDATA_PKT:
		if (!data->bulk_tx_ep || hdev->conn_hash.acl_num < 1)
			return -ENODEV;

		urb = usb_alloc_urb(0, GFP_ATOMIC);
		if (!urb)
			return -ENOMEM;

		pipe = usb_sndbulkpipe(data->udev,
					data->bulk_tx_ep->bEndpointAddress);

		usb_fill_bulk_urb(urb, data->udev, pipe,
				skb->data, skb->len, btusb_tx_complete, skb);

		hdev->stat.acl_tx++;
		break;

	case HCI_SCODATA_PKT:
		if (!data->isoc_tx_ep || hdev->conn_hash.sco_num < 1)
			return -ENODEV;

		urb = usb_alloc_urb(BTUSB_MAX_ISOC_FRAMES, GFP_ATOMIC);
		if (!urb)
			return -ENOMEM;

		pipe = usb_sndisocpipe(data->udev,
					data->isoc_tx_ep->bEndpointAddress);

		urb->dev      = data->udev;
		urb->pipe     = pipe;
		urb->context  = skb;
		urb->complete = btusb_isoc_tx_complete;
		urb->interval = data->isoc_tx_ep->bInterval;

		urb->transfer_flags  = URB_ISO_ASAP;
		urb->transfer_buffer = skb->data;
		urb->transfer_buffer_length = skb->len;

		__fill_isoc_descriptor(urb, skb->len,
				le16_to_cpu(data->isoc_tx_ep->wMaxPacketSize));

		hdev->stat.sco_tx++;
		goto skip_waking;

	default:
		return -EILSEQ;
	}

	err = inc_tx(data);
	if (err) {
		usb_anchor_urb(urb, &data->deferred);
		schedule_work(&data->waker);
		err = 0;
		goto done;
	}

skip_waking:
	usb_anchor_urb(urb, &data->tx_anchor);

	err = usb_submit_urb(urb, GFP_ATOMIC);
	if (err < 0) {
		BT_ERR("%s urb %p submission failed", hdev->name, urb);
		kfree(urb->setup_packet);
		usb_unanchor_urb(urb);
	} else {
		usb_mark_last_busy(data->udev);
	}

	usb_free_urb(urb);

done:
	return err;
}