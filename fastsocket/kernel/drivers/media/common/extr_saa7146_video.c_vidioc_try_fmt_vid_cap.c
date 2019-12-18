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
struct TYPE_5__ {int field; int height; int width; int bytesperline; int sizeimage; int /*<<< orphan*/  pixelformat; } ;
struct TYPE_6__ {TYPE_2__ pix; } ;
struct v4l2_format {TYPE_3__ fmt; } ;
struct saa7146_vv {int last_field; TYPE_1__* standard; } ;
struct saa7146_format {int depth; } ;
struct saa7146_fh {struct saa7146_dev* dev; } ;
struct saa7146_dev {struct saa7146_vv* vv_data; } ;
struct file {int dummy; } ;
typedef  enum v4l2_field { ____Placeholder_v4l2_field } v4l2_field ;
struct TYPE_4__ {int h_max_out; int v_max_out; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEB_D (char*) ; 
 int /*<<< orphan*/  DEB_EE (char*) ; 
 int EINVAL ; 
 int PAGE_SIZE ; 
#define  V4L2_FIELD_ALTERNATE 131 
 int V4L2_FIELD_ANY ; 
#define  V4L2_FIELD_BOTTOM 130 
#define  V4L2_FIELD_INTERLACED 129 
#define  V4L2_FIELD_TOP 128 
 struct saa7146_format* saa7146_format_by_fourcc (struct saa7146_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vidioc_try_fmt_vid_cap(struct file *file, void *fh, struct v4l2_format *f)
{
	struct saa7146_dev *dev = ((struct saa7146_fh *)fh)->dev;
	struct saa7146_vv *vv = dev->vv_data;
	struct saa7146_format *fmt;
	enum v4l2_field field;
	int maxw, maxh;
	int calc_bpl;

	DEB_EE(("V4L2_BUF_TYPE_VIDEO_CAPTURE: dev:%p, fh:%p\n", dev, fh));

	fmt = saa7146_format_by_fourcc(dev, f->fmt.pix.pixelformat);
	if (NULL == fmt)
		return -EINVAL;

	field = f->fmt.pix.field;
	maxw  = vv->standard->h_max_out;
	maxh  = vv->standard->v_max_out;

	if (V4L2_FIELD_ANY == field) {
		field = (f->fmt.pix.height > maxh / 2)
			? V4L2_FIELD_INTERLACED
			: V4L2_FIELD_BOTTOM;
	}
	switch (field) {
	case V4L2_FIELD_ALTERNATE:
		vv->last_field = V4L2_FIELD_TOP;
		maxh = maxh / 2;
		break;
	case V4L2_FIELD_TOP:
	case V4L2_FIELD_BOTTOM:
		vv->last_field = V4L2_FIELD_INTERLACED;
		maxh = maxh / 2;
		break;
	case V4L2_FIELD_INTERLACED:
		vv->last_field = V4L2_FIELD_INTERLACED;
		break;
	default:
		DEB_D(("no known field mode '%d'.\n", field));
		return -EINVAL;
	}

	f->fmt.pix.field = field;
	if (f->fmt.pix.width > maxw)
		f->fmt.pix.width = maxw;
	if (f->fmt.pix.height > maxh)
		f->fmt.pix.height = maxh;

	calc_bpl = (f->fmt.pix.width * fmt->depth) / 8;

	if (f->fmt.pix.bytesperline < calc_bpl)
		f->fmt.pix.bytesperline = calc_bpl;

	if (f->fmt.pix.bytesperline > (2 * PAGE_SIZE * fmt->depth) / 8) /* arbitrary constraint */
		f->fmt.pix.bytesperline = calc_bpl;

	f->fmt.pix.sizeimage = f->fmt.pix.bytesperline * f->fmt.pix.height;
	DEB_D(("w:%d, h:%d, bytesperline:%d, sizeimage:%d\n", f->fmt.pix.width,
			f->fmt.pix.height, f->fmt.pix.bytesperline, f->fmt.pix.sizeimage));

	return 0;
}