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
struct usb_device {int dummy; } ;
struct rt2x00_dev {int /*<<< orphan*/  flags; int /*<<< orphan*/  dev; } ;
struct queue_entry_priv_usb {int /*<<< orphan*/  urb; } ;
struct queue_entry {int /*<<< orphan*/  flags; TYPE_2__* skb; TYPE_1__* queue; struct queue_entry_priv_usb* priv_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct TYPE_3__ {int /*<<< orphan*/  usb_endpoint; struct rt2x00_dev* rt2x00dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_STATE_PRESENT ; 
 int ENODEV ; 
 int /*<<< orphan*/  ENTRY_DATA_IO_FAILED ; 
 int /*<<< orphan*/  ENTRY_DATA_STATUS_PENDING ; 
 int /*<<< orphan*/  ENTRY_OWNER_DEVICE_DATA ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2x00lib_dmadone (struct queue_entry*) ; 
 int /*<<< orphan*/  rt2x00lib_dmastart (struct queue_entry*) ; 
 int /*<<< orphan*/  rt2x00usb_interrupt_rxdone ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct usb_device* to_usb_device_intf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (int /*<<< orphan*/ ,struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct queue_entry*) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool rt2x00usb_kick_rx_entry(struct queue_entry *entry, void *data)
{
	struct rt2x00_dev *rt2x00dev = entry->queue->rt2x00dev;
	struct usb_device *usb_dev = to_usb_device_intf(rt2x00dev->dev);
	struct queue_entry_priv_usb *entry_priv = entry->priv_data;
	int status;

	if (test_and_set_bit(ENTRY_OWNER_DEVICE_DATA, &entry->flags) ||
	    test_bit(ENTRY_DATA_STATUS_PENDING, &entry->flags))
		return false;

	rt2x00lib_dmastart(entry);

	usb_fill_bulk_urb(entry_priv->urb, usb_dev,
			  usb_rcvbulkpipe(usb_dev, entry->queue->usb_endpoint),
			  entry->skb->data, entry->skb->len,
			  rt2x00usb_interrupt_rxdone, entry);

	status = usb_submit_urb(entry_priv->urb, GFP_ATOMIC);
	if (status) {
		if (status == -ENODEV)
			clear_bit(DEVICE_STATE_PRESENT, &rt2x00dev->flags);
		set_bit(ENTRY_DATA_IO_FAILED, &entry->flags);
		rt2x00lib_dmadone(entry);
	}

	return false;
}