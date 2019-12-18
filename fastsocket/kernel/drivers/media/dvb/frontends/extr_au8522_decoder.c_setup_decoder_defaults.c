#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct au8522_state {int brightness; int contrast; int saturation; int hue; } ;
struct TYPE_2__ {int* reg_val; int /*<<< orphan*/  reg_name; } ;

/* Variables and functions */
 int AU8522_INPUT_CONTROL_REG081H_SVIDEO_CH13 ; 
 int AU8522_INPUT_CONTROL_REG081H_SVIDEO_CH24 ; 
 int /*<<< orphan*/  AU8522_REG016H ; 
 int AU8522_REG016H_CVBS ; 
 int /*<<< orphan*/  AU8522_REG071H ; 
 int AU8522_REG071H_CVBS ; 
 int /*<<< orphan*/  AU8522_REG072H ; 
 int AU8522_REG072H_CVBS ; 
 int /*<<< orphan*/  AU8522_REG074H ; 
 int AU8522_REG074H_CVBS ; 
 int /*<<< orphan*/  AU8522_REG075H ; 
 int AU8522_REG075H_CVBS ; 
 int /*<<< orphan*/  AU8522_REG42EH ; 
 int /*<<< orphan*/  AU8522_REG42FH ; 
 int /*<<< orphan*/  AU8522_REG430H ; 
 int /*<<< orphan*/  AU8522_REG431H ; 
 int /*<<< orphan*/  AU8522_REG432H ; 
 int /*<<< orphan*/  AU8522_REG433H ; 
 int /*<<< orphan*/  AU8522_REG434H ; 
 int /*<<< orphan*/  AU8522_REG435H ; 
 int /*<<< orphan*/  AU8522_REG436H ; 
 int /*<<< orphan*/  AU8522_TOREGAAGC_REG0E5H ; 
 int AU8522_TOREGAAGC_REG0E5H_CVBS ; 
 int /*<<< orphan*/  AU8522_TVDEC_AGC_HIGH_LIMIT_REG079H ; 
 int AU8522_TVDEC_AGC_HIGH_LIMIT_REG079H_CVBS ; 
 int /*<<< orphan*/  AU8522_TVDEC_AGC_LOW_LIMIT_REG0E4H ; 
 int AU8522_TVDEC_AGC_LOW_LIMIT_REG0E4H_CVBS ; 
 int /*<<< orphan*/  AU8522_TVDEC_BRIGHTNESS_REG00AH ; 
 int /*<<< orphan*/  AU8522_TVDEC_COMB_DCDIF_THR1_REG06CH ; 
 int AU8522_TVDEC_COMB_DCDIF_THR1_REG06CH_CVBS ; 
 int AU8522_TVDEC_COMB_DCDIF_THR1_REG06CH_SVIDEO ; 
 int /*<<< orphan*/  AU8522_TVDEC_COMB_DCDIF_THR2_REG06DH ; 
 int AU8522_TVDEC_COMB_DCDIF_THR2_REG06DH_CVBS ; 
 int AU8522_TVDEC_COMB_DCDIF_THR2_REG06DH_SVIDEO ; 
 int /*<<< orphan*/  AU8522_TVDEC_COMB_DCDIF_THR3_REG06EH ; 
 int AU8522_TVDEC_COMB_DCDIF_THR3_REG06EH_CVBS ; 
 int /*<<< orphan*/  AU8522_TVDEC_COMB_DC_THR1_NTSC_REG070H ; 
 int AU8522_TVDEC_COMB_DC_THR1_NTSC_REG070H_CVBS ; 
 int /*<<< orphan*/  AU8522_TVDEC_COMB_DC_THR2_NTSC_REG073H ; 
 int AU8522_TVDEC_COMB_DC_THR2_NTSC_REG073H_CVBS ; 
 int /*<<< orphan*/  AU8522_TVDEC_COMB_HDIF_THR1_REG069H ; 
 int AU8522_TVDEC_COMB_HDIF_THR1_REG069H_CVBS ; 
 int /*<<< orphan*/  AU8522_TVDEC_COMB_HDIF_THR2_REG06AH ; 
 int AU8522_TVDEC_COMB_HDIF_THR2_REG06AH_CVBS ; 
 int /*<<< orphan*/  AU8522_TVDEC_COMB_HDIF_THR3_REG06BH ; 
 int AU8522_TVDEC_COMB_HDIF_THR3_REG06BH_CVBS ; 
 int /*<<< orphan*/  AU8522_TVDEC_COMB_MODE_REG015H ; 
 int AU8522_TVDEC_COMB_MODE_REG015H_CVBS ; 
 int /*<<< orphan*/  AU8522_TVDEC_COMB_NOTCH_THR_REG068H ; 
 int AU8522_TVDEC_COMB_NOTCH_THR_REG068H_CVBS ; 
 int /*<<< orphan*/  AU8522_TVDEC_COMB_VDIF_THR1_REG065H ; 
 int AU8522_TVDEC_COMB_VDIF_THR1_REG065H_CVBS ; 
 int /*<<< orphan*/  AU8522_TVDEC_COMB_VDIF_THR2_REG066H ; 
 int AU8522_TVDEC_COMB_VDIF_THR2_REG066H_CVBS ; 
 int /*<<< orphan*/  AU8522_TVDEC_COMB_VDIF_THR3_REG067H ; 
 int AU8522_TVDEC_COMB_VDIF_THR3_REG067H_CVBS ; 
 int /*<<< orphan*/  AU8522_TVDEC_CONTRAST_REG00BH ; 
 int /*<<< orphan*/  AU8522_TVDEC_DCAGC_CTRL_REG077H ; 
 int AU8522_TVDEC_DCAGC_CTRL_REG077H_CVBS ; 
 int /*<<< orphan*/  AU8522_TVDEC_FORMAT_CTRL1_REG061H ; 
 int AU8522_TVDEC_FORMAT_CTRL1_REG061H_CVBS13 ; 
 int /*<<< orphan*/  AU8522_TVDEC_FORMAT_CTRL2_REG062H ; 
 int AU8522_TVDEC_FORMAT_CTRL2_REG062H_CVBS13 ; 
 int /*<<< orphan*/  AU8522_TVDEC_HUE_H_REG00EH ; 
 int /*<<< orphan*/  AU8522_TVDEC_HUE_L_REG00FH ; 
 int /*<<< orphan*/  AU8522_TVDEC_INTRP_CTRL_REG07BH ; 
 int AU8522_TVDEC_INTRP_CTRL_REG07BH_CVBS ; 
 int /*<<< orphan*/  AU8522_TVDEC_INT_MASK_REG010H ; 
 int /*<<< orphan*/  AU8522_TVDEC_MACROVISION_SYNC_THR_REG07AH ; 
 int AU8522_TVDEC_MACROVISION_SYNC_THR_REG07AH_CVBS ; 
 int /*<<< orphan*/  AU8522_TVDEC_PGA_REG012H ; 
 int AU8522_TVDEC_PGA_REG012H_CVBS ; 
 int /*<<< orphan*/  AU8522_TVDEC_PIC_START_ADJ_REG078H ; 
 int AU8522_TVDEC_PIC_START_ADJ_REG078H_CVBS ; 
 int /*<<< orphan*/  AU8522_TVDEC_SATURATION_CB_REG00CH ; 
 int /*<<< orphan*/  AU8522_TVDEC_SATURATION_CR_REG00DH ; 
 int /*<<< orphan*/  AU8522_TVDEC_SHARPNESSREG009H ; 
 int /*<<< orphan*/  AU8522_TVDEC_UV_SEP_THR_REG06FH ; 
 int AU8522_TVDEC_UV_SEP_THR_REG06FH_CVBS ; 
 int /*<<< orphan*/  AU8522_TVDEC_VCR_DET_HLIM_REG064H ; 
 int AU8522_TVDEC_VCR_DET_HLIM_REG064H_CVBS ; 
 int /*<<< orphan*/  AU8522_TVDEC_VCR_DET_LLIM_REG063H ; 
 int AU8522_TVDEC_VCR_DET_LLIM_REG063H_CVBS ; 
 int /*<<< orphan*/  AU8522_TVDED_DBG_MODE_REG060H ; 
 int AU8522_TVDED_DBG_MODE_REG060H_CVBS ; 
 int /*<<< orphan*/  AU8522_VIDEO_MODE_REG011H ; 
 int NUM_FILTER_COEF ; 
 int /*<<< orphan*/  au8522_writereg (struct au8522_state*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* filter_coef ; 
 int /*<<< orphan*/  setup_vbi (struct au8522_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void setup_decoder_defaults(struct au8522_state *state, u8 input_mode)
{
	int i;
	int filter_coef_type;

	/* Provide reasonable defaults for picture tuning values */
	au8522_writereg(state, AU8522_TVDEC_SHARPNESSREG009H, 0x07);
	au8522_writereg(state, AU8522_TVDEC_BRIGHTNESS_REG00AH, 0xed);
	state->brightness = 0xed - 128;
	au8522_writereg(state, AU8522_TVDEC_CONTRAST_REG00BH, 0x79);
	state->contrast = 0x79;
	au8522_writereg(state, AU8522_TVDEC_SATURATION_CB_REG00CH, 0x80);
	au8522_writereg(state, AU8522_TVDEC_SATURATION_CR_REG00DH, 0x80);
	state->saturation = 0x80;
	au8522_writereg(state, AU8522_TVDEC_HUE_H_REG00EH, 0x00);
	au8522_writereg(state, AU8522_TVDEC_HUE_L_REG00FH, 0x00);
	state->hue = 0x00;

	/* Other decoder registers */
	au8522_writereg(state, AU8522_TVDEC_INT_MASK_REG010H, 0x00);

	if (input_mode == 0x23) {
		/* S-Video input mapping */
		au8522_writereg(state, AU8522_VIDEO_MODE_REG011H, 0x04);
	} else {
		/* All other modes (CVBS/ATVRF etc.) */
		au8522_writereg(state, AU8522_VIDEO_MODE_REG011H, 0x00);
	}

	au8522_writereg(state, AU8522_TVDEC_PGA_REG012H,
			AU8522_TVDEC_PGA_REG012H_CVBS);
	au8522_writereg(state, AU8522_TVDEC_COMB_MODE_REG015H,
			AU8522_TVDEC_COMB_MODE_REG015H_CVBS);
	au8522_writereg(state, AU8522_TVDED_DBG_MODE_REG060H,
			AU8522_TVDED_DBG_MODE_REG060H_CVBS);
	au8522_writereg(state, AU8522_TVDEC_FORMAT_CTRL1_REG061H,
			AU8522_TVDEC_FORMAT_CTRL1_REG061H_CVBS13);
	au8522_writereg(state, AU8522_TVDEC_FORMAT_CTRL2_REG062H,
			AU8522_TVDEC_FORMAT_CTRL2_REG062H_CVBS13);
	au8522_writereg(state, AU8522_TVDEC_VCR_DET_LLIM_REG063H,
			AU8522_TVDEC_VCR_DET_LLIM_REG063H_CVBS);
	au8522_writereg(state, AU8522_TVDEC_VCR_DET_HLIM_REG064H,
			AU8522_TVDEC_VCR_DET_HLIM_REG064H_CVBS);
	au8522_writereg(state, AU8522_TVDEC_COMB_VDIF_THR1_REG065H,
			AU8522_TVDEC_COMB_VDIF_THR1_REG065H_CVBS);
	au8522_writereg(state, AU8522_TVDEC_COMB_VDIF_THR2_REG066H,
			AU8522_TVDEC_COMB_VDIF_THR2_REG066H_CVBS);
	au8522_writereg(state, AU8522_TVDEC_COMB_VDIF_THR3_REG067H,
			AU8522_TVDEC_COMB_VDIF_THR3_REG067H_CVBS);
	au8522_writereg(state, AU8522_TVDEC_COMB_NOTCH_THR_REG068H,
			AU8522_TVDEC_COMB_NOTCH_THR_REG068H_CVBS);
	au8522_writereg(state, AU8522_TVDEC_COMB_HDIF_THR1_REG069H,
			AU8522_TVDEC_COMB_HDIF_THR1_REG069H_CVBS);
	au8522_writereg(state, AU8522_TVDEC_COMB_HDIF_THR2_REG06AH,
			AU8522_TVDEC_COMB_HDIF_THR2_REG06AH_CVBS);
	au8522_writereg(state, AU8522_TVDEC_COMB_HDIF_THR3_REG06BH,
			AU8522_TVDEC_COMB_HDIF_THR3_REG06BH_CVBS);
	if (input_mode == AU8522_INPUT_CONTROL_REG081H_SVIDEO_CH13 ||
	    input_mode == AU8522_INPUT_CONTROL_REG081H_SVIDEO_CH24) {
		au8522_writereg(state, AU8522_TVDEC_COMB_DCDIF_THR1_REG06CH,
				AU8522_TVDEC_COMB_DCDIF_THR1_REG06CH_SVIDEO);
		au8522_writereg(state, AU8522_TVDEC_COMB_DCDIF_THR2_REG06DH,
				AU8522_TVDEC_COMB_DCDIF_THR2_REG06DH_SVIDEO);
	} else {
		au8522_writereg(state, AU8522_TVDEC_COMB_DCDIF_THR1_REG06CH,
				AU8522_TVDEC_COMB_DCDIF_THR1_REG06CH_CVBS);
		au8522_writereg(state, AU8522_TVDEC_COMB_DCDIF_THR2_REG06DH,
				AU8522_TVDEC_COMB_DCDIF_THR2_REG06DH_CVBS);
	}
	au8522_writereg(state, AU8522_TVDEC_COMB_DCDIF_THR3_REG06EH,
			AU8522_TVDEC_COMB_DCDIF_THR3_REG06EH_CVBS);
	au8522_writereg(state, AU8522_TVDEC_UV_SEP_THR_REG06FH,
			AU8522_TVDEC_UV_SEP_THR_REG06FH_CVBS);
	au8522_writereg(state, AU8522_TVDEC_COMB_DC_THR1_NTSC_REG070H,
			AU8522_TVDEC_COMB_DC_THR1_NTSC_REG070H_CVBS);
	au8522_writereg(state, AU8522_REG071H, AU8522_REG071H_CVBS);
	au8522_writereg(state, AU8522_REG072H, AU8522_REG072H_CVBS);
	au8522_writereg(state, AU8522_TVDEC_COMB_DC_THR2_NTSC_REG073H,
			AU8522_TVDEC_COMB_DC_THR2_NTSC_REG073H_CVBS);
	au8522_writereg(state, AU8522_REG074H, AU8522_REG074H_CVBS);
	au8522_writereg(state, AU8522_REG075H, AU8522_REG075H_CVBS);
	au8522_writereg(state, AU8522_TVDEC_DCAGC_CTRL_REG077H,
			AU8522_TVDEC_DCAGC_CTRL_REG077H_CVBS);
	au8522_writereg(state, AU8522_TVDEC_PIC_START_ADJ_REG078H,
			AU8522_TVDEC_PIC_START_ADJ_REG078H_CVBS);
	au8522_writereg(state, AU8522_TVDEC_AGC_HIGH_LIMIT_REG079H,
			AU8522_TVDEC_AGC_HIGH_LIMIT_REG079H_CVBS);
	au8522_writereg(state, AU8522_TVDEC_MACROVISION_SYNC_THR_REG07AH,
			AU8522_TVDEC_MACROVISION_SYNC_THR_REG07AH_CVBS);
	au8522_writereg(state, AU8522_TVDEC_INTRP_CTRL_REG07BH,
			AU8522_TVDEC_INTRP_CTRL_REG07BH_CVBS);
	au8522_writereg(state, AU8522_TVDEC_AGC_LOW_LIMIT_REG0E4H,
			AU8522_TVDEC_AGC_LOW_LIMIT_REG0E4H_CVBS);
	au8522_writereg(state, AU8522_TOREGAAGC_REG0E5H,
			AU8522_TOREGAAGC_REG0E5H_CVBS);
	au8522_writereg(state, AU8522_REG016H, AU8522_REG016H_CVBS);

	setup_vbi(state, 0);

	if (input_mode == AU8522_INPUT_CONTROL_REG081H_SVIDEO_CH13 ||
	    input_mode == AU8522_INPUT_CONTROL_REG081H_SVIDEO_CH24) {
		/* Despite what the table says, for the HVR-950q we still need
		   to be in CVBS mode for the S-Video input (reason unknown). */
		/* filter_coef_type = 3; */
		filter_coef_type = 5;
	} else {
		filter_coef_type = 5;
	}

	/* Load the Video Decoder Filter Coefficients */
	for (i = 0; i < NUM_FILTER_COEF; i++) {
		au8522_writereg(state, filter_coef[i].reg_name,
				filter_coef[i].reg_val[filter_coef_type]);
	}

	/* It's not clear what these registers are for, but they are always
	   set to the same value regardless of what mode we're in */
	au8522_writereg(state, AU8522_REG42EH, 0x87);
	au8522_writereg(state, AU8522_REG42FH, 0xa2);
	au8522_writereg(state, AU8522_REG430H, 0xbf);
	au8522_writereg(state, AU8522_REG431H, 0xcb);
	au8522_writereg(state, AU8522_REG432H, 0xa1);
	au8522_writereg(state, AU8522_REG433H, 0x41);
	au8522_writereg(state, AU8522_REG434H, 0x88);
	au8522_writereg(state, AU8522_REG435H, 0xc2);
	au8522_writereg(state, AU8522_REG436H, 0x3c);
}