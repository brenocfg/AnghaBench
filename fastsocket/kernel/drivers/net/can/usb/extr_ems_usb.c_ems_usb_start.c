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
typedef  int /*<<< orphan*/  u8 ;
struct urb {int /*<<< orphan*/  transfer_dma; int /*<<< orphan*/  transfer_flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct net_device {TYPE_2__ dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  state; } ;
struct ems_usb {int free_slots; struct net_device* netdev; TYPE_1__ can; struct urb* intr_urb; scalar_t__* intr_in_buffer; int /*<<< orphan*/  udev; int /*<<< orphan*/  rx_submitted; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_STATE_ERROR_ACTIVE ; 
 int CONTR_BUS_ERROR ; 
 int CONTR_CAN_MESSAGE ; 
 int CONTR_CAN_STATE ; 
 int CONTR_CONT_ON ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INTR_IN_BUFFER_SIZE ; 
 int MAX_RX_URBS ; 
 int /*<<< orphan*/  RX_BUFFER_SIZE ; 
 int /*<<< orphan*/  SJA1000_MOD_NORMAL ; 
 int /*<<< orphan*/  URB_NO_TRANSFER_DMA_MAP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,...) ; 
 int ems_usb_control_cmd (struct ems_usb*,int) ; 
 int /*<<< orphan*/  ems_usb_read_bulk_callback ; 
 int /*<<< orphan*/  ems_usb_read_interrupt_callback ; 
 int ems_usb_write_mode (struct ems_usb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_device_detach (struct net_device*) ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_anchor_urb (struct urb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * usb_buffer_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_buffer_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (struct urb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ems_usb*) ; 
 int /*<<< orphan*/  usb_fill_int_urb (struct urb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ems_usb*,int) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_rcvintpipe (int /*<<< orphan*/ ,int) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_unanchor_urb (struct urb*) ; 

__attribute__((used)) static int ems_usb_start(struct ems_usb *dev)
{
	struct net_device *netdev = dev->netdev;
	int err, i;

	dev->intr_in_buffer[0] = 0;
	dev->free_slots = 15; /* initial size */

	for (i = 0; i < MAX_RX_URBS; i++) {
		struct urb *urb = NULL;
		u8 *buf = NULL;

		/* create a URB, and a buffer for it */
		urb = usb_alloc_urb(0, GFP_KERNEL);
		if (!urb) {
			dev_err(netdev->dev.parent,
				"No memory left for URBs\n");
			return -ENOMEM;
		}

		buf = usb_buffer_alloc(dev->udev, RX_BUFFER_SIZE, GFP_KERNEL,
				       &urb->transfer_dma);
		if (!buf) {
			dev_err(netdev->dev.parent,
				"No memory left for USB buffer\n");
			usb_free_urb(urb);
			return -ENOMEM;
		}

		usb_fill_bulk_urb(urb, dev->udev, usb_rcvbulkpipe(dev->udev, 2),
				  buf, RX_BUFFER_SIZE,
				  ems_usb_read_bulk_callback, dev);
		urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;
		usb_anchor_urb(urb, &dev->rx_submitted);

		err = usb_submit_urb(urb, GFP_KERNEL);
		if (err) {
			if (err == -ENODEV)
				netif_device_detach(dev->netdev);

			usb_unanchor_urb(urb);
			usb_buffer_free(dev->udev, RX_BUFFER_SIZE, buf,
					urb->transfer_dma);
			break;
		}

		/* Drop reference, USB core will take care of freeing it */
		usb_free_urb(urb);
	}

	/* Did we submit any URBs */
	if (i == 0) {
		dev_warn(netdev->dev.parent, "couldn't setup read URBs\n");
		return err;
	}

	/* Warn if we've couldn't transmit all the URBs */
	if (i < MAX_RX_URBS)
		dev_warn(netdev->dev.parent, "rx performance may be slow\n");

	/* Setup and start interrupt URB */
	usb_fill_int_urb(dev->intr_urb, dev->udev,
			 usb_rcvintpipe(dev->udev, 1),
			 dev->intr_in_buffer,
			 INTR_IN_BUFFER_SIZE,
			 ems_usb_read_interrupt_callback, dev, 1);

	err = usb_submit_urb(dev->intr_urb, GFP_KERNEL);
	if (err) {
		if (err == -ENODEV)
			netif_device_detach(dev->netdev);

		dev_warn(netdev->dev.parent, "intr URB submit failed: %d\n",
			 err);

		return err;
	}

	/* CPC-USB will transfer received message to host */
	err = ems_usb_control_cmd(dev, CONTR_CAN_MESSAGE | CONTR_CONT_ON);
	if (err)
		goto failed;

	/* CPC-USB will transfer CAN state changes to host */
	err = ems_usb_control_cmd(dev, CONTR_CAN_STATE | CONTR_CONT_ON);
	if (err)
		goto failed;

	/* CPC-USB will transfer bus errors to host */
	err = ems_usb_control_cmd(dev, CONTR_BUS_ERROR | CONTR_CONT_ON);
	if (err)
		goto failed;

	err = ems_usb_write_mode(dev, SJA1000_MOD_NORMAL);
	if (err)
		goto failed;

	dev->can.state = CAN_STATE_ERROR_ACTIVE;

	return 0;

failed:
	if (err == -ENODEV)
		netif_device_detach(dev->netdev);

	dev_warn(netdev->dev.parent, "couldn't submit control: %d\n", err);

	return err;
}