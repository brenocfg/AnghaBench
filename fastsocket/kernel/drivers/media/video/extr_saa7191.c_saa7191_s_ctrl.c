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
typedef  int u8 ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_control {int id; int value; } ;
typedef  int s32 ;

/* Variables and functions */
 int EINVAL ; 
#define  SAA7191_CONTROL_BANDPASS 136 
#define  SAA7191_CONTROL_BANDPASS_WEIGHT 135 
#define  SAA7191_CONTROL_CHROMA_GAIN 134 
#define  SAA7191_CONTROL_CORING 133 
#define  SAA7191_CONTROL_FORCE_COLOUR 132 
#define  SAA7191_CONTROL_LUMA_DELAY 131 
#define  SAA7191_CONTROL_VNR 130 
#define  SAA7191_CONTROL_VTRC 129 
 int SAA7191_CTL3_YDEL_MASK ; 
 int SAA7191_CTL3_YDEL_SHIFT ; 
 int SAA7191_CTL4_VNOI_MASK ; 
 int SAA7191_CTL4_VNOI_SHIFT ; 
 int SAA7191_GAIN_COLO ; 
 int SAA7191_GAIN_LFIS_MASK ; 
 int SAA7191_GAIN_LFIS_SHIFT ; 
 int SAA7191_LUMA_APER_MASK ; 
 int SAA7191_LUMA_APER_SHIFT ; 
 int SAA7191_LUMA_BPSS_MASK ; 
 int SAA7191_LUMA_BPSS_SHIFT ; 
 int SAA7191_LUMA_CORI_MASK ; 
 int SAA7191_LUMA_CORI_SHIFT ; 
 int /*<<< orphan*/  SAA7191_REG_CTL3 ; 
 int /*<<< orphan*/  SAA7191_REG_CTL4 ; 
 int /*<<< orphan*/  SAA7191_REG_GAIN ; 
 int /*<<< orphan*/  SAA7191_REG_HUEC ; 
 int /*<<< orphan*/  SAA7191_REG_LUMA ; 
 int /*<<< orphan*/  SAA7191_REG_STDC ; 
 int SAA7191_STDC_VTRC ; 
#define  V4L2_CID_HUE 128 
 int saa7191_read_reg (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int saa7191_write_reg (struct v4l2_subdev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int saa7191_s_ctrl(struct v4l2_subdev *sd, struct v4l2_control *ctrl)
{
	u8 reg;
	int ret = 0;

	switch (ctrl->id) {
	case SAA7191_CONTROL_BANDPASS:
	case SAA7191_CONTROL_BANDPASS_WEIGHT:
	case SAA7191_CONTROL_CORING:
		reg = saa7191_read_reg(sd, SAA7191_REG_LUMA);
		switch (ctrl->id) {
		case SAA7191_CONTROL_BANDPASS:
			reg &= ~SAA7191_LUMA_BPSS_MASK;
			reg |= (ctrl->value << SAA7191_LUMA_BPSS_SHIFT)
				& SAA7191_LUMA_BPSS_MASK;
			break;
		case SAA7191_CONTROL_BANDPASS_WEIGHT:
			reg &= ~SAA7191_LUMA_APER_MASK;
			reg |= (ctrl->value << SAA7191_LUMA_APER_SHIFT)
				& SAA7191_LUMA_APER_MASK;
			break;
		case SAA7191_CONTROL_CORING:
			reg &= ~SAA7191_LUMA_CORI_MASK;
			reg |= (ctrl->value << SAA7191_LUMA_CORI_SHIFT)
				& SAA7191_LUMA_CORI_MASK;
			break;
		}
		ret = saa7191_write_reg(sd, SAA7191_REG_LUMA, reg);
		break;
	case SAA7191_CONTROL_FORCE_COLOUR:
	case SAA7191_CONTROL_CHROMA_GAIN:
		reg = saa7191_read_reg(sd, SAA7191_REG_GAIN);
		if (ctrl->id == SAA7191_CONTROL_FORCE_COLOUR) {
			if (ctrl->value)
				reg |= SAA7191_GAIN_COLO;
			else
				reg &= ~SAA7191_GAIN_COLO;
		} else {
			reg &= ~SAA7191_GAIN_LFIS_MASK;
			reg |= (ctrl->value << SAA7191_GAIN_LFIS_SHIFT)
				& SAA7191_GAIN_LFIS_MASK;
		}
		ret = saa7191_write_reg(sd, SAA7191_REG_GAIN, reg);
		break;
	case V4L2_CID_HUE:
		reg = ctrl->value & 0xff;
		if (reg < 0x80)
			reg += 0x80;
		else
			reg -= 0x80;
		ret = saa7191_write_reg(sd, SAA7191_REG_HUEC, reg);
		break;
	case SAA7191_CONTROL_VTRC:
		reg = saa7191_read_reg(sd, SAA7191_REG_STDC);
		if (ctrl->value)
			reg |= SAA7191_STDC_VTRC;
		else
			reg &= ~SAA7191_STDC_VTRC;
		ret = saa7191_write_reg(sd, SAA7191_REG_STDC, reg);
		break;
	case SAA7191_CONTROL_LUMA_DELAY: {
		s32 value = ctrl->value;
		if (value < 0)
			value += 8;
		reg = saa7191_read_reg(sd, SAA7191_REG_CTL3);
		reg &= ~SAA7191_CTL3_YDEL_MASK;
		reg |= (value << SAA7191_CTL3_YDEL_SHIFT)
			& SAA7191_CTL3_YDEL_MASK;
		ret = saa7191_write_reg(sd, SAA7191_REG_CTL3, reg);
		break;
	}
	case SAA7191_CONTROL_VNR:
		reg = saa7191_read_reg(sd, SAA7191_REG_CTL4);
		reg &= ~SAA7191_CTL4_VNOI_MASK;
		reg |= (ctrl->value << SAA7191_CTL4_VNOI_SHIFT)
			& SAA7191_CTL4_VNOI_MASK;
		ret = saa7191_write_reg(sd, SAA7191_REG_CTL4, reg);
		break;
	default:
		ret = -EINVAL;
	}

	return ret;
}