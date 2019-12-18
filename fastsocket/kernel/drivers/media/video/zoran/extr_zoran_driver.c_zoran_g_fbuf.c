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
struct TYPE_7__ {TYPE_2__* format; } ;
struct zoran_fh {TYPE_3__ overlay_settings; struct zoran* zr; } ;
struct TYPE_5__ {scalar_t__ format; } ;
struct zoran {int /*<<< orphan*/  resource_lock; int /*<<< orphan*/  vbuf_bytesperline; TYPE_1__ overlay_settings; int /*<<< orphan*/  vbuf_height; int /*<<< orphan*/  vbuf_width; int /*<<< orphan*/  vbuf_base; } ;
struct TYPE_8__ {int /*<<< orphan*/  field; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  bytesperline; int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct v4l2_framebuffer {int /*<<< orphan*/  capability; int /*<<< orphan*/  flags; TYPE_4__ fmt; int /*<<< orphan*/  base; } ;
struct file {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  fourcc; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_COLORSPACE_SRGB ; 
 int /*<<< orphan*/  V4L2_FBUF_CAP_LIST_CLIPPING ; 
 int /*<<< orphan*/  V4L2_FBUF_FLAG_OVERLAY ; 
 int /*<<< orphan*/  V4L2_FIELD_INTERLACED ; 
 int /*<<< orphan*/  memset (struct v4l2_framebuffer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int zoran_g_fbuf(struct file *file, void *__fh,
		struct v4l2_framebuffer *fb)
{
	struct zoran_fh *fh = __fh;
	struct zoran *zr = fh->zr;

	memset(fb, 0, sizeof(*fb));
	mutex_lock(&zr->resource_lock);
	fb->base = zr->vbuf_base;
	fb->fmt.width = zr->vbuf_width;
	fb->fmt.height = zr->vbuf_height;
	if (zr->overlay_settings.format)
		fb->fmt.pixelformat = fh->overlay_settings.format->fourcc;
	fb->fmt.bytesperline = zr->vbuf_bytesperline;
	mutex_unlock(&zr->resource_lock);
	fb->fmt.colorspace = V4L2_COLORSPACE_SRGB;
	fb->fmt.field = V4L2_FIELD_INTERLACED;
	fb->flags = V4L2_FBUF_FLAG_OVERLAY;
	fb->capability = V4L2_FBUF_CAP_LIST_CLIPPING;

	return 0;
}