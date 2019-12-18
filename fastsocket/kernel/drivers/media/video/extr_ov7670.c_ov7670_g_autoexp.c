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
typedef  enum v4l2_exposure_auto_type { ____Placeholder_v4l2_exposure_auto_type } v4l2_exposure_auto_type ;
typedef  int /*<<< orphan*/  __s32 ;

/* Variables and functions */
 unsigned char COM8_AEC ; 
 int /*<<< orphan*/  REG_COM8 ; 
 int V4L2_EXPOSURE_AUTO ; 
 int V4L2_EXPOSURE_MANUAL ; 
 int ov7670_read (struct v4l2_subdev*,int /*<<< orphan*/ ,unsigned char*) ; 

__attribute__((used)) static int ov7670_g_autoexp(struct v4l2_subdev *sd, __s32 *value)
{
	int ret;
	unsigned char com8;
	enum v4l2_exposure_auto_type *atype = (enum v4l2_exposure_auto_type *) value;

	ret = ov7670_read(sd, REG_COM8, &com8);
	if (com8 & COM8_AEC)
		*atype = V4L2_EXPOSURE_AUTO;
	else
		*atype = V4L2_EXPOSURE_MANUAL;
	return ret;
}