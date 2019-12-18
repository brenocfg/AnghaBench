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
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct at76_priv {TYPE_1__* hw; } ;
struct TYPE_2__ {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  at76_delete_device (struct at76_priv*) ; 
 int /*<<< orphan*/  dev_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 struct at76_priv* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wiphy_info (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void at76_disconnect(struct usb_interface *interface)
{
	struct at76_priv *priv;

	priv = usb_get_intfdata(interface);
	usb_set_intfdata(interface, NULL);

	/* Disconnect after loading internal firmware */
	if (!priv)
		return;

	wiphy_info(priv->hw->wiphy, "disconnecting\n");
	at76_delete_device(priv);
	dev_printk(KERN_INFO, &interface->dev, "disconnected\n");
}