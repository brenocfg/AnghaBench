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
struct v4l2_pix_format {scalar_t__ pixelformat; } ;
struct sn9c102_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ V4L2_PIX_FMT_JPEG ; 
 scalar_t__ sn9c102_i2c_write (struct sn9c102_device*,int,int) ; 
 int sn9c102_pread_reg (struct sn9c102_device*,int) ; 
 scalar_t__ sn9c102_write_reg (struct sn9c102_device*,int,int) ; 

__attribute__((used)) static int ov7660_set_pix_format(struct sn9c102_device* cam,
				 const struct v4l2_pix_format* pix)
{
	int r0, err = 0;

	r0 = sn9c102_pread_reg(cam, 0x01);

	if (pix->pixelformat == V4L2_PIX_FMT_JPEG) {
		err += sn9c102_write_reg(cam, r0 | 0x40, 0x01);
		err += sn9c102_write_reg(cam, 0xa2, 0x17);
		err += sn9c102_i2c_write(cam, 0x11, 0x00);
	} else {
		err += sn9c102_write_reg(cam, r0 | 0x40, 0x01);
		err += sn9c102_write_reg(cam, 0xa2, 0x17);
		err += sn9c102_i2c_write(cam, 0x11, 0x0d);
	}

	return err;
}