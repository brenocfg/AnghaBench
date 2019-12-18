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
struct v4l2_dbg_chip_ident {int dummy; } ;
struct gspca_dev {int /*<<< orphan*/  usb_lock; TYPE_1__* sd_desc; scalar_t__ present; scalar_t__ usb_err; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int (* get_chip_ident ) (struct gspca_dev*,struct v4l2_dbg_chip_ident*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ERESTARTSYS ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct gspca_dev*,struct v4l2_dbg_chip_ident*) ; 

__attribute__((used)) static int vidioc_g_chip_ident(struct file *file, void *priv,
			struct v4l2_dbg_chip_ident *chip)
{
	int ret;
	struct gspca_dev *gspca_dev = priv;

	if (!gspca_dev->sd_desc->get_chip_ident)
		return -EINVAL;

	if (mutex_lock_interruptible(&gspca_dev->usb_lock))
		return -ERESTARTSYS;
	gspca_dev->usb_err = 0;
	if (gspca_dev->present)
		ret = gspca_dev->sd_desc->get_chip_ident(gspca_dev, chip);
	else
		ret = -ENODEV;
	mutex_unlock(&gspca_dev->usb_lock);

	return ret;
}