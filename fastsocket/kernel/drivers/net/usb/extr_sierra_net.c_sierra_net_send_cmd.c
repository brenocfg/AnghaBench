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
typedef  int /*<<< orphan*/  u8 ;
struct usbnet {int /*<<< orphan*/  net; } ;
struct sierra_net_data {int /*<<< orphan*/  ifnum; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  USB_CDC_SEND_ENCAPSULATED_COMMAND ; 
 int USB_DIR_OUT ; 
 int USB_RECIP_INTERFACE ; 
 int USB_TYPE_CLASS ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,char const*,int) ; 
 struct sierra_net_data* sierra_net_get_private (struct usbnet*) ; 
 int usbnet_write_cmd (struct usbnet*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int sierra_net_send_cmd(struct usbnet *dev,
		u8 *cmd, int cmdlen, const char * cmd_name)
{
	struct sierra_net_data *priv = sierra_net_get_private(dev);
	int  status;

	status = usbnet_write_cmd(dev, USB_CDC_SEND_ENCAPSULATED_COMMAND,
				  USB_DIR_OUT|USB_TYPE_CLASS|USB_RECIP_INTERFACE,
				  0, priv->ifnum, cmd, cmdlen);

	if (status != cmdlen && status != -ENODEV)
		netdev_err(dev->net, "Submit %s failed %d\n", cmd_name, status);

	return status;
}