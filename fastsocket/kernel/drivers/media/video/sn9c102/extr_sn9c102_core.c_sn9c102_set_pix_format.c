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
struct sn9c102_device {int bridge; int* reg; } ;

/* Variables and functions */
#define  BRIDGE_SN9C101 132 
#define  BRIDGE_SN9C102 131 
#define  BRIDGE_SN9C103 130 
#define  BRIDGE_SN9C105 129 
#define  BRIDGE_SN9C120 128 
 int EIO ; 
 scalar_t__ V4L2_PIX_FMT_JPEG ; 
 scalar_t__ V4L2_PIX_FMT_SN9C10X ; 
 int sn9c102_write_reg (struct sn9c102_device*,int,int) ; 

__attribute__((used)) static int
sn9c102_set_pix_format(struct sn9c102_device* cam, struct v4l2_pix_format* pix)
{
	int err = 0;

	if (pix->pixelformat == V4L2_PIX_FMT_SN9C10X ||
	    pix->pixelformat == V4L2_PIX_FMT_JPEG) {
		switch (cam->bridge) {
		case BRIDGE_SN9C101:
		case BRIDGE_SN9C102:
		case BRIDGE_SN9C103:
			err += sn9c102_write_reg(cam, cam->reg[0x18] | 0x80,
						 0x18);
			break;
		case BRIDGE_SN9C105:
		case BRIDGE_SN9C120:
			err += sn9c102_write_reg(cam, cam->reg[0x18] & 0x7f,
						 0x18);
			break;
		}
	} else {
		switch (cam->bridge) {
		case BRIDGE_SN9C101:
		case BRIDGE_SN9C102:
		case BRIDGE_SN9C103:
			err += sn9c102_write_reg(cam, cam->reg[0x18] & 0x7f,
						 0x18);
			break;
		case BRIDGE_SN9C105:
		case BRIDGE_SN9C120:
			err += sn9c102_write_reg(cam, cam->reg[0x18] | 0x80,
						 0x18);
			break;
		}
	}

	return err ? -EIO : 0;
}