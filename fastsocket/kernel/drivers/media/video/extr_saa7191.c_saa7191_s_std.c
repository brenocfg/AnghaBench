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
typedef  int v4l2_std_id ;
typedef  int u8 ;
struct v4l2_subdev {int dummy; } ;
struct saa7191 {int norm; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int SAA7191_CHCV_NTSC ; 
 int SAA7191_CHCV_PAL ; 
 int SAA7191_CTL3_AUFD ; 
 int SAA7191_CTL3_FSEL ; 
 int /*<<< orphan*/  SAA7191_REG_CHCV ; 
 int /*<<< orphan*/  SAA7191_REG_CTL3 ; 
 int /*<<< orphan*/  SAA7191_REG_STDC ; 
 int SAA7191_STDC_SECS ; 
 int V4L2_STD_NTSC ; 
 int V4L2_STD_PAL ; 
 int V4L2_STD_SECAM ; 
 int /*<<< orphan*/  dprintk (char*,int,...) ; 
 int saa7191_read_reg (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int saa7191_write_reg (struct v4l2_subdev*,int /*<<< orphan*/ ,int) ; 
 struct saa7191* to_saa7191 (struct v4l2_subdev*) ; 

__attribute__((used)) static int saa7191_s_std(struct v4l2_subdev *sd, v4l2_std_id norm)
{
	struct saa7191 *decoder = to_saa7191(sd);
	u8 stdc = saa7191_read_reg(sd, SAA7191_REG_STDC);
	u8 ctl3 = saa7191_read_reg(sd, SAA7191_REG_CTL3);
	u8 chcv = saa7191_read_reg(sd, SAA7191_REG_CHCV);
	int err;

	if (norm & V4L2_STD_PAL) {
		stdc &= ~SAA7191_STDC_SECS;
		ctl3 &= ~(SAA7191_CTL3_AUFD | SAA7191_CTL3_FSEL);
		chcv = SAA7191_CHCV_PAL;
	} else if (norm & V4L2_STD_NTSC) {
		stdc &= ~SAA7191_STDC_SECS;
		ctl3 &= ~SAA7191_CTL3_AUFD;
		ctl3 |= SAA7191_CTL3_FSEL;
		chcv = SAA7191_CHCV_NTSC;
	} else if (norm & V4L2_STD_SECAM) {
		stdc |= SAA7191_STDC_SECS;
		ctl3 &= ~(SAA7191_CTL3_AUFD | SAA7191_CTL3_FSEL);
		chcv = SAA7191_CHCV_PAL;
	} else {
		return -EINVAL;
	}

	err = saa7191_write_reg(sd, SAA7191_REG_CTL3, ctl3);
	if (err)
		return -EIO;
	err = saa7191_write_reg(sd, SAA7191_REG_STDC, stdc);
	if (err)
		return -EIO;
	err = saa7191_write_reg(sd, SAA7191_REG_CHCV, chcv);
	if (err)
		return -EIO;

	decoder->norm = norm;

	dprintk("ctl3: %02x stdc: %02x chcv: %02x\n", ctl3,
		stdc, chcv);
	dprintk("norm: %llx\n", norm);

	return 0;
}