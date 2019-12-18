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
struct usb_device {int dummy; } ;
struct r8192_priv {struct usb_device* udev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  RTL8187_REQT_READ ; 
 int /*<<< orphan*/  RTL8187_REQ_GET_REGS ; 
 scalar_t__ ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  printk (char*,int) ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

u8 read_nic_byte_E(struct net_device *dev, int indx)
{
	int status;
	u8 data;
	struct r8192_priv *priv = (struct r8192_priv *)ieee80211_priv(dev);
	struct usb_device *udev = priv->udev;

	status = usb_control_msg(udev, usb_rcvctrlpipe(udev, 0),
			       RTL8187_REQ_GET_REGS, RTL8187_REQT_READ,
			       indx|0xfe00, 0, &data, 1, HZ / 2);

        if (status < 0)
        {
                printk("read_nic_byte_E TimeOut! status:%d\n", status);
        }

	return data;
}