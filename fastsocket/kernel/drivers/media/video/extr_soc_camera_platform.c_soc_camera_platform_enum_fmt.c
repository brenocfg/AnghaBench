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
struct TYPE_2__ {int code; } ;
struct soc_camera_platform_info {TYPE_1__ format; } ;
typedef  enum v4l2_mbus_pixelcode { ____Placeholder_v4l2_mbus_pixelcode } v4l2_mbus_pixelcode ;

/* Variables and functions */
 int EINVAL ; 
 struct soc_camera_platform_info* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int soc_camera_platform_enum_fmt(struct v4l2_subdev *sd, unsigned int index,
					enum v4l2_mbus_pixelcode *code)
{
	struct soc_camera_platform_info *p = v4l2_get_subdevdata(sd);

	if (index)
		return -EINVAL;

	*code = p->format.code;
	return 0;
}