#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usb_sevsegdev {int /*<<< orphan*/  intf; scalar_t__ powered; scalar_t__ shadow_power; TYPE_1__* udev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int usb_autopm_get_interface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_autopm_put_interface (int /*<<< orphan*/ ) ; 
 int usb_control_msg (TYPE_1__*,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void update_display_powered(struct usb_sevsegdev *mydev)
{
	int rc;

	if (!mydev->shadow_power && mydev->powered) {
		rc = usb_autopm_get_interface(mydev->intf);
		if (rc < 0)
			return;
	}

	rc = usb_control_msg(mydev->udev,
			usb_sndctrlpipe(mydev->udev, 0),
			0x12,
			0x48,
			(80 * 0x100) + 10, /*  (power mode) */
			(0x00 * 0x100) + (mydev->powered ? 1 : 0),
			NULL,
			0,
			2000);
	if (rc < 0)
		dev_dbg(&mydev->udev->dev, "power retval = %d\n", rc);

	if (mydev->shadow_power && !mydev->powered)
		usb_autopm_put_interface(mydev->intf);
}