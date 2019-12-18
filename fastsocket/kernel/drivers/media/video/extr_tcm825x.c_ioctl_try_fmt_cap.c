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
struct v4l2_pix_format {int width; int height; int pixelformat; int bytesperline; int sizeimage; int /*<<< orphan*/  colorspace; scalar_t__ priv; int /*<<< orphan*/  field; } ;
struct v4l2_int_device {struct tcm825x_sensor* priv; } ;
struct TYPE_5__ {struct v4l2_pix_format pix; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct tcm825x_sensor {TYPE_2__* i2c_client; } ;
typedef  enum image_size { ____Placeholder_image_size } image_size ;
struct TYPE_8__ {int pixelformat; } ;
struct TYPE_7__ {int width; int height; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int TCM825X_BYTES_PER_PIXEL ; 
 int TCM825X_NUM_CAPTURE_FORMATS ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_JPEG ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_SRGB ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
#define  V4L2_PIX_FMT_RGB565 129 
#define  V4L2_PIX_FMT_UYVY 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,...) ; 
 int tcm825x_find_size (struct v4l2_int_device*,int,int) ; 
 TYPE_4__* tcm825x_formats ; 
 TYPE_3__* tcm825x_sizes ; 

__attribute__((used)) static int ioctl_try_fmt_cap(struct v4l2_int_device *s,
			     struct v4l2_format *f)
{
	struct tcm825x_sensor *sensor = s->priv;
	enum image_size isize;
	int ifmt;
	struct v4l2_pix_format *pix = &f->fmt.pix;

	isize = tcm825x_find_size(s, pix->width, pix->height);
	dev_dbg(&sensor->i2c_client->dev, "isize = %d num_capture = %lu\n",
		isize, (unsigned long)TCM825X_NUM_CAPTURE_FORMATS);

	pix->width = tcm825x_sizes[isize].width;
	pix->height = tcm825x_sizes[isize].height;

	for (ifmt = 0; ifmt < TCM825X_NUM_CAPTURE_FORMATS; ifmt++)
		if (pix->pixelformat == tcm825x_formats[ifmt].pixelformat)
			break;

	if (ifmt == TCM825X_NUM_CAPTURE_FORMATS)
		ifmt = 0;	/* Default = YUV 4:2:2 */

	pix->pixelformat = tcm825x_formats[ifmt].pixelformat;
	pix->field = V4L2_FIELD_NONE;
	pix->bytesperline = pix->width * TCM825X_BYTES_PER_PIXEL;
	pix->sizeimage = pix->bytesperline * pix->height;
	pix->priv = 0;
	dev_dbg(&sensor->i2c_client->dev, "format = 0x%08x\n",
		pix->pixelformat);

	switch (pix->pixelformat) {
	case V4L2_PIX_FMT_UYVY:
	default:
		pix->colorspace = V4L2_COLORSPACE_JPEG;
		break;
	case V4L2_PIX_FMT_RGB565:
		pix->colorspace = V4L2_COLORSPACE_SRGB;
		break;
	}

	return 0;
}