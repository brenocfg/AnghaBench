#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct v4l2_subdev {int dummy; } ;
struct soc_camera_platform_info {int (* set_capture ) (struct soc_camera_platform_info*,int) ;} ;

/* Variables and functions */
 int stub1 (struct soc_camera_platform_info*,int) ; 
 struct soc_camera_platform_info* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int soc_camera_platform_s_stream(struct v4l2_subdev *sd, int enable)
{
	struct soc_camera_platform_info *p = v4l2_get_subdevdata(sd);
	return p->set_capture(p, enable);
}