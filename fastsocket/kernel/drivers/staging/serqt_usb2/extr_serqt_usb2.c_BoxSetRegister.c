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
 int /*<<< orphan*/  QT_GET_SET_REGISTER ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned short,unsigned short,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int BoxSetRegister(struct usb_serial *serial, unsigned short Uart_Number,
			  unsigned short Register_Num, unsigned short Value)
{
	int result;
	unsigned short RegAndByte;

	RegAndByte = Value;
	RegAndByte = RegAndByte << 8;
	RegAndByte = RegAndByte + Register_Num;

/*
	result = usb_control_msg(serial->dev, usb_sndctrlpipe(serial->dev, 0),
				 QT_GET_SET_REGISTER, 0xC0, Register_Num,
				 Uart_Number, NULL, 0, 300);
*/

	result =
	    usb_control_msg(serial->dev, usb_sndctrlpipe(serial->dev, 0),
			    QT_GET_SET_REGISTER, 0x40, RegAndByte, Uart_Number,
			    NULL, 0, 300);

	return result;
}