#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct usb_device_id {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  parent; } ;
struct net_device {TYPE_4__ dev; int /*<<< orphan*/  flags; int /*<<< orphan*/ * netdev_ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  freq; } ;
struct TYPE_6__ {int /*<<< orphan*/  do_set_mode; int /*<<< orphan*/  do_set_bittiming; int /*<<< orphan*/ * bittiming_const; TYPE_1__ clock; int /*<<< orphan*/  state; } ;
struct ems_usb {int /*<<< orphan*/  intr_urb; void* intr_in_buffer; void* tx_msg_buffer; int /*<<< orphan*/  active_params; TYPE_3__* tx_contexts; int /*<<< orphan*/  active_tx_urbs; int /*<<< orphan*/  tx_submitted; int /*<<< orphan*/  rx_submitted; TYPE_2__ can; struct net_device* netdev; int /*<<< orphan*/  udev; } ;
struct ems_cpc_msg {int dummy; } ;
struct TYPE_7__ {int echo_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_STATE_STOPPED ; 
 scalar_t__ CPC_HEADER_SIZE ; 
 int /*<<< orphan*/  EMS_USB_ARM7_CLOCK ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IFF_ECHO ; 
 scalar_t__ INTR_IN_BUFFER_SIZE ; 
 int MAX_TX_URBS ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ *) ; 
 struct net_device* alloc_candev (int) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ems_usb_bittiming_const ; 
 int ems_usb_command_msg (struct ems_usb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ems_usb_netdev_ops ; 
 int /*<<< orphan*/  ems_usb_set_bittiming ; 
 int /*<<< orphan*/  ems_usb_set_mode ; 
 int /*<<< orphan*/  free_candev (struct net_device*) ; 
 int /*<<< orphan*/  init_params_sja1000 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_usb_anchor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kzalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 struct ems_usb* netdev_priv (struct net_device*) ; 
 int register_candev (struct net_device*) ; 
 int /*<<< orphan*/  usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct ems_usb*) ; 

__attribute__((used)) static int ems_usb_probe(struct usb_interface *intf,
			 const struct usb_device_id *id)
{
	struct net_device *netdev;
	struct ems_usb *dev;
	int i, err = -ENOMEM;

	netdev = alloc_candev(sizeof(struct ems_usb));
	if (!netdev) {
		dev_err(netdev->dev.parent, "Couldn't alloc candev\n");
		return -ENOMEM;
	}

	dev = netdev_priv(netdev);

	dev->udev = interface_to_usbdev(intf);
	dev->netdev = netdev;

	dev->can.state = CAN_STATE_STOPPED;
	dev->can.clock.freq = EMS_USB_ARM7_CLOCK;
	dev->can.bittiming_const = &ems_usb_bittiming_const;
	dev->can.do_set_bittiming = ems_usb_set_bittiming;
	dev->can.do_set_mode = ems_usb_set_mode;

	netdev->flags |= IFF_ECHO; /* we support local echo */

	netdev->netdev_ops = &ems_usb_netdev_ops;

	netdev->flags |= IFF_ECHO; /* we support local echo */

	init_usb_anchor(&dev->rx_submitted);

	init_usb_anchor(&dev->tx_submitted);
	atomic_set(&dev->active_tx_urbs, 0);

	for (i = 0; i < MAX_TX_URBS; i++)
		dev->tx_contexts[i].echo_index = MAX_TX_URBS;

	dev->intr_urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!dev->intr_urb) {
		dev_err(netdev->dev.parent, "Couldn't alloc intr URB\n");
		goto cleanup_candev;
	}

	dev->intr_in_buffer = kzalloc(INTR_IN_BUFFER_SIZE, GFP_KERNEL);
	if (!dev->intr_in_buffer) {
		dev_err(netdev->dev.parent, "Couldn't alloc Intr buffer\n");
		goto cleanup_intr_urb;
	}

	dev->tx_msg_buffer = kzalloc(CPC_HEADER_SIZE +
				     sizeof(struct ems_cpc_msg), GFP_KERNEL);
	if (!dev->tx_msg_buffer) {
		dev_err(netdev->dev.parent, "Couldn't alloc Tx buffer\n");
		goto cleanup_intr_in_buffer;
	}

	usb_set_intfdata(intf, dev);

	SET_NETDEV_DEV(netdev, &intf->dev);

	init_params_sja1000(&dev->active_params);

	err = ems_usb_command_msg(dev, &dev->active_params);
	if (err) {
		dev_err(netdev->dev.parent,
			"couldn't initialize controller: %d\n", err);
		goto cleanup_tx_msg_buffer;
	}

	err = register_candev(netdev);
	if (err) {
		dev_err(netdev->dev.parent,
			"couldn't register CAN device: %d\n", err);
		goto cleanup_tx_msg_buffer;
	}

	return 0;

cleanup_tx_msg_buffer:
	kfree(dev->tx_msg_buffer);

cleanup_intr_in_buffer:
	kfree(dev->intr_in_buffer);

cleanup_intr_urb:
	usb_free_urb(dev->intr_urb);

cleanup_candev:
	free_candev(netdev);

	return err;
}