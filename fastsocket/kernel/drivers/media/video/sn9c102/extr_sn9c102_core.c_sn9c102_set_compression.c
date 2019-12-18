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
struct v4l2_jpegcompression {int quality; } ;
struct sn9c102_device {int bridge; int* reg; } ;

/* Variables and functions */
#define  BRIDGE_SN9C101 132 
#define  BRIDGE_SN9C102 131 
#define  BRIDGE_SN9C103 130 
#define  BRIDGE_SN9C105 129 
#define  BRIDGE_SN9C120 128 
 int EIO ; 
 int* SN9C102_UV_QTABLE1 ; 
 int* SN9C102_Y_QTABLE1 ; 
 int sn9c102_write_reg (struct sn9c102_device*,int,int) ; 

__attribute__((used)) static int
sn9c102_set_compression(struct sn9c102_device* cam,
			struct v4l2_jpegcompression* compression)
{
	int i, err = 0;

	switch (cam->bridge) {
	case BRIDGE_SN9C101:
	case BRIDGE_SN9C102:
	case BRIDGE_SN9C103:
		if (compression->quality == 0)
			err += sn9c102_write_reg(cam, cam->reg[0x17] | 0x01,
						 0x17);
		else if (compression->quality == 1)
			err += sn9c102_write_reg(cam, cam->reg[0x17] & 0xfe,
						 0x17);
		break;
	case BRIDGE_SN9C105:
	case BRIDGE_SN9C120:
		if (compression->quality == 0) {
			for (i = 0; i <= 63; i++) {
				err += sn9c102_write_reg(cam,
							 SN9C102_Y_QTABLE1[i],
							 0x100 + i);
				err += sn9c102_write_reg(cam,
							 SN9C102_UV_QTABLE1[i],
							 0x140 + i);
			}
			err += sn9c102_write_reg(cam, cam->reg[0x18] & 0xbf,
						 0x18);
		} else if (compression->quality == 1) {
			for (i = 0; i <= 63; i++) {
				err += sn9c102_write_reg(cam,
							 SN9C102_Y_QTABLE1[i],
							 0x100 + i);
				err += sn9c102_write_reg(cam,
							 SN9C102_UV_QTABLE1[i],
							 0x140 + i);
			}
			err += sn9c102_write_reg(cam, cam->reg[0x18] | 0x40,
						 0x18);
		}
		break;
	}

	return err ? -EIO : 0;
}