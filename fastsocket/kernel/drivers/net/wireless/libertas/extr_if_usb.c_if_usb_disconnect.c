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
struct usb_interface {int dummy; } ;
struct lbs_private {int surpriseremoved; TYPE_1__* dev; } ;
struct if_usb_card {int surprise_removed; scalar_t__ priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  LBS_DEB_MAIN ; 
 int /*<<< orphan*/  dev_attr_lbs_flash_boot2 ; 
 int /*<<< orphan*/  dev_attr_lbs_flash_fw ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  if_usb_free (struct if_usb_card*) ; 
 int /*<<< orphan*/  interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_remove_card (struct lbs_private*) ; 
 int /*<<< orphan*/  lbs_stop_card (struct lbs_private*) ; 
 struct if_usb_card* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_put_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void if_usb_disconnect(struct usb_interface *intf)
{
	struct if_usb_card *cardp = usb_get_intfdata(intf);
	struct lbs_private *priv = (struct lbs_private *) cardp->priv;

	lbs_deb_enter(LBS_DEB_MAIN);

	device_remove_file(&priv->dev->dev, &dev_attr_lbs_flash_boot2);
	device_remove_file(&priv->dev->dev, &dev_attr_lbs_flash_fw);

	cardp->surprise_removed = 1;

	if (priv) {
		priv->surpriseremoved = 1;
		lbs_stop_card(priv);
		lbs_remove_card(priv);
	}

	/* Unlink and free urb */
	if_usb_free(cardp);

	usb_set_intfdata(intf, NULL);
	usb_put_dev(interface_to_usbdev(intf));

	lbs_deb_leave(LBS_DEB_MAIN);
}