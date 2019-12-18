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
struct urb {int /*<<< orphan*/  actual_length; int /*<<< orphan*/  transfer_buffer; int /*<<< orphan*/  status; struct hci_dev* context; } ;
struct TYPE_2__ {int /*<<< orphan*/  err_rx; int /*<<< orphan*/  byte_rx; } ;
struct hci_dev {int /*<<< orphan*/  name; TYPE_1__ stat; int /*<<< orphan*/  flags; struct btusb_data* driver_data; } ;
struct btusb_data {int /*<<< orphan*/  intr_anchor; int /*<<< orphan*/  udev; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTUSB_INTR_RUNNING ; 
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,struct urb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BT_ERR (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  HCI_EVENT_PKT ; 
 int /*<<< orphan*/  HCI_RUNNING ; 
 scalar_t__ hci_recv_fragment (struct hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_anchor_urb (struct urb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_mark_last_busy (int /*<<< orphan*/ ) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_unanchor_urb (struct urb*) ; 

__attribute__((used)) static void btusb_intr_complete(struct urb *urb)
{
	struct hci_dev *hdev = urb->context;
	struct btusb_data *data = hdev->driver_data;
	int err;

	BT_DBG("%s urb %p status %d count %d", hdev->name,
					urb, urb->status, urb->actual_length);

	if (!test_bit(HCI_RUNNING, &hdev->flags))
		return;

	if (urb->status == 0) {
		hdev->stat.byte_rx += urb->actual_length;

		if (hci_recv_fragment(hdev, HCI_EVENT_PKT,
						urb->transfer_buffer,
						urb->actual_length) < 0) {
			BT_ERR("%s corrupted event packet", hdev->name);
			hdev->stat.err_rx++;
		}
	}

	if (!test_bit(BTUSB_INTR_RUNNING, &data->flags))
		return;

	usb_mark_last_busy(data->udev);
	usb_anchor_urb(urb, &data->intr_anchor);

	err = usb_submit_urb(urb, GFP_ATOMIC);
	if (err < 0) {
		BT_ERR("%s urb %p failed to resubmit (%d)",
						hdev->name, urb, -err);
		usb_unanchor_urb(urb);
	}
}