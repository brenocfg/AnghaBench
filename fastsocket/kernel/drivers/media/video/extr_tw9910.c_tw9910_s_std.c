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
typedef  int v4l2_std_id ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int V4L2_STD_NTSC ; 
 int V4L2_STD_PAL ; 

__attribute__((used)) static int tw9910_s_std(struct v4l2_subdev *sd, v4l2_std_id norm)
{
	int ret = -EINVAL;

	if (norm & (V4L2_STD_NTSC | V4L2_STD_PAL))
		ret = 0;

	return ret;
}