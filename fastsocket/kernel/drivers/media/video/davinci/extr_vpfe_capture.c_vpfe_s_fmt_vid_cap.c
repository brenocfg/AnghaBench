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
struct vpfe_pixel_format {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pix; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct vpfe_device {int /*<<< orphan*/  lock; struct v4l2_format fmt; int /*<<< orphan*/  v4l2_dev; scalar_t__ started; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  debug ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 
 struct vpfe_device* video_drvdata (struct file*) ; 
 struct vpfe_pixel_format* vpfe_check_format (struct vpfe_device*,int /*<<< orphan*/ *) ; 
 int vpfe_config_ccdc_image_format (struct vpfe_device*) ; 
 int /*<<< orphan*/  vpfe_detach_irq (struct vpfe_device*) ; 

__attribute__((used)) static int vpfe_s_fmt_vid_cap(struct file *file, void *priv,
				struct v4l2_format *fmt)
{
	struct vpfe_device *vpfe_dev = video_drvdata(file);
	const struct vpfe_pixel_format *pix_fmts;
	int ret = 0;

	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev, "vpfe_s_fmt_vid_cap\n");

	/* If streaming is started, return error */
	if (vpfe_dev->started) {
		v4l2_err(&vpfe_dev->v4l2_dev, "Streaming is started\n");
		return -EBUSY;
	}

	/* Check for valid frame format */
	pix_fmts = vpfe_check_format(vpfe_dev, &fmt->fmt.pix);

	if (NULL == pix_fmts)
		return -EINVAL;

	/* store the pixel format in the device  object */
	ret = mutex_lock_interruptible(&vpfe_dev->lock);
	if (ret)
		return ret;

	/* First detach any IRQ if currently attached */
	vpfe_detach_irq(vpfe_dev);
	vpfe_dev->fmt = *fmt;
	/* set image capture parameters in the ccdc */
	ret = vpfe_config_ccdc_image_format(vpfe_dev);
	mutex_unlock(&vpfe_dev->lock);
	return ret;
}