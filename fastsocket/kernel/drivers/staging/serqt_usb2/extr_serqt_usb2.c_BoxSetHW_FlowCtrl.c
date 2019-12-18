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

/* Variables and functions */
 int /*<<< orphan*/  QT_HW_FLOW_CONTROL_MASK ; 
 int SERIAL_MCR_RTS ; 
 int SERIAL_MSR_CTS ; 
 unsigned int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int BoxSetHW_FlowCtrl(struct usb_serial *serial, unsigned int index,
			     int bSet)
{
	__u8 mcr = 0;
	__u8 msr = 0, MOUT_Value = 0;
	unsigned int status;

	if (bSet == 1) {
		/* flow control, box will clear RTS line to prevent remote */
		mcr = SERIAL_MCR_RTS;
	} /* device from xmitting more chars */
	else {
		/* no flow control to remote device */
		mcr = 0;

	}
	MOUT_Value = mcr << 8;

	if (bSet == 1) {
		/* flow control, box will inhibit xmit data if CTS line is
		 * asserted */
		msr = SERIAL_MSR_CTS;
	} else {
		/* Box will not inhimbe xmit data due to CTS line */
		msr = 0;
	}
	MOUT_Value |= msr;

	status =
	    usb_control_msg(serial->dev, usb_sndctrlpipe(serial->dev, 0),
			    QT_HW_FLOW_CONTROL_MASK, 0x40, MOUT_Value,
			    index, NULL, 0, 300);
	return status;

}