#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int height; int bytesperline; TYPE_1__* format; int /*<<< orphan*/  width; } ;
struct zoran_fh {scalar_t__ map_mode; TYPE_2__ v4l_settings; struct zoran* zr; } ;
struct zoran {int /*<<< orphan*/  resource_lock; } ;
struct TYPE_7__ {int height; int sizeimage; int bytesperline; int /*<<< orphan*/  field; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  width; } ;
struct TYPE_8__ {TYPE_3__ pix; } ;
struct v4l2_format {TYPE_4__ fmt; } ;
struct file {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  colorspace; int /*<<< orphan*/  fourcc; } ;

/* Variables and functions */
 int BUZ_MAX_HEIGHT ; 
 int /*<<< orphan*/  V4L2_FIELD_INTERLACED ; 
 int /*<<< orphan*/  V4L2_FIELD_TOP ; 
 scalar_t__ ZORAN_MAP_MODE_RAW ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int zoran_g_fmt_vid_out (struct file*,struct zoran_fh*,struct v4l2_format*) ; 

__attribute__((used)) static int zoran_g_fmt_vid_cap(struct file *file, void *__fh,
					struct v4l2_format *fmt)
{
	struct zoran_fh *fh = __fh;
	struct zoran *zr = fh->zr;

	if (fh->map_mode != ZORAN_MAP_MODE_RAW)
		return zoran_g_fmt_vid_out(file, fh, fmt);

	mutex_lock(&zr->resource_lock);
	fmt->fmt.pix.width = fh->v4l_settings.width;
	fmt->fmt.pix.height = fh->v4l_settings.height;
	fmt->fmt.pix.sizeimage = fh->v4l_settings.bytesperline *
					fh->v4l_settings.height;
	fmt->fmt.pix.pixelformat = fh->v4l_settings.format->fourcc;
	fmt->fmt.pix.colorspace = fh->v4l_settings.format->colorspace;
	fmt->fmt.pix.bytesperline = fh->v4l_settings.bytesperline;
	if (BUZ_MAX_HEIGHT < (fh->v4l_settings.height * 2))
		fmt->fmt.pix.field = V4L2_FIELD_INTERLACED;
	else
		fmt->fmt.pix.field = V4L2_FIELD_TOP;
	mutex_unlock(&zr->resource_lock);
	return 0;
}