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
 unsigned char COM8_AEC ; 
 int /*<<< orphan*/  REG_BRIGHT ; 
 int /*<<< orphan*/  REG_COM8 ; 
 unsigned char ov7670_abs_to_sm (int) ; 
 int /*<<< orphan*/  ov7670_read (struct v4l2_subdev*,int /*<<< orphan*/ ,unsigned char*) ; 
 int ov7670_write (struct v4l2_subdev*,int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static int ov7670_s_brightness(struct v4l2_subdev *sd, int value)
{
	unsigned char com8 = 0, v;
	int ret;

	ov7670_read(sd, REG_COM8, &com8);
	com8 &= ~COM8_AEC;
	ov7670_write(sd, REG_COM8, com8);
	v = ov7670_abs_to_sm(value);
	ret = ov7670_write(sd, REG_BRIGHT, v);
	return ret;
}