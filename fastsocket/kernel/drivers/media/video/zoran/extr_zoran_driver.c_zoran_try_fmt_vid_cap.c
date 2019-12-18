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
struct zoran_fh {struct zoran* zr; } ;
struct zoran {int /*<<< orphan*/  resource_lock; } ;
struct TYPE_4__ {scalar_t__ pixelformat; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_5__ {TYPE_1__ pix; } ;
struct v4l2_format {TYPE_2__ fmt; } ;
struct file {int dummy; } ;
struct TYPE_6__ {scalar_t__ fourcc; int /*<<< orphan*/  depth; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUZ_MAX_HEIGHT ; 
 int /*<<< orphan*/  BUZ_MAX_WIDTH ; 
 int /*<<< orphan*/  BUZ_MIN_HEIGHT ; 
 int /*<<< orphan*/  BUZ_MIN_WIDTH ; 
 int DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int EINVAL ; 
 int NUM_FORMATS ; 
 scalar_t__ V4L2_PIX_FMT_MJPEG ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l_bound_align_image (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* zoran_formats ; 
 int zoran_try_fmt_vid_out (struct file*,struct zoran_fh*,struct v4l2_format*) ; 

__attribute__((used)) static int zoran_try_fmt_vid_cap(struct file *file, void *__fh,
					struct v4l2_format *fmt)
{
	struct zoran_fh *fh = __fh;
	struct zoran *zr = fh->zr;
	int bpp;
	int i;

	if (fmt->fmt.pix.pixelformat == V4L2_PIX_FMT_MJPEG)
		return zoran_try_fmt_vid_out(file, fh, fmt);

	mutex_lock(&zr->resource_lock);

	for (i = 0; i < NUM_FORMATS; i++)
		if (zoran_formats[i].fourcc == fmt->fmt.pix.pixelformat)
			break;

	if (i == NUM_FORMATS) {
		mutex_unlock(&zr->resource_lock);
		return -EINVAL;
	}

	bpp = DIV_ROUND_UP(zoran_formats[i].depth, 8);
	v4l_bound_align_image(
		&fmt->fmt.pix.width, BUZ_MIN_WIDTH, BUZ_MAX_WIDTH, bpp == 2 ? 1 : 2,
		&fmt->fmt.pix.height, BUZ_MIN_HEIGHT, BUZ_MAX_HEIGHT, 0, 0);
	mutex_unlock(&zr->resource_lock);

	return 0;
}