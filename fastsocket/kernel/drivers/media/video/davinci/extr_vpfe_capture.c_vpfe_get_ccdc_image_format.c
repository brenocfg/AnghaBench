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
struct vpfe_device {int /*<<< orphan*/  v4l2_dev; } ;
struct v4l2_rect {int height; int /*<<< orphan*/  width; } ;
struct TYPE_6__ {int height; int bytesperline; int sizeimage; int /*<<< orphan*/  field; int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  width; } ;
struct TYPE_7__ {TYPE_2__ pix; } ;
struct v4l2_format {TYPE_3__ fmt; int /*<<< orphan*/  type; } ;
typedef  enum ccdc_frmfmt { ____Placeholder_ccdc_frmfmt } ccdc_frmfmt ;
typedef  enum ccdc_buftype { ____Placeholder_ccdc_buftype } ccdc_buftype ;
struct TYPE_5__ {int (* get_line_length ) () ;int (* get_buftype ) () ;int (* get_frame_format ) () ;int /*<<< orphan*/  (* get_pixel_format ) () ;int /*<<< orphan*/  (* get_image_window ) (struct v4l2_rect*) ;} ;
struct TYPE_8__ {TYPE_1__ hw_ops; } ;

/* Variables and functions */
 int CCDC_BUFTYPE_FLD_INTERLEAVED ; 
 int CCDC_BUFTYPE_FLD_SEPARATED ; 
 int CCDC_FRMFMT_INTERLACED ; 
 int CCDC_FRMFMT_PROGRESSIVE ; 
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
 int /*<<< orphan*/  V4L2_FIELD_INTERLACED ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 int /*<<< orphan*/  V4L2_FIELD_SEQ_TB ; 
 TYPE_4__* ccdc_dev ; 
 int /*<<< orphan*/  memset (struct v4l2_format*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct v4l2_rect*) ; 
 int stub2 () ; 
 int stub3 () ; 
 int /*<<< orphan*/  stub4 () ; 
 int stub5 () ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int vpfe_get_ccdc_image_format(struct vpfe_device *vpfe_dev,
				 struct v4l2_format *f)
{
	struct v4l2_rect image_win;
	enum ccdc_buftype buf_type;
	enum ccdc_frmfmt frm_fmt;

	memset(f, 0, sizeof(*f));
	f->type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	ccdc_dev->hw_ops.get_image_window(&image_win);
	f->fmt.pix.width = image_win.width;
	f->fmt.pix.height = image_win.height;
	f->fmt.pix.bytesperline = ccdc_dev->hw_ops.get_line_length();
	f->fmt.pix.sizeimage = f->fmt.pix.bytesperline *
				f->fmt.pix.height;
	buf_type = ccdc_dev->hw_ops.get_buftype();
	f->fmt.pix.pixelformat = ccdc_dev->hw_ops.get_pixel_format();
	frm_fmt = ccdc_dev->hw_ops.get_frame_format();
	if (frm_fmt == CCDC_FRMFMT_PROGRESSIVE)
		f->fmt.pix.field = V4L2_FIELD_NONE;
	else if (frm_fmt == CCDC_FRMFMT_INTERLACED) {
		if (buf_type == CCDC_BUFTYPE_FLD_INTERLEAVED)
			f->fmt.pix.field = V4L2_FIELD_INTERLACED;
		else if (buf_type == CCDC_BUFTYPE_FLD_SEPARATED)
			f->fmt.pix.field = V4L2_FIELD_SEQ_TB;
		else {
			v4l2_err(&vpfe_dev->v4l2_dev, "Invalid buf_type\n");
			return -EINVAL;
		}
	} else {
		v4l2_err(&vpfe_dev->v4l2_dev, "Invalid frm_fmt\n");
		return -EINVAL;
	}
	return 0;
}