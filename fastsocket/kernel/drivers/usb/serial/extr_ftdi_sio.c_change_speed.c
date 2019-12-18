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
struct usb_serial_port {TYPE_1__* serial; } ;
struct tty_struct {int dummy; } ;
struct ftdi_private {int interface; } ;
typedef  int __u32 ;
typedef  int __u16 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FTDI_SIO_SET_BAUDRATE_REQUEST ; 
 int /*<<< orphan*/  FTDI_SIO_SET_BAUDRATE_REQUEST_TYPE ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  WDR_SHORT_TIMEOUT ; 
 int get_ftdi_divisor (struct tty_struct*,struct usb_serial_port*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ftdi_private* usb_get_serial_port_data (struct usb_serial_port*) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int change_speed(struct tty_struct *tty, struct usb_serial_port *port)
{
	struct ftdi_private *priv = usb_get_serial_port_data(port);
	char *buf;
	__u16 urb_value;
	__u16 urb_index;
	__u32 urb_index_value;
	int rv;

	buf = kmalloc(1, GFP_NOIO);
	if (!buf)
		return -ENOMEM;

	urb_index_value = get_ftdi_divisor(tty, port);
	urb_value = (__u16)urb_index_value;
	urb_index = (__u16)(urb_index_value >> 16);
	if (priv->interface) {	/* FT2232C */
		urb_index = (__u16)((urb_index << 8) | priv->interface);
	}

	rv = usb_control_msg(port->serial->dev,
			    usb_sndctrlpipe(port->serial->dev, 0),
			    FTDI_SIO_SET_BAUDRATE_REQUEST,
			    FTDI_SIO_SET_BAUDRATE_REQUEST_TYPE,
			    urb_value, urb_index,
			    buf, 0, WDR_SHORT_TIMEOUT);

	kfree(buf);
	return rv;
}