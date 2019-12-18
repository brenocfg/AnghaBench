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
struct stk_camera {int /*<<< orphan*/  interface; struct file* owner; } ;
struct file {struct stk_camera* private_data; } ;

/* Variables and functions */
 scalar_t__ is_present (struct stk_camera*) ; 
 int /*<<< orphan*/  stk_free_buffers (struct stk_camera*) ; 
 int /*<<< orphan*/  stk_stop_stream (struct stk_camera*) ; 
 int /*<<< orphan*/  usb_autopm_put_interface (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int v4l_stk_release(struct file *fp)
{
	struct stk_camera *dev = fp->private_data;

	if (dev->owner == fp) {
		stk_stop_stream(dev);
		stk_free_buffers(dev);
		dev->owner = NULL;
	}

	if(is_present(dev))
		usb_autopm_put_interface(dev->interface);

	return 0;
}