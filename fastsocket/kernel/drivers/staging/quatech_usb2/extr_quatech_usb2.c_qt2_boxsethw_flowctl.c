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
typedef  int __u8 ;
typedef  int __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  QT2_HW_FLOW_CONTROL_MASK ; 
 int QT2_SERIAL_MCR_RTS ; 
 int QT2_SERIAL_MSR_CTS ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qt2_boxsethw_flowctl(struct usb_serial *serial,
		unsigned int UartNumber, bool bSet)
{
	__u8 MCR_Value = 0;
	__u8 MSR_Value = 0;
	__u16 MOUT_Value = 0;

	if (bSet == true) {
		MCR_Value =  QT2_SERIAL_MCR_RTS;
		/* flow control, box will clear RTS line to prevent remote
		 * device from transmitting more chars */
	} else {
		/* no flow control to remote device */
		MCR_Value =  0;
	}
	MOUT_Value = MCR_Value << 8;

	if (bSet == true) {
		MSR_Value = QT2_SERIAL_MSR_CTS;
		/* flow control on, box will inhibit tx data if CTS line is
		 * asserted */
	} else {
		/* Box will not inhibit tx data due to CTS line */
		MSR_Value = 0;
	}
	MOUT_Value |= MSR_Value;
	return usb_control_msg(serial->dev, usb_sndctrlpipe(serial->dev, 0),
			QT2_HW_FLOW_CONTROL_MASK, 0x40, MOUT_Value, UartNumber,
			NULL, 0, 300);
}