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
typedef  unsigned char __s32 ;

/* Variables and functions */
 int /*<<< orphan*/  REG_AECH ; 
 int /*<<< orphan*/  REG_AECHH ; 
 int /*<<< orphan*/  REG_COM1 ; 
 int ov7670_read (struct v4l2_subdev*,int /*<<< orphan*/ ,unsigned char*) ; 

__attribute__((used)) static int ov7670_g_exp(struct v4l2_subdev *sd, __s32 *value)
{
	int ret;
	unsigned char com1, aech, aechh;

	ret = ov7670_read(sd, REG_COM1, &com1) +
		ov7670_read(sd, REG_AECH, &aech) +
		ov7670_read(sd, REG_AECHH, &aechh);
	*value = ((aechh & 0x3f) << 10) | (aech << 2) | (com1 & 0x03);
	return ret;
}