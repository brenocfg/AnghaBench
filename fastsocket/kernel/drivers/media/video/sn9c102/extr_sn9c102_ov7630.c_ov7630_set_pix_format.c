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
struct v4l2_pix_format {int /*<<< orphan*/  pixelformat; } ;
struct sn9c102_device {int dummy; } ;

/* Variables and functions */
#define  BRIDGE_SN9C101 132 
#define  BRIDGE_SN9C102 131 
#define  BRIDGE_SN9C103 130 
#define  BRIDGE_SN9C105 129 
#define  BRIDGE_SN9C120 128 
 int /*<<< orphan*/  V4L2_PIX_FMT_SBGGR8 ; 
 int sn9c102_get_bridge (struct sn9c102_device*) ; 
 int sn9c102_i2c_write (struct sn9c102_device*,int,int) ; 
 int sn9c102_write_reg (struct sn9c102_device*,int,int) ; 

__attribute__((used)) static int ov7630_set_pix_format(struct sn9c102_device* cam,
				 const struct v4l2_pix_format* pix)
{
	int err = 0;

	switch (sn9c102_get_bridge(cam)) {
	case BRIDGE_SN9C101:
	case BRIDGE_SN9C102:
	case BRIDGE_SN9C103:
		if (pix->pixelformat == V4L2_PIX_FMT_SBGGR8)
			err += sn9c102_write_reg(cam, 0x50, 0x19);
		else
			err += sn9c102_write_reg(cam, 0x20, 0x19);
		break;
	case BRIDGE_SN9C105:
	case BRIDGE_SN9C120:
		if (pix->pixelformat == V4L2_PIX_FMT_SBGGR8) {
			err += sn9c102_write_reg(cam, 0xe5, 0x17);
			err += sn9c102_i2c_write(cam, 0x11, 0x04);
		} else {
			err += sn9c102_write_reg(cam, 0xe2, 0x17);
			err += sn9c102_i2c_write(cam, 0x11, 0x02);
		}
		break;
	default:
		break;
	}

	return err;
}