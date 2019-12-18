#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* pdabusb_t ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {TYPE_2__* usbdev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,int) ; 
 int usb_control_msg (TYPE_2__*,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,unsigned char*,int,int) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dabusb_writemem (pdabusb_t s, int pos, const unsigned char *data,
			    int len)
{
	int ret;
	unsigned char *transfer_buffer =  kmalloc (len, GFP_KERNEL);

	if (!transfer_buffer) {
		dev_err(&s->usbdev->dev,
			"dabusb_writemem: kmalloc(%d) failed.\n", len);
		return -ENOMEM;
	}

	memcpy (transfer_buffer, data, len);

	ret=usb_control_msg(s->usbdev, usb_sndctrlpipe( s->usbdev, 0 ), 0xa0, 0x40, pos, 0, transfer_buffer, len, 300);

	kfree (transfer_buffer);
	return ret;
}