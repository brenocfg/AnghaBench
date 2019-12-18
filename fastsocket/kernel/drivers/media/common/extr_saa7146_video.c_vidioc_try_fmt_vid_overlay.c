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
struct TYPE_8__ {int width; int height; } ;
struct v4l2_window {int clipcount; int field; TYPE_4__ w; } ;
struct TYPE_5__ {struct v4l2_window win; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct TYPE_6__ {int /*<<< orphan*/ * base; } ;
struct saa7146_vv {TYPE_3__* standard; int /*<<< orphan*/ * ov_fmt; TYPE_2__ ov_fb; } ;
struct saa7146_fh {struct saa7146_dev* dev; } ;
struct saa7146_dev {struct saa7146_vv* vv_data; } ;
struct file {int dummy; } ;
typedef  enum v4l2_field { ____Placeholder_v4l2_field } v4l2_field ;
struct TYPE_7__ {int h_max_out; int v_max_out; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEB_D (char*) ; 
 int /*<<< orphan*/  DEB_EE (char*) ; 
 int EINVAL ; 
#define  V4L2_FIELD_ALTERNATE 131 
 int V4L2_FIELD_ANY ; 
#define  V4L2_FIELD_BOTTOM 130 
#define  V4L2_FIELD_INTERLACED 129 
#define  V4L2_FIELD_TOP 128 

__attribute__((used)) static int vidioc_try_fmt_vid_overlay(struct file *file, void *fh, struct v4l2_format *f)
{
	struct saa7146_dev *dev = ((struct saa7146_fh *)fh)->dev;
	struct saa7146_vv *vv = dev->vv_data;
	struct v4l2_window *win = &f->fmt.win;
	enum v4l2_field field;
	int maxw, maxh;

	DEB_EE(("dev:%p\n", dev));

	if (NULL == vv->ov_fb.base) {
		DEB_D(("no fb base set.\n"));
		return -EINVAL;
	}
	if (NULL == vv->ov_fmt) {
		DEB_D(("no fb fmt set.\n"));
		return -EINVAL;
	}
	if (win->w.width < 48 || win->w.height < 32) {
		DEB_D(("min width/height. (%d,%d)\n", win->w.width, win->w.height));
		return -EINVAL;
	}
	if (win->clipcount > 16) {
		DEB_D(("clipcount too big.\n"));
		return -EINVAL;
	}

	field = win->field;
	maxw  = vv->standard->h_max_out;
	maxh  = vv->standard->v_max_out;

	if (V4L2_FIELD_ANY == field) {
		field = (win->w.height > maxh / 2)
			? V4L2_FIELD_INTERLACED
			: V4L2_FIELD_TOP;
		}
	switch (field) {
	case V4L2_FIELD_TOP:
	case V4L2_FIELD_BOTTOM:
	case V4L2_FIELD_ALTERNATE:
		maxh = maxh / 2;
		break;
	case V4L2_FIELD_INTERLACED:
		break;
	default:
		DEB_D(("no known field mode '%d'.\n", field));
		return -EINVAL;
	}

	win->field = field;
	if (win->w.width > maxw)
		win->w.width = maxw;
	if (win->w.height > maxh)
		win->w.height = maxh;

	return 0;
}