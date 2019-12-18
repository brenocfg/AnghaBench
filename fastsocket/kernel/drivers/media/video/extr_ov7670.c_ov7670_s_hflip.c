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

/* Variables and functions */
 unsigned char MVFP_MIRROR ; 
 int /*<<< orphan*/  REG_MVFP ; 
 int /*<<< orphan*/  msleep (int) ; 
 int ov7670_read (struct v4l2_subdev*,int /*<<< orphan*/ ,unsigned char*) ; 
 scalar_t__ ov7670_write (struct v4l2_subdev*,int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static int ov7670_s_hflip(struct v4l2_subdev *sd, int value)
{
	unsigned char v = 0;
	int ret;

	ret = ov7670_read(sd, REG_MVFP, &v);
	if (value)
		v |= MVFP_MIRROR;
	else
		v &= ~MVFP_MIRROR;
	msleep(10);  /* FIXME */
	ret += ov7670_write(sd, REG_MVFP, v);
	return ret;
}