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
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  unusable; int /*<<< orphan*/  reset; int /*<<< orphan*/  shutdown; } ;
struct TYPE_4__ {TYPE_1__ eh_ops; int /*<<< orphan*/ * tcp_socket; int /*<<< orphan*/  lock; int /*<<< orphan*/  status; int /*<<< orphan*/  side; int /*<<< orphan*/  tcp_tx; int /*<<< orphan*/  tcp_rx; } ;
struct stub_device {int devid; TYPE_2__ ud; int /*<<< orphan*/  tx_waitq; int /*<<< orphan*/  priv_lock; int /*<<< orphan*/  unlink_tx; int /*<<< orphan*/  unlink_free; int /*<<< orphan*/  priv_free; int /*<<< orphan*/  priv_tx; int /*<<< orphan*/  priv_init; struct usb_interface* interface; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SDEV_ST_AVAILABLE ; 
 int /*<<< orphan*/  USBIP_STUB ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int interface_to_busnum (struct usb_interface*) ; 
 int interface_to_devnum (struct usb_interface*) ; 
 struct stub_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub_device_reset ; 
 int /*<<< orphan*/  stub_device_unusable ; 
 int /*<<< orphan*/  stub_rx_loop ; 
 int /*<<< orphan*/  stub_shutdown_connection ; 
 int /*<<< orphan*/  stub_tx_loop ; 
 int /*<<< orphan*/  usbip_start_eh (TYPE_2__*) ; 
 int /*<<< orphan*/  usbip_task_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbip_udbg (char*) ; 

__attribute__((used)) static struct stub_device *stub_device_alloc(struct usb_interface *interface)
{
	struct stub_device *sdev;
	int busnum = interface_to_busnum(interface);
	int devnum = interface_to_devnum(interface);

	dev_dbg(&interface->dev, "allocating stub device");

	/* yes, it's a new device */
	sdev = kzalloc(sizeof(struct stub_device), GFP_KERNEL);
	if (!sdev) {
		dev_err(&interface->dev, "no memory for stub_device\n");
		return NULL;
	}

	sdev->interface = interface;

	/*
	 * devid is defined with devnum when this driver is first allocated.
	 * devnum may change later if a device is reset. However, devid never
	 * changes during a usbip connection.
	 */
	sdev->devid     = (busnum << 16) | devnum;

	usbip_task_init(&sdev->ud.tcp_rx, "stub_rx", stub_rx_loop);
	usbip_task_init(&sdev->ud.tcp_tx, "stub_tx", stub_tx_loop);

	sdev->ud.side = USBIP_STUB;
	sdev->ud.status = SDEV_ST_AVAILABLE;
	/* sdev->ud.lock = SPIN_LOCK_UNLOCKED; */
	spin_lock_init(&sdev->ud.lock);
	sdev->ud.tcp_socket = NULL;

	INIT_LIST_HEAD(&sdev->priv_init);
	INIT_LIST_HEAD(&sdev->priv_tx);
	INIT_LIST_HEAD(&sdev->priv_free);
	INIT_LIST_HEAD(&sdev->unlink_free);
	INIT_LIST_HEAD(&sdev->unlink_tx);
	/* sdev->priv_lock = SPIN_LOCK_UNLOCKED; */
	spin_lock_init(&sdev->priv_lock);

	init_waitqueue_head(&sdev->tx_waitq);

	sdev->ud.eh_ops.shutdown = stub_shutdown_connection;
	sdev->ud.eh_ops.reset    = stub_device_reset;
	sdev->ud.eh_ops.unusable = stub_device_unusable;

	usbip_start_eh(&sdev->ud);

	usbip_udbg("register new interface\n");
	return sdev;
}