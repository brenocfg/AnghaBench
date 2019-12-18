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
 int /*<<< orphan*/  PREFUFF_LEVEL_CONSERVATIVE ; 
 int /*<<< orphan*/  QT_SET_ATF ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int BoxSetATC(struct usb_serial *serial, __u16 n_Mode)
{
	int result;
	__u16 buffer_length;

	buffer_length = PREFUFF_LEVEL_CONSERVATIVE;

	result =
	    usb_control_msg(serial->dev, usb_sndctrlpipe(serial->dev, 0),
			    QT_SET_ATF, 0x40, n_Mode, 0, NULL, 0, 300);

	return result;
}