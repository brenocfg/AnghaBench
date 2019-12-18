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
struct usb_serial_port {TYPE_1__* serial; scalar_t__ number; } ;
struct usb_device {int dummy; } ;
typedef  int __u16 ;
struct TYPE_2__ {int num_ports; scalar_t__ minor; struct usb_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCS_RDREQ ; 
 int /*<<< orphan*/  MCS_RD_RTYPE ; 
 int /*<<< orphan*/  MOS_WDR_TIMEOUT ; 
 int /*<<< orphan*/  VENDOR_READ_LENGTH ; 
 int /*<<< orphan*/  dbg (char*,int) ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mos7840_get_uart_reg(struct usb_serial_port *port, __u16 reg,
				__u16 *val)
{
	struct usb_device *dev = port->serial->dev;
	int ret = 0;
	__u16 Wval;

	/* dbg("application number is %4x",
	    (((__u16)port->number - (__u16)(port->serial->minor))+1)<<8); */
	/* Wval  is same as application number */
	if (port->serial->num_ports == 4) {
		Wval =
		    (((__u16) port->number - (__u16) (port->serial->minor)) +
		     1) << 8;
		dbg("mos7840_get_uart_reg application number is %x", Wval);
	} else {
		if (((__u16) port->number - (__u16) (port->serial->minor)) == 0) {
			Wval = (((__u16) port->number -
			      (__u16) (port->serial->minor)) + 1) << 8;
			dbg("mos7840_get_uart_reg application number is %x",
			    Wval);
		} else {
			Wval = (((__u16) port->number -
			      (__u16) (port->serial->minor)) + 2) << 8;
			dbg("mos7840_get_uart_reg application number is %x",
			    Wval);
		}
	}
	ret = usb_control_msg(dev, usb_rcvctrlpipe(dev, 0), MCS_RDREQ,
			      MCS_RD_RTYPE, Wval, reg, val, VENDOR_READ_LENGTH,
			      MOS_WDR_TIMEOUT);
	*val = (*val) & 0x00ff;
	return ret;
}