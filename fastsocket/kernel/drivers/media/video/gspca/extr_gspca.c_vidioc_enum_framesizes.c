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
struct TYPE_4__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct v4l2_frmsizeenum {scalar_t__ pixel_format; scalar_t__ index; TYPE_1__ discrete; int /*<<< orphan*/  type; } ;
struct TYPE_6__ {int nmodes; TYPE_2__* cam_mode; } ;
struct gspca_dev {TYPE_3__ cam; } ;
struct file {int dummy; } ;
typedef  scalar_t__ __u32 ;
struct TYPE_5__ {scalar_t__ pixelformat; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_FRMSIZE_TYPE_DISCRETE ; 

__attribute__((used)) static int vidioc_enum_framesizes(struct file *file, void *priv,
				  struct v4l2_frmsizeenum *fsize)
{
	struct gspca_dev *gspca_dev = priv;
	int i;
	__u32 index = 0;

	for (i = 0; i < gspca_dev->cam.nmodes; i++) {
		if (fsize->pixel_format !=
				gspca_dev->cam.cam_mode[i].pixelformat)
			continue;

		if (fsize->index == index) {
			fsize->type = V4L2_FRMSIZE_TYPE_DISCRETE;
			fsize->discrete.width =
				gspca_dev->cam.cam_mode[i].width;
			fsize->discrete.height =
				gspca_dev->cam.cam_mode[i].height;
			return 0;
		}
		index++;
	}

	return -EINVAL;
}