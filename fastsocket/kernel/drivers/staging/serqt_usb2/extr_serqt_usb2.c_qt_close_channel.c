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
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  QT_OPEN_CLOSE_CHANNEL ; 
 int /*<<< orphan*/  USBD_TRANSFER_DIRECTION_OUT ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qt_close_channel(struct usb_serial *serial, __u16 Uart_Number)
{
	int result;

	result = usb_control_msg(serial->dev, usb_rcvctrlpipe(serial->dev, 0),
				 QT_OPEN_CLOSE_CHANNEL,
				 USBD_TRANSFER_DIRECTION_OUT, 0, Uart_Number,
				 NULL, 0, 300);

	return result;

}