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
struct qt2_status_data {int dummy; } ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  int __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  QT_OPEN_CLOSE_CHANNEL ; 
 int /*<<< orphan*/  USBD_TRANSFER_DIRECTION_IN ; 
 int usb_control_msg (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct qt2_status_data*,int,int) ; 
 unsigned int usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qt2_openboxchannel(struct usb_serial *serial, __u16
		Uart_Number, struct qt2_status_data *status)
{
	int result;
	__u16 length;
	__u8  Direcion;
	unsigned int pipe;
	length = sizeof(struct qt2_status_data);
	Direcion = USBD_TRANSFER_DIRECTION_IN;
	pipe = usb_rcvctrlpipe(serial->dev, 0);
	result = usb_control_msg(serial->dev, pipe, QT_OPEN_CLOSE_CHANNEL,
			Direcion, 0x00, Uart_Number, status, length, 5000);
	return result;
}