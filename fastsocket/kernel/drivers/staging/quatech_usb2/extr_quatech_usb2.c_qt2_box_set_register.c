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
 int /*<<< orphan*/  QT2_GET_SET_REGISTER ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned short,unsigned short,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qt2_box_set_register(struct usb_serial *serial,
		unsigned short Uart_Number, unsigned short Register_Num,
		unsigned short Value)
{
	int result;
	unsigned short reg_and_byte;

	reg_and_byte = Value;
	reg_and_byte = reg_and_byte << 8;
	reg_and_byte = reg_and_byte + Register_Num;

	result = usb_control_msg(serial->dev, usb_sndctrlpipe(serial->dev, 0),
			QT2_GET_SET_REGISTER, 0x40, reg_and_byte,
			Uart_Number, NULL, 0, 300);
	return result;
}