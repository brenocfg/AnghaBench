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
struct usb_serial {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  QT2_FLUSH_DEVICE ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned short,unsigned char,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qt2_box_flush(struct usb_serial *serial,  unsigned char uart_number,
		    unsigned short rcv_or_xmit)
{
	int result;
	result = usb_control_msg(serial->dev, usb_rcvctrlpipe(serial->dev, 0),
		QT2_FLUSH_DEVICE, 0x40, rcv_or_xmit, uart_number, NULL, 0,
		300);
	return result;
}