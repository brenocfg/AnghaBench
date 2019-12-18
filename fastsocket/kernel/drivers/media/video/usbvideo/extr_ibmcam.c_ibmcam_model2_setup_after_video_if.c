#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int hue; } ;
struct uvd {int videosize; scalar_t__ debug; int /*<<< orphan*/  video_endp; TYPE_2__* dev; TYPE_1__ vpic; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 short FRAMERATE_MAX ; 
 short FRAMERATE_MIN ; 
 int /*<<< orphan*/  RESTRICT_TO_RANGE (short,short,int) ; 
#define  VIDEOSIZE_176x144 131 
#define  VIDEOSIZE_320x240 130 
#define  VIDEOSIZE_352x240 129 
#define  VIDEOSIZE_352x288 128 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,short) ; 
 short framerate ; 
 int /*<<< orphan*/  ibmcam_model2_Packet1 (struct uvd*,int,int) ; 
 int /*<<< orphan*/  ibmcam_veio (struct uvd*,int /*<<< orphan*/ ,int,int) ; 
 short init_model2_rg2 ; 
 short init_model2_sat ; 
 short init_model2_yb ; 
 int lighting ; 
 int mod2_brightness ; 
 int mod2_color_balance_rg2 ; 
 int mod2_color_balance_yb ; 
 int mod2_hue ; 
 int mod2_saturation ; 
 int mod2_sensitivity ; 
 int mod2_set_framerate ; 
 int /*<<< orphan*/  usb_clear_halt (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvisocpipe (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ibmcam_model2_setup_after_video_if(struct uvd *uvd)
{
	unsigned short setup_model2_rg2, setup_model2_sat, setup_model2_yb;

	ibmcam_veio(uvd, 0, 0x0000, 0x0100);	/* LED on */

	switch (uvd->videosize) {
	case VIDEOSIZE_176x144:
		ibmcam_veio(uvd, 0, 0x0050, 0x0111);
		ibmcam_veio(uvd, 0, 0x00d0, 0x0111);
		break;
	case VIDEOSIZE_320x240:
	case VIDEOSIZE_352x240:
	case VIDEOSIZE_352x288:
		ibmcam_veio(uvd, 0, 0x0040, 0x0111);
		ibmcam_veio(uvd, 0, 0x00c0, 0x0111);
		break;
	}
	ibmcam_veio(uvd, 0, 0x009b, 0x010f);
	ibmcam_veio(uvd, 0, 0x00bb, 0x010f);

	/*
	 * Hardware settings, may affect CMOS sensor; not user controls!
	 * -------------------------------------------------------------
	 * 0x0004: no effect
	 * 0x0006: hardware effect
	 * 0x0008: no effect
	 * 0x000a: stops video stream, probably important h/w setting
	 * 0x000c: changes color in hardware manner (not user setting)
	 * 0x0012: changes number of colors (does not affect speed)
	 * 0x002a: no effect
	 * 0x002c: hardware setting (related to scan lines)
	 * 0x002e: stops video stream, probably important h/w setting
	 */
	ibmcam_model2_Packet1(uvd, 0x000a, 0x005c);
	ibmcam_model2_Packet1(uvd, 0x0004, 0x0000);
	ibmcam_model2_Packet1(uvd, 0x0006, 0x00fb);
	ibmcam_model2_Packet1(uvd, 0x0008, 0x0000);
	ibmcam_model2_Packet1(uvd, 0x000c, 0x0009);
	ibmcam_model2_Packet1(uvd, 0x0012, 0x000a);
	ibmcam_model2_Packet1(uvd, 0x002a, 0x0000);
	ibmcam_model2_Packet1(uvd, 0x002c, 0x0000);
	ibmcam_model2_Packet1(uvd, 0x002e, 0x0008);

	/*
	 * Function 0x0030 pops up all over the place. Apparently
	 * it is a hardware control register, with every bit assigned to
	 * do something.
	 */
	ibmcam_model2_Packet1(uvd, 0x0030, 0x0000);

	/*
	 * Magic control of CMOS sensor. Only lower values like
	 * 0-3 work, and picture shifts left or right. Don't change.
	 */
	switch (uvd->videosize) {
	case VIDEOSIZE_176x144:
		ibmcam_model2_Packet1(uvd, 0x0014, 0x0002);
		ibmcam_model2_Packet1(uvd, 0x0016, 0x0002); /* Horizontal shift */
		ibmcam_model2_Packet1(uvd, 0x0018, 0x004a); /* Another hardware setting */
		break;
	case VIDEOSIZE_320x240:
		ibmcam_model2_Packet1(uvd, 0x0014, 0x0009);
		ibmcam_model2_Packet1(uvd, 0x0016, 0x0005); /* Horizontal shift */
		ibmcam_model2_Packet1(uvd, 0x0018, 0x0044); /* Another hardware setting */
		break;
	case VIDEOSIZE_352x240:
		/* This mode doesn't work as Windows programs it; changed to work */
		ibmcam_model2_Packet1(uvd, 0x0014, 0x0009); /* Windows sets this to 8 */
		ibmcam_model2_Packet1(uvd, 0x0016, 0x0003); /* Horizontal shift */
		ibmcam_model2_Packet1(uvd, 0x0018, 0x0044); /* Windows sets this to 0x0045 */
		break;
	case VIDEOSIZE_352x288:
		ibmcam_model2_Packet1(uvd, 0x0014, 0x0003);
		ibmcam_model2_Packet1(uvd, 0x0016, 0x0002); /* Horizontal shift */
		ibmcam_model2_Packet1(uvd, 0x0018, 0x004a); /* Another hardware setting */
		break;
	}

	ibmcam_model2_Packet1(uvd, mod2_brightness, 0x005a);

	/*
	 * We have our own frame rate setting varying from 0 (slowest) to 6 (fastest).
	 * The camera model 2 allows frame rate in range [0..0x1F] where 0 is also the
	 * slowest setting. However for all practical reasons high settings make no
	 * sense because USB is not fast enough to support high FPS. Be aware that
	 * the picture datastream will be severely disrupted if you ask for
	 * frame rate faster than allowed for the video size - see below:
	 *
	 * Allowable ranges (obtained experimentally on OHCI, K6-3, 450 MHz):
	 * -----------------------------------------------------------------
	 * 176x144: [6..31]
	 * 320x240: [8..31]
	 * 352x240: [10..31]
	 * 352x288: [16..31] I have to raise lower threshold for stability...
	 *
	 * As usual, slower FPS provides better sensitivity.
	 */
	{
		short hw_fps=31, i_framerate;

		RESTRICT_TO_RANGE(framerate, FRAMERATE_MIN, FRAMERATE_MAX);
		i_framerate = FRAMERATE_MAX - framerate + FRAMERATE_MIN;
		switch (uvd->videosize) {
		case VIDEOSIZE_176x144:
			hw_fps = 6 + i_framerate*4;
			break;
		case VIDEOSIZE_320x240:
			hw_fps = 8 + i_framerate*3;
			break;
		case VIDEOSIZE_352x240:
			hw_fps = 10 + i_framerate*2;
			break;
		case VIDEOSIZE_352x288:
			hw_fps = 28 + i_framerate/2;
			break;
		}
		if (uvd->debug > 0)
			dev_info(&uvd->dev->dev, "Framerate (hardware): %hd.\n",
				 hw_fps);
		RESTRICT_TO_RANGE(hw_fps, 0, 31);
		ibmcam_model2_Packet1(uvd, mod2_set_framerate, hw_fps);
	}

	/*
	 * This setting does not visibly affect pictures; left it here
	 * because it was present in Windows USB data stream. This function
	 * does not allow arbitrary values and apparently is a bit mask, to
	 * be activated only at appropriate time. Don't change it randomly!
	 */
	switch (uvd->videosize) {
	case VIDEOSIZE_176x144:
		ibmcam_model2_Packet1(uvd, 0x0026, 0x00c2);
		break;
	case VIDEOSIZE_320x240:
		ibmcam_model2_Packet1(uvd, 0x0026, 0x0044);
		break;
	case VIDEOSIZE_352x240:
		ibmcam_model2_Packet1(uvd, 0x0026, 0x0046);
		break;
	case VIDEOSIZE_352x288:
		ibmcam_model2_Packet1(uvd, 0x0026, 0x0048);
		break;
	}

	ibmcam_model2_Packet1(uvd, mod2_sensitivity, lighting);

	if (init_model2_rg2 >= 0) {
		RESTRICT_TO_RANGE(init_model2_rg2, 0, 255);
		setup_model2_rg2 = init_model2_rg2;
	} else
		setup_model2_rg2 = 0x002f;

	if (init_model2_sat >= 0) {
		RESTRICT_TO_RANGE(init_model2_sat, 0, 255);
		setup_model2_sat = init_model2_sat;
	} else
		setup_model2_sat = 0x0034;

	if (init_model2_yb >= 0) {
		RESTRICT_TO_RANGE(init_model2_yb, 0, 255);
		setup_model2_yb = init_model2_yb;
	} else
		setup_model2_yb = 0x00a0;

	ibmcam_model2_Packet1(uvd, mod2_color_balance_rg2, setup_model2_rg2);
	ibmcam_model2_Packet1(uvd, mod2_saturation, setup_model2_sat);
	ibmcam_model2_Packet1(uvd, mod2_color_balance_yb, setup_model2_yb);
	ibmcam_model2_Packet1(uvd, mod2_hue, uvd->vpic.hue >> 9); /* 0 .. 7F */;

	/* Hardware control command */
	ibmcam_model2_Packet1(uvd, 0x0030, 0x0004);

	ibmcam_veio(uvd, 0, 0x00c0, 0x010c);	/* Go camera, go! */
	usb_clear_halt(uvd->dev, usb_rcvisocpipe(uvd->dev, uvd->video_endp));
}