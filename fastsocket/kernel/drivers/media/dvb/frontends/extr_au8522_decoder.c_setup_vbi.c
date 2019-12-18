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
struct au8522_state {int dummy; } ;

/* Variables and functions */
 int AU8522_TVDEC_VBI_CTRL_H_REG017H ; 
 int AU8522_TVDEC_VBI_CTRL_H_REG017H_CCON ; 
 int AU8522_TVDEC_VBI_CTRL_L_REG018H ; 
 int AU8522_TVDEC_VBI_USER_FRAME_MASK0_REG023H ; 
 int AU8522_TVDEC_VBI_USER_FRAME_MASK1_REG022H ; 
 int AU8522_TVDEC_VBI_USER_FRAME_MASK2_REG021H ; 
 int AU8522_TVDEC_VBI_USER_FRAME_PAT0_REG020H ; 
 int AU8522_TVDEC_VBI_USER_FRAME_PAT1_REG01FH ; 
 int AU8522_TVDEC_VBI_USER_FRAME_PAT2_REG01EH ; 
 int AU8522_TVDEC_VBI_USER_THRESH1_REG01CH ; 
 int AU8522_TVDEC_VBI_USER_TOTAL_BITS_REG019H ; 
 int AU8522_TVDEC_VBI_USER_TUNIT_H_REG01AH ; 
 int AU8522_TVDEC_VBI_USER_TUNIT_L_REG01BH ; 
 int /*<<< orphan*/  au8522_writereg (struct au8522_state*,int,int) ; 

__attribute__((used)) static void setup_vbi(struct au8522_state *state, int aud_input)
{
	int i;

	/* These are set to zero regardless of what mode we're in */
	au8522_writereg(state, AU8522_TVDEC_VBI_CTRL_H_REG017H, 0x00);
	au8522_writereg(state, AU8522_TVDEC_VBI_CTRL_L_REG018H, 0x00);
	au8522_writereg(state, AU8522_TVDEC_VBI_USER_TOTAL_BITS_REG019H, 0x00);
	au8522_writereg(state, AU8522_TVDEC_VBI_USER_TUNIT_H_REG01AH, 0x00);
	au8522_writereg(state, AU8522_TVDEC_VBI_USER_TUNIT_L_REG01BH, 0x00);
	au8522_writereg(state, AU8522_TVDEC_VBI_USER_THRESH1_REG01CH, 0x00);
	au8522_writereg(state, AU8522_TVDEC_VBI_USER_FRAME_PAT2_REG01EH, 0x00);
	au8522_writereg(state, AU8522_TVDEC_VBI_USER_FRAME_PAT1_REG01FH, 0x00);
	au8522_writereg(state, AU8522_TVDEC_VBI_USER_FRAME_PAT0_REG020H, 0x00);
	au8522_writereg(state, AU8522_TVDEC_VBI_USER_FRAME_MASK2_REG021H,
			0x00);
	au8522_writereg(state, AU8522_TVDEC_VBI_USER_FRAME_MASK1_REG022H,
			0x00);
	au8522_writereg(state, AU8522_TVDEC_VBI_USER_FRAME_MASK0_REG023H,
			0x00);

	/* Setup the VBI registers */
	for (i = 0x30; i < 0x60; i++)
		au8522_writereg(state, i, 0x40);

	/* For some reason, every register is 0x40 except register 0x44
	   (confirmed via the HVR-950q USB capture) */
	au8522_writereg(state, 0x44, 0x60);

	/* Enable VBI (we always do this regardless of whether the user is
	   viewing closed caption info) */
	au8522_writereg(state, AU8522_TVDEC_VBI_CTRL_H_REG017H,
			AU8522_TVDEC_VBI_CTRL_H_REG017H_CCON);

}