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
struct v4l2_rect {scalar_t__ top; scalar_t__ height; scalar_t__ left; scalar_t__ width; } ;
struct TYPE_2__ {scalar_t__ height; scalar_t__ width; scalar_t__ top; scalar_t__ left; } ;
struct v4l2_crop {scalar_t__ type; TYPE_1__ c; } ;
struct saa7134_fh {struct saa7134_dev* dev; } ;
struct saa7134_dev {TYPE_1__ crop_current; struct v4l2_rect crop_bounds; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  RESOURCE_OVERLAY ; 
 int /*<<< orphan*/  RESOURCE_VIDEO ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OVERLAY ; 
 scalar_t__ res_locked (struct saa7134_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int saa7134_s_crop(struct file *file, void *f, struct v4l2_crop *crop)
{
	struct saa7134_fh *fh = f;
	struct saa7134_dev *dev = fh->dev;
	struct v4l2_rect *b = &dev->crop_bounds;

	if (crop->type != V4L2_BUF_TYPE_VIDEO_CAPTURE &&
	    crop->type != V4L2_BUF_TYPE_VIDEO_OVERLAY)
		return -EINVAL;
	if (crop->c.height < 0)
		return -EINVAL;
	if (crop->c.width < 0)
		return -EINVAL;

	if (res_locked(fh->dev, RESOURCE_OVERLAY))
		return -EBUSY;
	if (res_locked(fh->dev, RESOURCE_VIDEO))
		return -EBUSY;

	if (crop->c.top < b->top)
		crop->c.top = b->top;
	if (crop->c.top > b->top + b->height)
		crop->c.top = b->top + b->height;
	if (crop->c.height > b->top - crop->c.top + b->height)
		crop->c.height = b->top - crop->c.top + b->height;

	if (crop->c.left < b->left)
		crop->c.left = b->left;
	if (crop->c.left > b->left + b->width)
		crop->c.left = b->left + b->width;
	if (crop->c.width > b->left - crop->c.left + b->width)
		crop->c.width = b->left - crop->c.left + b->width;

	dev->crop_current = crop->c;
	return 0;
}