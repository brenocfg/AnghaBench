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
struct stk_camera {int /*<<< orphan*/  udev; TYPE_1__* isobufs; } ;
struct TYPE_2__ {scalar_t__ urb; } ;

/* Variables and functions */
 int MAX_ISO_BUFS ; 
 int /*<<< orphan*/  STK_ERROR (char*) ; 
 scalar_t__ is_present (struct stk_camera*) ; 
 int /*<<< orphan*/  stk_camera_read_reg (struct stk_camera*,int,int*) ; 
 int /*<<< orphan*/  stk_camera_write_reg (struct stk_camera*,int,int) ; 
 scalar_t__ stk_sensor_sleep (struct stk_camera*) ; 
 int /*<<< orphan*/  unset_streaming (struct stk_camera*) ; 
 int /*<<< orphan*/  usb_kill_urb (scalar_t__) ; 
 scalar_t__ usb_set_interface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stk_stop_stream(struct stk_camera *dev)
{
	int value;
	int i;
	if (is_present(dev)) {
		stk_camera_read_reg(dev, 0x0100, &value);
		stk_camera_write_reg(dev, 0x0100, value & ~0x80);
		if (dev->isobufs != NULL) {
			for (i = 0; i < MAX_ISO_BUFS; i++) {
				if (dev->isobufs[i].urb)
					usb_kill_urb(dev->isobufs[i].urb);
			}
		}
		unset_streaming(dev);

		if (usb_set_interface(dev->udev, 0, 0))
			STK_ERROR("usb_set_interface failed !\n");
		if (stk_sensor_sleep(dev))
			STK_ERROR("error suspending the sensor\n");
	}
	return 0;
}