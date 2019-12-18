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
typedef  int /*<<< orphan*/  __s32 ;

/* Variables and functions */
 int /*<<< orphan*/  REG_BRIGHT ; 
 int ov7670_read (struct v4l2_subdev*,int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  ov7670_sm_to_abs (unsigned char) ; 

__attribute__((used)) static int ov7670_g_brightness(struct v4l2_subdev *sd, __s32 *value)
{
	unsigned char v = 0;
	int ret = ov7670_read(sd, REG_BRIGHT, &v);

	*value = ov7670_sm_to_abs(v);
	return ret;
}