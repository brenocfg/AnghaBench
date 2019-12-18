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
 int /*<<< orphan*/  REG_AECH ; 
 int /*<<< orphan*/  REG_AECHH ; 
 int /*<<< orphan*/  REG_COM1 ; 
 int /*<<< orphan*/  REG_COM8 ; 
 int ov7670_read (struct v4l2_subdev*,int /*<<< orphan*/ ,unsigned char*) ; 
 int ov7670_write (struct v4l2_subdev*,int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static int ov7670_s_exp(struct v4l2_subdev *sd, int value)
{
	int ret;
	unsigned char com1, com8, aech, aechh;

	ret = ov7670_read(sd, REG_COM1, &com1) +
		ov7670_read(sd, REG_COM8, &com8);
		ov7670_read(sd, REG_AECHH, &aechh);
	if (ret)
		return ret;

	com1 = (com1 & 0xfc) | (value & 0x03);
	aech = (value >> 2) & 0xff;
	aechh = (aechh & 0xc0) | ((value >> 10) & 0x3f);
	ret = ov7670_write(sd, REG_COM1, com1) +
		ov7670_write(sd, REG_AECH, aech) +
		ov7670_write(sd, REG_AECHH, aechh);
	/* Have to turn off AEC as well */
	if (ret == 0)
		ret = ov7670_write(sd, REG_COM8, com8 & ~COM8_AEC);
	return ret;
}