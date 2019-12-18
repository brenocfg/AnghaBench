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
 int /*<<< orphan*/  MCS_WRREQ ; 
 int /*<<< orphan*/  MCS_WR_RTYPE ; 
 int /*<<< orphan*/  MOS_WDR_TIMEOUT ; 
 int /*<<< orphan*/  dbg (char*,int) ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mos7840_set_uart_reg(struct usb_serial_port *port, __u16 reg,
				__u16 val)
{

	struct usb_device *dev = port->serial->dev;
	val = val & 0x00ff;
	/* For the UART control registers, the application number need
	   to be Or'ed */
	if (port->serial->num_ports == 4) {
		val |= (((__u16) port->number -
				(__u16) (port->serial->minor)) + 1) << 8;
		dbg("mos7840_set_uart_reg application number is %x", val);
	} else {
		if (((__u16) port->number - (__u16) (port->serial->minor)) == 0) {
			val |= (((__u16) port->number -
			      (__u16) (port->serial->minor)) + 1) << 8;
			dbg("mos7840_set_uart_reg application number is %x",
			    val);
		} else {
			val |=
			    (((__u16) port->number -
			      (__u16) (port->serial->minor)) + 2) << 8;
			dbg("mos7840_set_uart_reg application number is %x",
			    val);
		}
	}
	return usb_control_msg(dev, usb_sndctrlpipe(dev, 0), MCS_WRREQ,
			       MCS_WR_RTYPE, val, reg, NULL, 0,
			       MOS_WDR_TIMEOUT);

}