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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct cx231xx {int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cx231xx_info (char*,...) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int usb_bulk_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int*,int) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (int /*<<< orphan*/ ,int) ; 

int cx231xx_ep5_bulkout(struct cx231xx *dev, u8 *firmware, u16 size)
{
	int errCode = 0;
	int actlen, ret = -ENOMEM;
	u32 *buffer;

buffer = kzalloc(4096, GFP_KERNEL);
	if (buffer == NULL) {
		cx231xx_info("out of mem\n");
		return -ENOMEM;
	}
	memcpy(&buffer[0], firmware, 4096);

	ret = usb_bulk_msg(dev->udev, usb_sndbulkpipe(dev->udev, 5),
				 buffer, 4096, &actlen, 2000);

	if (ret)
		cx231xx_info("bulk message failed: %d (%d/%d)", ret,
				 size, actlen);
	else {
		errCode = actlen != size ? -1 : 0;
	}
kfree(buffer);
	return 0;
}