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
struct zd_usb {int dummy; } ;
struct TYPE_2__ {struct zd_usb usb; } ;
struct zd_mac {TYPE_1__ chip; } ;
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_dbg_f (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ieee80211_free_hw (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  ieee80211_unregister_hw (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_reset_device (int /*<<< orphan*/ ) ; 
 struct zd_mac* zd_hw_mac (struct ieee80211_hw*) ; 
 struct ieee80211_hw* zd_intf_to_hw (struct usb_interface*) ; 
 int /*<<< orphan*/  zd_mac_clear (struct zd_mac*) ; 
 int /*<<< orphan*/  zd_usb_dev (struct zd_usb*) ; 
 int /*<<< orphan*/  zd_usb_disable_int (struct zd_usb*) ; 
 int /*<<< orphan*/  zd_usb_disable_rx (struct zd_usb*) ; 
 int /*<<< orphan*/  zd_usb_disable_tx (struct zd_usb*) ; 

__attribute__((used)) static void disconnect(struct usb_interface *intf)
{
	struct ieee80211_hw *hw = zd_intf_to_hw(intf);
	struct zd_mac *mac;
	struct zd_usb *usb;

	/* Either something really bad happened, or we're just dealing with
	 * a DEVICE_INSTALLER. */
	if (hw == NULL)
		return;

	mac = zd_hw_mac(hw);
	usb = &mac->chip.usb;

	dev_dbg_f(zd_usb_dev(usb), "\n");

	ieee80211_unregister_hw(hw);

	/* Just in case something has gone wrong! */
	zd_usb_disable_tx(usb);
	zd_usb_disable_rx(usb);
	zd_usb_disable_int(usb);

	/* If the disconnect has been caused by a removal of the
	 * driver module, the reset allows reloading of the driver. If the
	 * reset will not be executed here, the upload of the firmware in the
	 * probe function caused by the reloading of the driver will fail.
	 */
	usb_reset_device(interface_to_usbdev(intf));

	zd_mac_clear(mac);
	ieee80211_free_hw(hw);
	dev_dbg(&intf->dev, "disconnected\n");
}