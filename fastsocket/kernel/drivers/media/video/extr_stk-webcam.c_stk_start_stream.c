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
struct stk_camera {int /*<<< orphan*/  urbs_used; TYPE_1__* isobufs; int /*<<< orphan*/  udev; } ;
struct TYPE_2__ {scalar_t__ urb; } ;

/* Variables and functions */
 int EFAULT ; 
 int ENODEV ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MAX_ISO_BUFS ; 
 int /*<<< orphan*/  STK_ERROR (char*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_initialised (struct stk_camera*) ; 
 int /*<<< orphan*/  is_memallocd (struct stk_camera*) ; 
 int /*<<< orphan*/  is_present (struct stk_camera*) ; 
 int /*<<< orphan*/  set_streaming (struct stk_camera*) ; 
 int /*<<< orphan*/  stk_camera_read_reg (struct stk_camera*,int,int*) ; 
 int /*<<< orphan*/  stk_camera_write_reg (struct stk_camera*,int,int) ; 
 scalar_t__ stk_sensor_wakeup (struct stk_camera*) ; 
 int usb_set_interface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int usb_submit_urb (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stk_start_stream(struct stk_camera *dev)
{
	int value;
	int i, ret;
	int value_116, value_117;

	if (!is_present(dev))
		return -ENODEV;
	if (!is_memallocd(dev) || !is_initialised(dev)) {
		STK_ERROR("FIXME: Buffers are not allocated\n");
		return -EFAULT;
	}
	ret = usb_set_interface(dev->udev, 0, 5);

	if (ret < 0)
		STK_ERROR("usb_set_interface failed !\n");
	if (stk_sensor_wakeup(dev))
		STK_ERROR("error awaking the sensor\n");

	stk_camera_read_reg(dev, 0x0116, &value_116);
	stk_camera_read_reg(dev, 0x0117, &value_117);

	stk_camera_write_reg(dev, 0x0116, 0x0000);
	stk_camera_write_reg(dev, 0x0117, 0x0000);

	stk_camera_read_reg(dev, 0x0100, &value);
	stk_camera_write_reg(dev, 0x0100, value | 0x80);

	stk_camera_write_reg(dev, 0x0116, value_116);
	stk_camera_write_reg(dev, 0x0117, value_117);
	for (i = 0; i < MAX_ISO_BUFS; i++) {
		if (dev->isobufs[i].urb) {
			ret = usb_submit_urb(dev->isobufs[i].urb, GFP_KERNEL);
			atomic_inc(&dev->urbs_used);
			if (ret)
				return ret;
		}
	}
	set_streaming(dev);
	return 0;
}