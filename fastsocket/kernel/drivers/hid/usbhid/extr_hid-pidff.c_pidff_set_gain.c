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
typedef  int /*<<< orphan*/  u16 ;
struct pidff_device {int /*<<< orphan*/ * reports; int /*<<< orphan*/  hid; int /*<<< orphan*/ * device_gain; } ;
struct input_dev {TYPE_1__* ff; } ;
struct TYPE_2__ {struct pidff_device* private; } ;

/* Variables and functions */
 size_t PID_DEVICE_GAIN ; 
 size_t PID_DEVICE_GAIN_FIELD ; 
 int /*<<< orphan*/  USB_DIR_OUT ; 
 int /*<<< orphan*/  pidff_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbhid_submit_report (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pidff_set_gain(struct input_dev *dev, u16 gain)
{
	struct pidff_device *pidff = dev->ff->private;

	pidff_set(&pidff->device_gain[PID_DEVICE_GAIN_FIELD], gain);
	usbhid_submit_report(pidff->hid, pidff->reports[PID_DEVICE_GAIN],
			  USB_DIR_OUT);
}