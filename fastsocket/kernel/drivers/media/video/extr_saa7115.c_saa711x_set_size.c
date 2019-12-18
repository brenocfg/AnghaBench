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
struct saa711x_state {int std; int width; int height; int /*<<< orphan*/  ident; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  R_80_GLOBAL_CNTL_1 ; 
 int /*<<< orphan*/  R_CC_B_HORIZ_OUTPUT_WINDOW_LENGTH ; 
 int /*<<< orphan*/  R_CD_B_HORIZ_OUTPUT_WINDOW_LENGTH_MSB ; 
 int /*<<< orphan*/  R_CE_B_VERT_OUTPUT_WINDOW_LENGTH ; 
 int /*<<< orphan*/  R_CF_B_VERT_OUTPUT_WINDOW_LENGTH_MSB ; 
 int /*<<< orphan*/  R_D0_B_HORIZ_PRESCALING ; 
 int /*<<< orphan*/  R_D5_B_LUMA_CONTRAST_CNTL ; 
 int /*<<< orphan*/  R_D6_B_CHROMA_SATURATION_CNTL ; 
 int /*<<< orphan*/  R_D8_B_HORIZ_LUMA_SCALING_INC ; 
 int /*<<< orphan*/  R_D9_B_HORIZ_LUMA_SCALING_INC_MSB ; 
 int /*<<< orphan*/  R_DC_B_HORIZ_CHROMA_SCALING ; 
 int /*<<< orphan*/  R_DD_B_HORIZ_CHROMA_SCALING_MSB ; 
 int /*<<< orphan*/  R_E0_B_VERT_LUMA_SCALING_INC ; 
 int /*<<< orphan*/  R_E1_B_VERT_LUMA_SCALING_INC_MSB ; 
 int /*<<< orphan*/  R_E2_B_VERT_CHROMA_SCALING_INC ; 
 int /*<<< orphan*/  R_E3_B_VERT_CHROMA_SCALING_INC_MSB ; 
 int V4L2_STD_625_50 ; 
 int VRES_60HZ ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  saa7115_cfg_reset_scaler ; 
 int /*<<< orphan*/  saa711x_has_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int saa711x_read (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa711x_write (struct v4l2_subdev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  saa711x_writeregs (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 struct saa711x_state* to_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*,int,int) ; 

__attribute__((used)) static int saa711x_set_size(struct v4l2_subdev *sd, int width, int height)
{
	struct saa711x_state *state = to_state(sd);
	int HPSC, HFSC;
	int VSCY;
	int res;
	int is_50hz = state->std & V4L2_STD_625_50;
	int Vsrc = is_50hz ? 576 : 480;

	v4l2_dbg(1, debug, sd, "decoder set size to %ix%i\n", width, height);

	/* FIXME need better bounds checking here */
	if ((width < 1) || (width > 1440))
		return -EINVAL;
	if ((height < 1) || (height > Vsrc))
		return -EINVAL;

	if (!saa711x_has_reg(state->ident, R_D0_B_HORIZ_PRESCALING)) {
		/* Decoder only supports 720 columns and 480 or 576 lines */
		if (width != 720)
			return -EINVAL;
		if (height != Vsrc)
			return -EINVAL;
	}

	state->width = width;
	state->height = height;

	if (!saa711x_has_reg(state->ident, R_CC_B_HORIZ_OUTPUT_WINDOW_LENGTH))
		return 0;

	/* probably have a valid size, let's set it */
	/* Set output width/height */
	/* width */

	saa711x_write(sd, R_CC_B_HORIZ_OUTPUT_WINDOW_LENGTH,
					(u8) (width & 0xff));
	saa711x_write(sd, R_CD_B_HORIZ_OUTPUT_WINDOW_LENGTH_MSB,
					(u8) ((width >> 8) & 0xff));

	/* Vertical Scaling uses height/2 */
	res = height / 2;

	/* On 60Hz, it is using a higher Vertical Output Size */
	if (!is_50hz)
		res += (VRES_60HZ - 480) >> 1;

		/* height */
	saa711x_write(sd, R_CE_B_VERT_OUTPUT_WINDOW_LENGTH,
					(u8) (res & 0xff));
	saa711x_write(sd, R_CF_B_VERT_OUTPUT_WINDOW_LENGTH_MSB,
					(u8) ((res >> 8) & 0xff));

	/* Scaling settings */
	/* Hprescaler is floor(inres/outres) */
	HPSC = (int)(720 / width);
	/* 0 is not allowed (div. by zero) */
	HPSC = HPSC ? HPSC : 1;
	HFSC = (int)((1024 * 720) / (HPSC * width));
	/* FIXME hardcodes to "Task B"
	 * write H prescaler integer */
	saa711x_write(sd, R_D0_B_HORIZ_PRESCALING,
				(u8) (HPSC & 0x3f));

	v4l2_dbg(1, debug, sd, "Hpsc: 0x%05x, Hfsc: 0x%05x\n", HPSC, HFSC);
	/* write H fine-scaling (luminance) */
	saa711x_write(sd, R_D8_B_HORIZ_LUMA_SCALING_INC,
				(u8) (HFSC & 0xff));
	saa711x_write(sd, R_D9_B_HORIZ_LUMA_SCALING_INC_MSB,
				(u8) ((HFSC >> 8) & 0xff));
	/* write H fine-scaling (chrominance)
	 * must be lum/2, so i'll just bitshift :) */
	saa711x_write(sd, R_DC_B_HORIZ_CHROMA_SCALING,
				(u8) ((HFSC >> 1) & 0xff));
	saa711x_write(sd, R_DD_B_HORIZ_CHROMA_SCALING_MSB,
				(u8) ((HFSC >> 9) & 0xff));

	VSCY = (int)((1024 * Vsrc) / height);
	v4l2_dbg(1, debug, sd, "Vsrc: %d, Vscy: 0x%05x\n", Vsrc, VSCY);

	/* Correct Contrast and Luminance */
	saa711x_write(sd, R_D5_B_LUMA_CONTRAST_CNTL,
					(u8) (64 * 1024 / VSCY));
	saa711x_write(sd, R_D6_B_CHROMA_SATURATION_CNTL,
					(u8) (64 * 1024 / VSCY));

		/* write V fine-scaling (luminance) */
	saa711x_write(sd, R_E0_B_VERT_LUMA_SCALING_INC,
					(u8) (VSCY & 0xff));
	saa711x_write(sd, R_E1_B_VERT_LUMA_SCALING_INC_MSB,
					(u8) ((VSCY >> 8) & 0xff));
		/* write V fine-scaling (chrominance) */
	saa711x_write(sd, R_E2_B_VERT_CHROMA_SCALING_INC,
					(u8) (VSCY & 0xff));
	saa711x_write(sd, R_E3_B_VERT_CHROMA_SCALING_INC_MSB,
					(u8) ((VSCY >> 8) & 0xff));

	saa711x_writeregs(sd, saa7115_cfg_reset_scaler);

	/* Activates task "B" */
	saa711x_write(sd, R_80_GLOBAL_CNTL_1,
				saa711x_read(sd, R_80_GLOBAL_CNTL_1) | 0x20);

	return 0;
}