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
struct TYPE_3__ {int /*<<< orphan*/  unusable; int /*<<< orphan*/  reset; int /*<<< orphan*/  shutdown; } ;
struct TYPE_4__ {TYPE_1__ eh_ops; int /*<<< orphan*/  lock; int /*<<< orphan*/  status; int /*<<< orphan*/  side; int /*<<< orphan*/  tcp_tx; int /*<<< orphan*/  tcp_rx; } ;
struct vhci_device {TYPE_2__ ud; int /*<<< orphan*/  waitq_tx; int /*<<< orphan*/  priv_lock; int /*<<< orphan*/  unlink_rx; int /*<<< orphan*/  unlink_tx; int /*<<< orphan*/  priv_tx; int /*<<< orphan*/  priv_rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  USBIP_VHCI ; 
 int /*<<< orphan*/  VDEV_ST_NULL ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct vhci_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbip_start_eh (TYPE_2__*) ; 
 int /*<<< orphan*/  usbip_task_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vhci_device_reset ; 
 int /*<<< orphan*/  vhci_device_unusable ; 
 int /*<<< orphan*/  vhci_rx_loop ; 
 int /*<<< orphan*/  vhci_shutdown_connection ; 
 int /*<<< orphan*/  vhci_tx_loop ; 

__attribute__((used)) static void vhci_device_init(struct vhci_device *vdev)
{
	memset(vdev, 0, sizeof(*vdev));

	usbip_task_init(&vdev->ud.tcp_rx, "vhci_rx", vhci_rx_loop);
	usbip_task_init(&vdev->ud.tcp_tx, "vhci_tx", vhci_tx_loop);

	vdev->ud.side   = USBIP_VHCI;
	vdev->ud.status = VDEV_ST_NULL;
	/* vdev->ud.lock   = SPIN_LOCK_UNLOCKED; */
	spin_lock_init(&vdev->ud.lock);

	INIT_LIST_HEAD(&vdev->priv_rx);
	INIT_LIST_HEAD(&vdev->priv_tx);
	INIT_LIST_HEAD(&vdev->unlink_tx);
	INIT_LIST_HEAD(&vdev->unlink_rx);
	/* vdev->priv_lock = SPIN_LOCK_UNLOCKED; */
	spin_lock_init(&vdev->priv_lock);

	init_waitqueue_head(&vdev->waitq_tx);

	vdev->ud.eh_ops.shutdown = vhci_shutdown_connection;
	vdev->ud.eh_ops.reset = vhci_device_reset;
	vdev->ud.eh_ops.unusable = vhci_device_unusable;

	usbip_start_eh(&vdev->ud);
}