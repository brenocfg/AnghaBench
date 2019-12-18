#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct usb_device_id {int /*<<< orphan*/  driver_info; } ;
struct usb_device {int /*<<< orphan*/  dev; } ;
struct ar9170 {struct usb_device* udev; int /*<<< orphan*/  rx_pool_urbs; int /*<<< orphan*/  rx_anch_urbs; int /*<<< orphan*/  rx_work_urbs; int /*<<< orphan*/  tx_anch_urbs; int /*<<< orphan*/  tx_cmd_urbs; int /*<<< orphan*/  usb_tasklet; int /*<<< orphan*/  fw_load_wait; int /*<<< orphan*/  fw_boot_wait; int /*<<< orphan*/  cmd_wait; int /*<<< orphan*/  tx_err; int /*<<< orphan*/  tx_cmd; int /*<<< orphan*/  tx_anch; int /*<<< orphan*/  tx_wait; int /*<<< orphan*/  rx_work; int /*<<< orphan*/  rx_pool; int /*<<< orphan*/  rx_anch; int /*<<< orphan*/  hw; int /*<<< orphan*/  features; struct usb_interface* intf; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARL9170FW_NAME ; 
 int /*<<< orphan*/  CARL9170_STOPPED ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct ar9170*) ; 
 int PTR_ERR (struct ar9170*) ; 
 int /*<<< orphan*/  SET_IEEE80211_DEV (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ar9170* carl9170_alloc (int) ; 
 int /*<<< orphan*/  carl9170_set_state (struct ar9170*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  carl9170_usb_firmware_step2 ; 
 int /*<<< orphan*/  carl9170_usb_tasklet ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_usb_anchor (int /*<<< orphan*/ *) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int request_firmware_nowait (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ar9170*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  usb_get_dev (struct usb_device*) ; 
 int usb_reset_device (struct usb_device*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct ar9170*) ; 

__attribute__((used)) static int carl9170_usb_probe(struct usb_interface *intf,
			      const struct usb_device_id *id)
{
	struct ar9170 *ar;
	struct usb_device *udev;
	int err;

	err = usb_reset_device(interface_to_usbdev(intf));
	if (err)
		return err;

	ar = carl9170_alloc(sizeof(*ar));
	if (IS_ERR(ar))
		return PTR_ERR(ar);

	udev = interface_to_usbdev(intf);
	usb_get_dev(udev);
	ar->udev = udev;
	ar->intf = intf;
	ar->features = id->driver_info;

	usb_set_intfdata(intf, ar);
	SET_IEEE80211_DEV(ar->hw, &intf->dev);

	init_usb_anchor(&ar->rx_anch);
	init_usb_anchor(&ar->rx_pool);
	init_usb_anchor(&ar->rx_work);
	init_usb_anchor(&ar->tx_wait);
	init_usb_anchor(&ar->tx_anch);
	init_usb_anchor(&ar->tx_cmd);
	init_usb_anchor(&ar->tx_err);
	init_completion(&ar->cmd_wait);
	init_completion(&ar->fw_boot_wait);
	init_completion(&ar->fw_load_wait);
	tasklet_init(&ar->usb_tasklet, carl9170_usb_tasklet,
		     (unsigned long)ar);

	atomic_set(&ar->tx_cmd_urbs, 0);
	atomic_set(&ar->tx_anch_urbs, 0);
	atomic_set(&ar->rx_work_urbs, 0);
	atomic_set(&ar->rx_anch_urbs, 0);
	atomic_set(&ar->rx_pool_urbs, 0);

	usb_get_dev(ar->udev);

	carl9170_set_state(ar, CARL9170_STOPPED);

	return request_firmware_nowait(THIS_MODULE, 1, CARL9170FW_NAME,
		&ar->udev->dev, GFP_KERNEL, ar, carl9170_usb_firmware_step2);
}