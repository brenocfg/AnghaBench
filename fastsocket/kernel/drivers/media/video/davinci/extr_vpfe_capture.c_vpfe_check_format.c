#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_9__ {scalar_t__ pixelformat; } ;
struct vpfe_pixel_format {scalar_t__ bpp; TYPE_2__ fmtdesc; } ;
struct TYPE_13__ {scalar_t__ active_pixels; scalar_t__ active_lines; int /*<<< orphan*/  frame_format; } ;
struct TYPE_10__ {scalar_t__ pixelformat; int field; } ;
struct TYPE_11__ {TYPE_3__ pix; } ;
struct TYPE_12__ {TYPE_4__ fmt; } ;
struct vpfe_device {int /*<<< orphan*/  v4l2_dev; TYPE_6__ std_info; TYPE_5__ fmt; } ;
struct v4l2_pix_format {scalar_t__ pixelformat; int field; int width; int height; int bytesperline; int sizeimage; } ;
struct TYPE_8__ {scalar_t__ (* enum_pix ) (scalar_t__*,int) ;} ;
struct TYPE_14__ {TYPE_1__ hw_ops; } ;

/* Variables and functions */
 int V4L2_FIELD_ANY ; 
#define  V4L2_FIELD_INTERLACED 130 
#define  V4L2_FIELD_NONE 129 
#define  V4L2_FIELD_SEQ_TB 128 
 scalar_t__ V4L2_PIX_FMT_NV12 ; 
 TYPE_7__* ccdc_dev ; 
 void* clamp (int,scalar_t__,scalar_t__) ; 
 scalar_t__ stub1 (scalar_t__*,int) ; 
 int /*<<< orphan*/  v4l2_info (int /*<<< orphan*/ *,char*,int,int,int,...) ; 
 struct vpfe_pixel_format* vpfe_lookup_pix_format (scalar_t__) ; 

__attribute__((used)) static const struct vpfe_pixel_format *
	vpfe_check_format(struct vpfe_device *vpfe_dev,
			  struct v4l2_pix_format *pixfmt)
{
	u32 min_height = 1, min_width = 32, max_width, max_height;
	const struct vpfe_pixel_format *vpfe_pix_fmt;
	u32 pix;
	int temp, found;

	vpfe_pix_fmt = vpfe_lookup_pix_format(pixfmt->pixelformat);
	if (NULL == vpfe_pix_fmt) {
		/*
		 * use current pixel format in the vpfe device. We
		 * will find this pix format in the table
		 */
		pixfmt->pixelformat = vpfe_dev->fmt.fmt.pix.pixelformat;
		vpfe_pix_fmt = vpfe_lookup_pix_format(pixfmt->pixelformat);
	}

	/* check if hw supports it */
	temp = 0;
	found = 0;
	while (ccdc_dev->hw_ops.enum_pix(&pix, temp) >= 0) {
		if (vpfe_pix_fmt->fmtdesc.pixelformat == pix) {
			found = 1;
			break;
		}
		temp++;
	}

	if (!found) {
		/* use current pixel format */
		pixfmt->pixelformat = vpfe_dev->fmt.fmt.pix.pixelformat;
		/*
		 * Since this is currently used in the vpfe device, we
		 * will find this pix format in the table
		 */
		vpfe_pix_fmt = vpfe_lookup_pix_format(pixfmt->pixelformat);
	}

	/* check what field format is supported */
	if (pixfmt->field == V4L2_FIELD_ANY) {
		/* if field is any, use current value as default */
		pixfmt->field = vpfe_dev->fmt.fmt.pix.field;
	}

	/*
	 * if field is not same as current field in the vpfe device
	 * try matching the field with the sub device field
	 */
	if (vpfe_dev->fmt.fmt.pix.field != pixfmt->field) {
		/*
		 * If field value is not in the supported fields, use current
		 * field used in the device as default
		 */
		switch (pixfmt->field) {
		case V4L2_FIELD_INTERLACED:
		case V4L2_FIELD_SEQ_TB:
			/* if sub device is supporting progressive, use that */
			if (!vpfe_dev->std_info.frame_format)
				pixfmt->field = V4L2_FIELD_NONE;
			break;
		case V4L2_FIELD_NONE:
			if (vpfe_dev->std_info.frame_format)
				pixfmt->field = V4L2_FIELD_INTERLACED;
			break;

		default:
			/* use current field as default */
			pixfmt->field = vpfe_dev->fmt.fmt.pix.field;
			break;
		}
	}

	/* Now adjust image resolutions supported */
	if (pixfmt->field == V4L2_FIELD_INTERLACED ||
	    pixfmt->field == V4L2_FIELD_SEQ_TB)
		min_height = 2;

	max_width = vpfe_dev->std_info.active_pixels;
	max_height = vpfe_dev->std_info.active_lines;
	min_width /= vpfe_pix_fmt->bpp;

	v4l2_info(&vpfe_dev->v4l2_dev, "width = %d, height = %d, bpp = %d\n",
		  pixfmt->width, pixfmt->height, vpfe_pix_fmt->bpp);

	pixfmt->width = clamp((pixfmt->width), min_width, max_width);
	pixfmt->height = clamp((pixfmt->height), min_height, max_height);

	/* If interlaced, adjust height to be a multiple of 2 */
	if (pixfmt->field == V4L2_FIELD_INTERLACED)
		pixfmt->height &= (~1);
	/*
	 * recalculate bytesperline and sizeimage since width
	 * and height might have changed
	 */
	pixfmt->bytesperline = (((pixfmt->width * vpfe_pix_fmt->bpp) + 31)
				& ~31);
	if (pixfmt->pixelformat == V4L2_PIX_FMT_NV12)
		pixfmt->sizeimage =
			pixfmt->bytesperline * pixfmt->height +
			((pixfmt->bytesperline * pixfmt->height) >> 1);
	else
		pixfmt->sizeimage = pixfmt->bytesperline * pixfmt->height;

	v4l2_info(&vpfe_dev->v4l2_dev, "adjusted width = %d, height ="
		 " %d, bpp = %d, bytesperline = %d, sizeimage = %d\n",
		 pixfmt->width, pixfmt->height, vpfe_pix_fmt->bpp,
		 pixfmt->bytesperline, pixfmt->sizeimage);
	return vpfe_pix_fmt;
}