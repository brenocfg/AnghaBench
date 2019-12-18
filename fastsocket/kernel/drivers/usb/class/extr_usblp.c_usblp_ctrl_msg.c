#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct usblp {int ifnum; size_t current_protocol; int /*<<< orphan*/  dev; TYPE_1__* protocol; } ;
struct TYPE_2__ {int alt_setting; } ;

/* Variables and functions */
 int /*<<< orphan*/  USBLP_CTL_TIMEOUT ; 
 int USBLP_REQ_GET_ID ; 
 int USB_TYPE_CLASS ; 
 int /*<<< orphan*/  dbg (char*,int,int,int,int,int,int,int) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usblp_ctrl_msg(struct usblp *usblp, int request, int type, int dir, int recip, int value, void *buf, int len)
{
	int retval;
	int index = usblp->ifnum;

	/* High byte has the interface index.
	   Low byte has the alternate setting.
	 */
	if ((request == USBLP_REQ_GET_ID) && (type == USB_TYPE_CLASS)) {
	  index = (usblp->ifnum<<8)|usblp->protocol[usblp->current_protocol].alt_setting;
	}

	retval = usb_control_msg(usblp->dev,
		dir ? usb_rcvctrlpipe(usblp->dev, 0) : usb_sndctrlpipe(usblp->dev, 0),
		request, type | dir | recip, value, index, buf, len, USBLP_CTL_TIMEOUT);
	dbg("usblp_control_msg: rq: 0x%02x dir: %d recip: %d value: %d idx: %d len: %#x result: %d",
		request, !!dir, recip, value, index, len, retval);
	return retval < 0 ? retval : 0;
}