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
struct urb {int number_of_packets; scalar_t__ transfer_buffer; TYPE_1__* iso_frame_desc; int /*<<< orphan*/  status; int /*<<< orphan*/  actual_length; struct hci_dev* context; } ;
struct TYPE_4__ {unsigned int byte_rx; int /*<<< orphan*/  err_rx; } ;
struct hci_dev {int /*<<< orphan*/  name; TYPE_2__ stat; int /*<<< orphan*/  flags; struct btusb_data* driver_data; } ;
struct btusb_data {int /*<<< orphan*/  isoc_anchor; int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {unsigned int offset; unsigned int actual_length; scalar_t__ status; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTUSB_ISOC_RUNNING ; 
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,struct urb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BT_ERR (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  HCI_RUNNING ; 
 int /*<<< orphan*/  HCI_SCODATA_PKT ; 
 scalar_t__ hci_recv_fragment (struct hci_dev*,int /*<<< orphan*/ ,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_anchor_urb (struct urb*,int /*<<< orphan*/ *) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_unanchor_urb (struct urb*) ; 

__attribute__((used)) static void btusb_isoc_complete(struct urb *urb)
{
	struct hci_dev *hdev = urb->context;
	struct btusb_data *data = hdev->driver_data;
	int i, err;

	BT_DBG("%s urb %p status %d count %d", hdev->name,
					urb, urb->status, urb->actual_length);

	if (!test_bit(HCI_RUNNING, &hdev->flags))
		return;

	if (urb->status == 0) {
		for (i = 0; i < urb->number_of_packets; i++) {
			unsigned int offset = urb->iso_frame_desc[i].offset;
			unsigned int length = urb->iso_frame_desc[i].actual_length;

			if (urb->iso_frame_desc[i].status)
				continue;

			hdev->stat.byte_rx += length;

			if (hci_recv_fragment(hdev, HCI_SCODATA_PKT,
						urb->transfer_buffer + offset,
								length) < 0) {
				BT_ERR("%s corrupted SCO packet", hdev->name);
				hdev->stat.err_rx++;
			}
		}
	}

	if (!test_bit(BTUSB_ISOC_RUNNING, &data->flags))
		return;

	usb_anchor_urb(urb, &data->isoc_anchor);

	err = usb_submit_urb(urb, GFP_ATOMIC);
	if (err < 0) {
		BT_ERR("%s urb %p failed to resubmit (%d)",
						hdev->name, urb, -err);
		usb_unanchor_urb(urb);
	}
}