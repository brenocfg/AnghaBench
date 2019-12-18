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
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  QT_SET_GET_DEVICE ; 
 int /*<<< orphan*/  QU2BOXPWRON ; 
 int /*<<< orphan*/  USBD_TRANSFER_DIRECTION_OUT ; 
 int usb_control_msg (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int) ; 
 unsigned int usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qt2_boxpoweron(struct usb_serial *serial)
{
	int result;
	__u8  Direcion;
	unsigned int pipe;
	Direcion = USBD_TRANSFER_DIRECTION_OUT;
	pipe = usb_rcvctrlpipe(serial->dev, 0);
	result = usb_control_msg(serial->dev, pipe, QT_SET_GET_DEVICE,
				Direcion, QU2BOXPWRON, 0x00, NULL, 0x00,
				5000);
	return result;
}