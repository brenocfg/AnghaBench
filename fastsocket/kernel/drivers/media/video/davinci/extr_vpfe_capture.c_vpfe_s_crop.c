#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ top; scalar_t__ left; int width; scalar_t__ height; } ;
struct TYPE_10__ {scalar_t__ width; scalar_t__ height; int bytesperline; int sizeimage; } ;
struct TYPE_11__ {TYPE_3__ pix; } ;
struct TYPE_12__ {TYPE_4__ fmt; } ;
struct TYPE_8__ {scalar_t__ active_pixels; scalar_t__ active_lines; } ;
struct vpfe_device {int /*<<< orphan*/  lock; TYPE_6__ crop; TYPE_5__ fmt; int /*<<< orphan*/  v4l2_dev; TYPE_1__ std_info; scalar_t__ started; } ;
struct v4l2_crop {TYPE_6__ c; } ;
struct file {int dummy; } ;
struct TYPE_9__ {int (* get_line_length ) () ;int /*<<< orphan*/  (* set_image_window ) (TYPE_6__*) ;} ;
struct TYPE_14__ {TYPE_2__ hw_ops; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 TYPE_7__* ccdc_dev ; 
 int /*<<< orphan*/  debug ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*) ; 
 int stub2 () ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 
 struct vpfe_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int vpfe_s_crop(struct file *file, void *priv,
			     struct v4l2_crop *crop)
{
	struct vpfe_device *vpfe_dev = video_drvdata(file);
	int ret = 0;

	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev, "vpfe_s_crop\n");

	if (vpfe_dev->started) {
		/* make sure streaming is not started */
		v4l2_err(&vpfe_dev->v4l2_dev,
			"Cannot change crop when streaming is ON\n");
		return -EBUSY;
	}

	ret = mutex_lock_interruptible(&vpfe_dev->lock);
	if (ret)
		return ret;

	if (crop->c.top < 0 || crop->c.left < 0) {
		v4l2_err(&vpfe_dev->v4l2_dev,
			"doesn't support negative values for top & left\n");
		ret = -EINVAL;
		goto unlock_out;
	}

	/* adjust the width to 16 pixel boundry */
	crop->c.width = ((crop->c.width + 15) & ~0xf);

	/* make sure parameters are valid */
	if ((crop->c.left + crop->c.width >
		vpfe_dev->std_info.active_pixels) ||
	    (crop->c.top + crop->c.height >
		vpfe_dev->std_info.active_lines)) {
		v4l2_err(&vpfe_dev->v4l2_dev, "Error in S_CROP params\n");
		ret = -EINVAL;
		goto unlock_out;
	}
	ccdc_dev->hw_ops.set_image_window(&crop->c);
	vpfe_dev->fmt.fmt.pix.width = crop->c.width;
	vpfe_dev->fmt.fmt.pix.height = crop->c.height;
	vpfe_dev->fmt.fmt.pix.bytesperline =
		ccdc_dev->hw_ops.get_line_length();
	vpfe_dev->fmt.fmt.pix.sizeimage =
		vpfe_dev->fmt.fmt.pix.bytesperline *
		vpfe_dev->fmt.fmt.pix.height;
	vpfe_dev->crop = crop->c;
unlock_out:
	mutex_unlock(&vpfe_dev->lock);
	return ret;
}