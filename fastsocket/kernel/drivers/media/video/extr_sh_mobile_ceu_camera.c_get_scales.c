#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct v4l2_subdev {int dummy; } ;
struct v4l2_crop {int /*<<< orphan*/  c; int /*<<< orphan*/  type; } ;
struct soc_camera_device {int /*<<< orphan*/  user_height; int /*<<< orphan*/  user_width; struct sh_mobile_ceu_cam* host_priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct sh_mobile_ceu_cam {TYPE_1__ ceu_rect; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 unsigned int calc_generic_scale (unsigned int,int /*<<< orphan*/ ) ; 
 int client_g_rect (struct v4l2_subdev*,int /*<<< orphan*/ *) ; 
 int get_camera_scales (struct v4l2_subdev*,int /*<<< orphan*/ *,unsigned int*,unsigned int*) ; 
 unsigned int scale_up (int /*<<< orphan*/ ,unsigned int) ; 
 struct v4l2_subdev* soc_camera_to_subdev (struct soc_camera_device*) ; 

__attribute__((used)) static int get_scales(struct soc_camera_device *icd,
		      unsigned int *scale_h, unsigned int *scale_v)
{
	struct sh_mobile_ceu_cam *cam = icd->host_priv;
	struct v4l2_subdev *sd = soc_camera_to_subdev(icd);
	struct v4l2_crop cam_crop;
	unsigned int width_in, height_in;
	int ret;

	cam_crop.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

	ret = client_g_rect(sd, &cam_crop.c);
	if (ret < 0)
		return ret;

	ret = get_camera_scales(sd, &cam_crop.c, scale_h, scale_v);
	if (ret < 0)
		return ret;

	width_in = scale_up(cam->ceu_rect.width, *scale_h);
	height_in = scale_up(cam->ceu_rect.height, *scale_v);

	*scale_h = calc_generic_scale(width_in, icd->user_width);
	*scale_v = calc_generic_scale(height_in, icd->user_height);

	return 0;
}