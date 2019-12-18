#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct p54u_priv {TYPE_1__* udev; TYPE_4__* intf; } ;
struct ieee80211_hw {struct p54u_priv* priv; } ;
struct TYPE_6__ {scalar_t__ condition; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ USB_INTERFACE_BINDING ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int usb_lock_device_for_reset (TYPE_1__*,TYPE_4__*) ; 
 int usb_reset_device (TYPE_1__*) ; 
 int /*<<< orphan*/  usb_unlock_device (TYPE_1__*) ; 

__attribute__((used)) static int p54u_device_reset(struct ieee80211_hw *dev)
{
	struct p54u_priv *priv = dev->priv;
	int ret, lock = (priv->intf->condition != USB_INTERFACE_BINDING);

	if (lock) {
		ret = usb_lock_device_for_reset(priv->udev, priv->intf);
		if (ret < 0) {
			dev_err(&priv->udev->dev, "(p54usb) unable to lock "
				"device for reset (%d)!\n", ret);
			return ret;
		}
	}

	ret = usb_reset_device(priv->udev);
	if (lock)
		usb_unlock_device(priv->udev);

	if (ret)
		dev_err(&priv->udev->dev, "(p54usb) unable to reset "
			"device (%d)!\n", ret);

	return ret;
}