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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct uvd {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int,int) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int konicawc_ctrl_msg(struct uvd *uvd, u8 dir, u8 request, u16 value, u16 index, void *buf, int len)
{
	int retval = usb_control_msg(uvd->dev,
		dir ? usb_rcvctrlpipe(uvd->dev, 0) : usb_sndctrlpipe(uvd->dev, 0),
		    request, 0x40 | dir, value, index, buf, len, 1000);
	return retval < 0 ? retval : 0;
}