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
typedef  scalar_t__ v4l2_std_id ;
typedef  int u8 ;
struct v4l2_subdev {int dummy; } ;
struct saa711x_state {scalar_t__ std; scalar_t__ ident; int /*<<< orphan*/  audclk_freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  R_0E_CHROMA_CNTL_1 ; 
 int /*<<< orphan*/  R_80_GLOBAL_CNTL_1 ; 
 scalar_t__ V4L2_IDENT_SAA7113 ; 
 scalar_t__ V4L2_IDENT_SAA7114 ; 
 scalar_t__ V4L2_STD_525_60 ; 
 scalar_t__ V4L2_STD_NTSC_M_JP ; 
 scalar_t__ V4L2_STD_PAL_60 ; 
 scalar_t__ V4L2_STD_PAL_M ; 
 scalar_t__ V4L2_STD_PAL_Nc ; 
 scalar_t__ V4L2_STD_SECAM ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  saa7115_cfg_50hz_video ; 
 int /*<<< orphan*/  saa7115_cfg_60hz_video ; 
 int /*<<< orphan*/  saa7115_cfg_vbi_on ; 
 int saa711x_read (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa711x_s_clock_freq (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa711x_set_size (struct v4l2_subdev*,int,int) ; 
 int /*<<< orphan*/  saa711x_write (struct v4l2_subdev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  saa711x_writeregs (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 struct saa711x_state* to_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*) ; 

__attribute__((used)) static void saa711x_set_v4lstd(struct v4l2_subdev *sd, v4l2_std_id std)
{
	struct saa711x_state *state = to_state(sd);

	/* Prevent unnecessary standard changes. During a standard
	   change the I-Port is temporarily disabled. Any devices
	   reading from that port can get confused.
	   Note that s_std is also used to switch from
	   radio to TV mode, so if a s_std is broadcast to
	   all I2C devices then you do not want to have an unwanted
	   side-effect here. */
	if (std == state->std)
		return;

	state->std = std;

	// This works for NTSC-M, SECAM-L and the 50Hz PAL variants.
	if (std & V4L2_STD_525_60) {
		v4l2_dbg(1, debug, sd, "decoder set standard 60 Hz\n");
		saa711x_writeregs(sd, saa7115_cfg_60hz_video);
		saa711x_set_size(sd, 720, 480);
	} else {
		v4l2_dbg(1, debug, sd, "decoder set standard 50 Hz\n");
		saa711x_writeregs(sd, saa7115_cfg_50hz_video);
		saa711x_set_size(sd, 720, 576);
	}

	/* Register 0E - Bits D6-D4 on NO-AUTO mode
		(SAA7111 and SAA7113 doesn't have auto mode)
	    50 Hz / 625 lines           60 Hz / 525 lines
	000 PAL BGDHI (4.43Mhz)         NTSC M (3.58MHz)
	001 NTSC 4.43 (50 Hz)           PAL 4.43 (60 Hz)
	010 Combination-PAL N (3.58MHz) NTSC 4.43 (60 Hz)
	011 NTSC N (3.58MHz)            PAL M (3.58MHz)
	100 reserved                    NTSC-Japan (3.58MHz)
	*/
	if (state->ident <= V4L2_IDENT_SAA7113) {
		u8 reg = saa711x_read(sd, R_0E_CHROMA_CNTL_1) & 0x8f;

		if (std == V4L2_STD_PAL_M) {
			reg |= 0x30;
		} else if (std == V4L2_STD_PAL_Nc) {
			reg |= 0x20;
		} else if (std == V4L2_STD_PAL_60) {
			reg |= 0x10;
		} else if (std == V4L2_STD_NTSC_M_JP) {
			reg |= 0x40;
		} else if (std & V4L2_STD_SECAM) {
			reg |= 0x50;
		}
		saa711x_write(sd, R_0E_CHROMA_CNTL_1, reg);
	} else {
		/* restart task B if needed */
		int taskb = saa711x_read(sd, R_80_GLOBAL_CNTL_1) & 0x10;

		if (taskb && state->ident == V4L2_IDENT_SAA7114) {
			saa711x_writeregs(sd, saa7115_cfg_vbi_on);
		}

		/* switch audio mode too! */
		saa711x_s_clock_freq(sd, state->audclk_freq);
	}
}