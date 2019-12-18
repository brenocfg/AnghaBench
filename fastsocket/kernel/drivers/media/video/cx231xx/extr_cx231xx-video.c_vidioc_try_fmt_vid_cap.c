#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned int width; unsigned int height; int bytesperline; unsigned int sizeimage; int /*<<< orphan*/  field; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  pixelformat; } ;
struct TYPE_4__ {TYPE_1__ pix; } ;
struct v4l2_format {TYPE_2__ fmt; } ;
struct file {int dummy; } ;
struct cx231xx_fmt {int depth; int /*<<< orphan*/  fourcc; } ;
struct cx231xx_fh {struct cx231xx* dev; } ;
struct cx231xx {int width; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_SMPTE170M ; 
 int /*<<< orphan*/  V4L2_FIELD_INTERLACED ; 
 int /*<<< orphan*/  cx231xx_videodbg (char*,int /*<<< orphan*/ ) ; 
 struct cx231xx_fmt* format_by_fourcc (int /*<<< orphan*/ ) ; 
 unsigned int norm_maxh (struct cx231xx*) ; 
 unsigned int norm_maxw (struct cx231xx*) ; 
 int /*<<< orphan*/  v4l_bound_align_image (unsigned int*,int,unsigned int,int,unsigned int*,int,unsigned int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vidioc_try_fmt_vid_cap(struct file *file, void *priv,
				  struct v4l2_format *f)
{
	struct cx231xx_fh *fh = priv;
	struct cx231xx *dev = fh->dev;
	unsigned int width = f->fmt.pix.width;
	unsigned int height = f->fmt.pix.height;
	unsigned int maxw = norm_maxw(dev);
	unsigned int maxh = norm_maxh(dev);
	struct cx231xx_fmt *fmt;

	fmt = format_by_fourcc(f->fmt.pix.pixelformat);
	if (!fmt) {
		cx231xx_videodbg("Fourcc format (%08x) invalid.\n",
				 f->fmt.pix.pixelformat);
		return -EINVAL;
	}

	/* width must even because of the YUYV format
	   height must be even because of interlacing */
	v4l_bound_align_image(&width, 48, maxw, 1, &height, 32, maxh, 1, 0);

	f->fmt.pix.width = width;
	f->fmt.pix.height = height;
	f->fmt.pix.pixelformat = fmt->fourcc;
	f->fmt.pix.bytesperline = (dev->width * fmt->depth + 7) >> 3;
	f->fmt.pix.sizeimage = f->fmt.pix.bytesperline * height;
	f->fmt.pix.colorspace = V4L2_COLORSPACE_SMPTE170M;
	f->fmt.pix.field = V4L2_FIELD_INTERLACED;

	return 0;
}