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
typedef  int u16 ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_rect {void* height; void* width; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct v4l2_pix_format {int pixelformat; int field; void* height; void* width; } ;
struct TYPE_4__ {struct v4l2_pix_format pix; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct v4l2_crop {int /*<<< orphan*/  type; struct v4l2_rect c; } ;
struct soc_camera_host {struct sh_mobile_ceu_dev* priv; } ;
struct soc_camera_format_xlate {TYPE_3__* cam_fmt; int /*<<< orphan*/  host_fmt; int /*<<< orphan*/  buswidth; } ;
struct TYPE_5__ {struct device* parent; } ;
struct soc_camera_device {int /*<<< orphan*/  current_fmt; int /*<<< orphan*/  buswidth; TYPE_2__ dev; struct sh_mobile_ceu_cam* host_priv; } ;
struct sh_mobile_ceu_dev {int cflcr; int is_interlaced; int image_mode; } ;
struct sh_mobile_ceu_cam {struct v4l2_rect ceu_rect; TYPE_3__* camera_fmt; } ;
struct device {int dummy; } ;
typedef  int __u32 ;
struct TYPE_6__ {int fourcc; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
#define  V4L2_FIELD_ANY 134 
#define  V4L2_FIELD_INTERLACED 133 
#define  V4L2_FIELD_NONE 132 
#define  V4L2_PIX_FMT_NV12 131 
#define  V4L2_PIX_FMT_NV16 130 
#define  V4L2_PIX_FMT_NV21 129 
#define  V4L2_PIX_FMT_NV61 128 
 int calc_generic_scale (void*,void*) ; 
 int calc_scale (void*,void**) ; 
 int client_g_rect (struct v4l2_subdev*,struct v4l2_rect*) ; 
 int client_scale (struct soc_camera_device*,struct v4l2_rect*,struct v4l2_rect*,struct v4l2_rect*,struct v4l2_format*,int) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,void*,void*,void*,void*) ; 
 int /*<<< orphan*/  dev_geo (struct device*,char*,unsigned int,...) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int) ; 
 int get_camera_scales (struct v4l2_subdev*,struct v4l2_rect*,unsigned int*,unsigned int*) ; 
 int get_camera_subwin (struct soc_camera_device*,struct v4l2_rect*,unsigned int,unsigned int) ; 
 void* scale_down (void*,int) ; 
 struct v4l2_subdev* soc_camera_to_subdev (struct soc_camera_device*) ; 
 struct soc_camera_format_xlate* soc_camera_xlate_by_fourcc (struct soc_camera_device*,int) ; 
 struct soc_camera_host* to_soc_camera_host (struct device*) ; 

__attribute__((used)) static int sh_mobile_ceu_set_fmt(struct soc_camera_device *icd,
				 struct v4l2_format *f)
{
	struct soc_camera_host *ici = to_soc_camera_host(icd->dev.parent);
	struct sh_mobile_ceu_dev *pcdev = ici->priv;
	struct sh_mobile_ceu_cam *cam = icd->host_priv;
	struct v4l2_pix_format *pix = &f->fmt.pix;
	struct v4l2_format cam_f = *f;
	struct v4l2_pix_format *cam_pix = &cam_f.fmt.pix;
	struct v4l2_subdev *sd = soc_camera_to_subdev(icd);
	struct device *dev = icd->dev.parent;
	__u32 pixfmt = pix->pixelformat;
	const struct soc_camera_format_xlate *xlate;
	struct v4l2_crop cam_crop;
	struct v4l2_rect *cam_rect = &cam_crop.c, cam_subrect, ceu_rect;
	unsigned int scale_cam_h, scale_cam_v;
	u16 scale_v, scale_h;
	int ret;
	bool is_interlaced, image_mode;

	switch (pix->field) {
	case V4L2_FIELD_INTERLACED:
		is_interlaced = true;
		break;
	case V4L2_FIELD_ANY:
	default:
		pix->field = V4L2_FIELD_NONE;
		/* fall-through */
	case V4L2_FIELD_NONE:
		is_interlaced = false;
		break;
	}

	xlate = soc_camera_xlate_by_fourcc(icd, pixfmt);
	if (!xlate) {
		dev_warn(dev, "Format %x not found\n", pixfmt);
		return -EINVAL;
	}

	/* 1. Calculate current camera scales. */
	cam_crop.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

	ret = client_g_rect(sd, cam_rect);
	if (ret < 0)
		return ret;

	ret = get_camera_scales(sd, cam_rect, &scale_cam_h, &scale_cam_v);
	if (ret < 0)
		return ret;

	dev_geo(dev, "1: camera scales %u:%u\n", scale_cam_h, scale_cam_v);

	/*
	 * 2. Calculate "effective" input crop (sensor subwindow) - CEU crop
	 *    scaled back at current camera scales onto input window.
	 */
	ret = get_camera_subwin(icd, &cam_subrect, scale_cam_h, scale_cam_v);
	if (ret < 0)
		return ret;

	dev_geo(dev, "2: subwin %ux%u@%u:%u\n",
		cam_subrect.width, cam_subrect.height,
		cam_subrect.left, cam_subrect.top);

	/*
	 * 3. Calculate new combined scales from "effective" input window to
	 *    requested user window.
	 */
	scale_h = calc_generic_scale(cam_subrect.width, pix->width);
	scale_v = calc_generic_scale(cam_subrect.height, pix->height);

	dev_geo(dev, "3: scales %u:%u\n", scale_h, scale_v);

	/*
	 * 4. Calculate camera output window by applying combined scales to real
	 *    input window.
	 */
	cam_pix->width = scale_down(cam_rect->width, scale_h);
	cam_pix->height = scale_down(cam_rect->height, scale_v);
	cam_pix->pixelformat = xlate->cam_fmt->fourcc;

	switch (pixfmt) {
	case V4L2_PIX_FMT_NV12:
	case V4L2_PIX_FMT_NV21:
	case V4L2_PIX_FMT_NV16:
	case V4L2_PIX_FMT_NV61:
		image_mode = true;
		break;
	default:
		image_mode = false;
	}

	dev_geo(dev, "4: camera output %ux%u\n",
		cam_pix->width, cam_pix->height);

	/* 5. - 9. */
	ret = client_scale(icd, cam_rect, &cam_subrect, &ceu_rect, &cam_f,
			   image_mode && !is_interlaced);

	dev_geo(dev, "5-9: client scale %d\n", ret);

	/* Done with the camera. Now see if we can improve the result */

	dev_dbg(dev, "Camera %d fmt %ux%u, requested %ux%u\n",
		ret, cam_pix->width, cam_pix->height, pix->width, pix->height);
	if (ret < 0)
		return ret;

	/* 10. Use CEU scaling to scale to the requested user window. */

	/* We cannot scale up */
	if (pix->width > cam_pix->width)
		pix->width = cam_pix->width;
	if (pix->width > ceu_rect.width)
		pix->width = ceu_rect.width;

	if (pix->height > cam_pix->height)
		pix->height = cam_pix->height;
	if (pix->height > ceu_rect.height)
		pix->height = ceu_rect.height;

	/* Let's rock: scale pix->{width x height} down to width x height */
	scale_h = calc_scale(ceu_rect.width, &pix->width);
	scale_v = calc_scale(ceu_rect.height, &pix->height);

	dev_geo(dev, "10: W: %u : 0x%x = %u, H: %u : 0x%x = %u\n",
		ceu_rect.width, scale_h, pix->width,
		ceu_rect.height, scale_v, pix->height);

	pcdev->cflcr = scale_h | (scale_v << 16);

	icd->buswidth = xlate->buswidth;
	icd->current_fmt = xlate->host_fmt;
	cam->camera_fmt = xlate->cam_fmt;
	cam->ceu_rect = ceu_rect;

	pcdev->is_interlaced = is_interlaced;
	pcdev->image_mode = image_mode;

	return 0;
}