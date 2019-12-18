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
typedef  int v4l2_std_id ;
typedef  scalar_t__ u32 ;
struct tw9910_scale_ctrl {scalar_t__ height; scalar_t__ width; } ;
struct soc_camera_device {TYPE_1__* vdev; } ;
typedef  scalar_t__ __u32 ;
struct TYPE_2__ {int current_norm; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct tw9910_scale_ctrl*) ; 
 int V4L2_STD_NTSC ; 
 int V4L2_STD_PAL ; 
 scalar_t__ abs (scalar_t__) ; 
 struct tw9910_scale_ctrl* tw9910_ntsc_scales ; 
 struct tw9910_scale_ctrl* tw9910_pal_scales ; 

__attribute__((used)) static const struct tw9910_scale_ctrl*
tw9910_select_norm(struct soc_camera_device *icd, u32 width, u32 height)
{
	const struct tw9910_scale_ctrl *scale;
	const struct tw9910_scale_ctrl *ret = NULL;
	v4l2_std_id norm = icd->vdev->current_norm;
	__u32 diff = 0xffffffff, tmp;
	int size, i;

	if (norm & V4L2_STD_NTSC) {
		scale = tw9910_ntsc_scales;
		size = ARRAY_SIZE(tw9910_ntsc_scales);
	} else if (norm & V4L2_STD_PAL) {
		scale = tw9910_pal_scales;
		size = ARRAY_SIZE(tw9910_pal_scales);
	} else {
		return NULL;
	}

	for (i = 0; i < size; i++) {
		tmp = abs(width - scale[i].width) +
			abs(height - scale[i].height);
		if (tmp < diff) {
			diff = tmp;
			ret = scale + i;
		}
	}

	return ret;
}