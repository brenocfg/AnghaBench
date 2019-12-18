#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_7__ {int width; int height; } ;
struct TYPE_11__ {scalar_t__ if_type; } ;
struct vpif_params {TYPE_1__ std_info; TYPE_5__ iface; } ;
struct v4l2_pix_format {int field; scalar_t__ pixelformat; int bytesperline; int sizeimage; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_8__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_9__ {TYPE_2__ pix; } ;
struct TYPE_10__ {TYPE_3__ fmt; } ;
struct common_obj {scalar_t__ memory; TYPE_4__ fmt; } ;
struct channel_obj {size_t channel_id; struct vpif_params vpifparams; struct common_obj* common; } ;
typedef  enum v4l2_field { ____Placeholder_v4l2_field } v4l2_field ;
struct TYPE_12__ {int* channel_bufsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN (int,int) ; 
 int EINVAL ; 
 int V4L2_FIELD_ANY ; 
 scalar_t__ V4L2_MEMORY_USERPTR ; 
 scalar_t__ V4L2_PIX_FMT_SBGGR8 ; 
 scalar_t__ V4L2_PIX_FMT_YUV422P ; 
 scalar_t__ VPIF_IF_RAW_BAYER ; 
 int /*<<< orphan*/  VPIF_VALID_FIELD (int) ; 
 size_t VPIF_VIDEO_INDEX ; 
 TYPE_6__ config_params ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  vpif_dbg (int,int /*<<< orphan*/ ,char*) ; 
 int vpif_get_default_field (TYPE_5__*) ; 

__attribute__((used)) static int vpif_check_format(struct channel_obj *ch,
			     struct v4l2_pix_format *pixfmt,
			     int update)
{
	struct common_obj *common = &(ch->common[VPIF_VIDEO_INDEX]);
	struct vpif_params *vpif_params = &ch->vpifparams;
	enum v4l2_field field = pixfmt->field;
	u32 sizeimage, hpitch, vpitch;
	int ret = -EINVAL;

	vpif_dbg(2, debug, "vpif_check_format\n");
	/**
	 * first check for the pixel format. If if_type is Raw bayer,
	 * only V4L2_PIX_FMT_SBGGR8 format is supported. Otherwise only
	 * V4L2_PIX_FMT_YUV422P is supported
	 */
	if (vpif_params->iface.if_type == VPIF_IF_RAW_BAYER) {
		if (pixfmt->pixelformat != V4L2_PIX_FMT_SBGGR8) {
			if (!update) {
				vpif_dbg(2, debug, "invalid pix format\n");
				goto exit;
			}
			pixfmt->pixelformat = V4L2_PIX_FMT_SBGGR8;
		}
	} else {
		if (pixfmt->pixelformat != V4L2_PIX_FMT_YUV422P) {
			if (!update) {
				vpif_dbg(2, debug, "invalid pixel format\n");
				goto exit;
			}
			pixfmt->pixelformat = V4L2_PIX_FMT_YUV422P;
		}
	}

	if (!(VPIF_VALID_FIELD(field))) {
		if (!update) {
			vpif_dbg(2, debug, "invalid field format\n");
			goto exit;
		}
		/**
		 * By default use FIELD_NONE for RAW Bayer capture
		 * and FIELD_INTERLACED for other interfaces
		 */
		field = vpif_get_default_field(&vpif_params->iface);
	} else if (field == V4L2_FIELD_ANY)
		/* unsupported field. Use default */
		field = vpif_get_default_field(&vpif_params->iface);

	/* validate the hpitch */
	hpitch = pixfmt->bytesperline;
	if (hpitch < vpif_params->std_info.width) {
		if (!update) {
			vpif_dbg(2, debug, "invalid hpitch\n");
			goto exit;
		}
		hpitch = vpif_params->std_info.width;
	}

	if (V4L2_MEMORY_USERPTR == common->memory)
		sizeimage = pixfmt->sizeimage;
	else
		sizeimage = config_params.channel_bufsize[ch->channel_id];

	vpitch = sizeimage / (hpitch * 2);

	/* validate the vpitch */
	if (vpitch < vpif_params->std_info.height) {
		if (!update) {
			vpif_dbg(2, debug, "Invalid vpitch\n");
			goto exit;
		}
		vpitch = vpif_params->std_info.height;
	}

	/* Check for 8 byte alignment */
	if (!ALIGN(hpitch, 8)) {
		if (!update) {
			vpif_dbg(2, debug, "invalid pitch alignment\n");
			goto exit;
		}
		/* adjust to next 8 byte boundary */
		hpitch = (((hpitch + 7) / 8) * 8);
	}
	/* if update is set, modify the bytesperline and sizeimage */
	if (update) {
		pixfmt->bytesperline = hpitch;
		pixfmt->sizeimage = hpitch * vpitch * 2;
	}
	/**
	 * Image width and height is always based on current standard width and
	 * height
	 */
	pixfmt->width = common->fmt.fmt.pix.width;
	pixfmt->height = common->fmt.fmt.pix.height;
	return 0;
exit:
	return ret;
}