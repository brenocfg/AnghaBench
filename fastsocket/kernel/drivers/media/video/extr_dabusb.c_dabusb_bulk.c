#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* pdabusb_t ;
typedef  TYPE_2__* pbulk_transfer_t ;
struct TYPE_12__ {int /*<<< orphan*/  dev; } ;
struct TYPE_11__ {int size; int /*<<< orphan*/  data; int /*<<< orphan*/  pipe; } ;
struct TYPE_10__ {TYPE_3__* usbdev; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPIPE ; 
 int /*<<< orphan*/  _DABUSB_IF ; 
 int /*<<< orphan*/  dbg (char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int usb_bulk_msg (TYPE_3__*,unsigned int,int /*<<< orphan*/ ,int,int*,int) ; 
 scalar_t__ usb_clear_halt (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_pipeendpoint (unsigned int) ; 
 unsigned int usb_rcvbulkpipe (TYPE_3__*,int) ; 
 scalar_t__ usb_set_interface (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 unsigned int usb_sndbulkpipe (TYPE_3__*,int) ; 

__attribute__((used)) static int dabusb_bulk (pdabusb_t s, pbulk_transfer_t pb)
{
	int ret;
	unsigned int pipe;
	int actual_length;

	dbg("dabusb_bulk");

	if (!pb->pipe)
		pipe = usb_rcvbulkpipe (s->usbdev, 2);
	else
		pipe = usb_sndbulkpipe (s->usbdev, 2);

	ret=usb_bulk_msg(s->usbdev, pipe, pb->data, pb->size, &actual_length, 100);
	if(ret<0) {
		dev_err(&s->usbdev->dev,
			"usb_bulk_msg failed(%d)\n", ret);

		if (usb_set_interface (s->usbdev, _DABUSB_IF, 1) < 0) {
			dev_err(&s->usbdev->dev, "set_interface failed\n");
			return -EINVAL;
		}

	}

	if( ret == -EPIPE ) {
		dev_warn(&s->usbdev->dev, "CLEAR_FEATURE request to remove STALL condition.\n");
		if(usb_clear_halt(s->usbdev, usb_pipeendpoint(pipe)))
			dev_err(&s->usbdev->dev, "request failed\n");
	}

	pb->size = actual_length;
	return ret;
}