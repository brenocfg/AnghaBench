#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct usb_device {scalar_t__ speed; int /*<<< orphan*/  dev; TYPE_1__* parent; TYPE_3__* bos; } ;
struct TYPE_6__ {int /*<<< orphan*/  ss_cap; TYPE_2__* ext_cap; } ;
struct TYPE_5__ {int /*<<< orphan*/  bmAttributes; } ;
struct TYPE_4__ {scalar_t__ lpm_capable; } ;

/* Variables and functions */
 int USB_LPM_SUPPORT ; 
 scalar_t__ USB_SPEED_HIGH ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usb_device_supports_lpm(struct usb_device *udev)
{
	/* USB 2.1 (and greater) devices indicate LPM support through
	 * their USB 2.0 Extended Capabilities BOS descriptor.
	 */
	if (udev->speed == USB_SPEED_HIGH) {
		if (udev->bos->ext_cap &&
			(USB_LPM_SUPPORT &
			 le32_to_cpu(udev->bos->ext_cap->bmAttributes)))
			return 1;
		return 0;
	}

	/* All USB 3.0 must support LPM, but we need their max exit latency
	 * information from the SuperSpeed Extended Capabilities BOS descriptor.
	 */
	if (!udev->bos->ss_cap) {
		dev_warn(&udev->dev, "No LPM exit latency info found.  "
				"Power management will be impacted.\n");
		return 0;
	}
	if (udev->parent->lpm_capable)
		return 1;

	dev_warn(&udev->dev, "Parent hub missing LPM exit latency info.  "
			"Power management will be impacted.\n");
	return 0;
}