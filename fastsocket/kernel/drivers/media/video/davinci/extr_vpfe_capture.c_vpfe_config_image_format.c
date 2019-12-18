#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int v4l2_std_id ;
struct vpfe_subdev_info {int /*<<< orphan*/  grp_id; } ;
struct TYPE_13__ {int height; int bytesperline; int sizeimage; int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  field; int /*<<< orphan*/  width; } ;
struct TYPE_14__ {TYPE_4__ pix; } ;
struct TYPE_16__ {TYPE_5__ fmt; } ;
struct TYPE_11__ {int active_lines; int /*<<< orphan*/  frame_format; int /*<<< orphan*/  active_pixels; } ;
struct TYPE_10__ {int height; int /*<<< orphan*/  width; scalar_t__ left; scalar_t__ top; } ;
struct vpfe_device {int std_index; TYPE_7__ fmt; int /*<<< orphan*/  v4l2_dev; TYPE_2__ std_info; TYPE_1__ crop; struct vpfe_subdev_info* current_subdev; } ;
struct TYPE_12__ {int (* get_line_length ) () ;} ;
struct TYPE_17__ {TYPE_3__ hw_ops; } ;
struct TYPE_15__ {int const std_id; int height; int /*<<< orphan*/  frame_format; int /*<<< orphan*/  width; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_6__*) ; 
 int EINVAL ; 
 int ENOIOCTLCMD ; 
 int /*<<< orphan*/  V4L2_FIELD_INTERLACED ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_SBGGR8 ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_UYVY ; 
 TYPE_8__* ccdc_dev ; 
 int /*<<< orphan*/  g_fmt ; 
 int stub1 () ; 
 int v4l2_device_call_until_err (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_7__*) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  video ; 
 int vpfe_config_ccdc_image_format (struct vpfe_device*) ; 
 TYPE_6__* vpfe_standards ; 

__attribute__((used)) static int vpfe_config_image_format(struct vpfe_device *vpfe_dev,
				    const v4l2_std_id *std_id)
{
	struct vpfe_subdev_info *sdinfo = vpfe_dev->current_subdev;
	int i, ret = 0;

	for (i = 0; i < ARRAY_SIZE(vpfe_standards); i++) {
		if (vpfe_standards[i].std_id & *std_id) {
			vpfe_dev->std_info.active_pixels =
					vpfe_standards[i].width;
			vpfe_dev->std_info.active_lines =
					vpfe_standards[i].height;
			vpfe_dev->std_info.frame_format =
					vpfe_standards[i].frame_format;
			vpfe_dev->std_index = i;
			break;
		}
	}

	if (i ==  ARRAY_SIZE(vpfe_standards)) {
		v4l2_err(&vpfe_dev->v4l2_dev, "standard not supported\n");
		return -EINVAL;
	}

	vpfe_dev->crop.top = 0;
	vpfe_dev->crop.left = 0;
	vpfe_dev->crop.width = vpfe_dev->std_info.active_pixels;
	vpfe_dev->crop.height = vpfe_dev->std_info.active_lines;
	vpfe_dev->fmt.fmt.pix.width = vpfe_dev->crop.width;
	vpfe_dev->fmt.fmt.pix.height = vpfe_dev->crop.height;

	/* first field and frame format based on standard frame format */
	if (vpfe_dev->std_info.frame_format) {
		vpfe_dev->fmt.fmt.pix.field = V4L2_FIELD_INTERLACED;
		/* assume V4L2_PIX_FMT_UYVY as default */
		vpfe_dev->fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_UYVY;
	} else {
		vpfe_dev->fmt.fmt.pix.field = V4L2_FIELD_NONE;
		/* assume V4L2_PIX_FMT_SBGGR8 */
		vpfe_dev->fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_SBGGR8;
	}

	/* if sub device supports g_fmt, override the defaults */
	ret = v4l2_device_call_until_err(&vpfe_dev->v4l2_dev,
			sdinfo->grp_id, video, g_fmt, &vpfe_dev->fmt);

	if (ret && ret != -ENOIOCTLCMD) {
		v4l2_err(&vpfe_dev->v4l2_dev,
			"error in getting g_fmt from sub device\n");
		return ret;
	}

	/* Sets the values in CCDC */
	ret = vpfe_config_ccdc_image_format(vpfe_dev);
	if (ret)
		return ret;

	/* Update the values of sizeimage and bytesperline */
	if (!ret) {
		vpfe_dev->fmt.fmt.pix.bytesperline =
			ccdc_dev->hw_ops.get_line_length();
		vpfe_dev->fmt.fmt.pix.sizeimage =
			vpfe_dev->fmt.fmt.pix.bytesperline *
			vpfe_dev->fmt.fmt.pix.height;
	}
	return ret;
}