#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct v4l2_subdev {int dummy; } ;
struct v4l2_rect {int width; int left; int height; int top; } ;
struct v4l2_pix_format {int width; int height; } ;
struct TYPE_4__ {struct v4l2_pix_format pix; } ;
struct v4l2_format {int /*<<< orphan*/  type; TYPE_2__ fmt; } ;
struct TYPE_3__ {struct device* parent; } ;
struct soc_camera_device {TYPE_1__ dev; struct sh_mobile_ceu_cam* host_priv; } ;
struct sh_mobile_ceu_cam {struct v4l2_rect ceu_rect; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  dev_geo (struct device*,char*,int,int,...) ; 
 int /*<<< orphan*/  g_fmt ; 
 void* scale_up (int,unsigned int) ; 
 struct v4l2_subdev* soc_camera_to_subdev (struct soc_camera_device*) ; 
 int v4l2_subdev_call (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_format*) ; 
 int /*<<< orphan*/  video ; 

__attribute__((used)) static int get_camera_subwin(struct soc_camera_device *icd,
			     struct v4l2_rect *cam_subrect,
			     unsigned int cam_hscale, unsigned int cam_vscale)
{
	struct sh_mobile_ceu_cam *cam = icd->host_priv;
	struct v4l2_rect *ceu_rect = &cam->ceu_rect;

	if (!ceu_rect->width) {
		struct v4l2_subdev *sd = soc_camera_to_subdev(icd);
		struct device *dev = icd->dev.parent;
		struct v4l2_format f;
		struct v4l2_pix_format *pix = &f.fmt.pix;
		int ret;
		/* First time */

		f.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

		ret = v4l2_subdev_call(sd, video, g_fmt, &f);
		if (ret < 0)
			return ret;

		dev_geo(dev, "camera fmt %ux%u\n", pix->width, pix->height);

		if (pix->width > 2560) {
			ceu_rect->width	 = 2560;
			ceu_rect->left	 = (pix->width - 2560) / 2;
		} else {
			ceu_rect->width	 = pix->width;
			ceu_rect->left	 = 0;
		}

		if (pix->height > 1920) {
			ceu_rect->height = 1920;
			ceu_rect->top	 = (pix->height - 1920) / 2;
		} else {
			ceu_rect->height = pix->height;
			ceu_rect->top	 = 0;
		}

		dev_geo(dev, "initialised CEU rect %ux%u@%u:%u\n",
			ceu_rect->width, ceu_rect->height,
			ceu_rect->left, ceu_rect->top);
	}

	cam_subrect->width	= scale_up(ceu_rect->width, cam_hscale);
	cam_subrect->left	= scale_up(ceu_rect->left, cam_hscale);
	cam_subrect->height	= scale_up(ceu_rect->height, cam_vscale);
	cam_subrect->top	= scale_up(ceu_rect->top, cam_vscale);

	return 0;
}