#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int hue; } ;
struct TYPE_4__ {unsigned short hue; } ;
struct uvd {int /*<<< orphan*/  videosize; TYPE_2__ vpic; int /*<<< orphan*/  video_endp; int /*<<< orphan*/  dev; TYPE_1__ vpic_old; } ;
struct TYPE_6__ {int camera_model; } ;

/* Variables and functions */
#define  IBMCAM_MODEL_2 133 
#define  IBMCAM_MODEL_3 132 
#define  IBMCAM_MODEL_4 131 
 TYPE_3__* IBMCAM_T (struct uvd*) ; 
 int /*<<< orphan*/  RESTRICT_TO_RANGE (unsigned short,int,int) ; 
#define  VIDEOSIZE_128x96 130 
#define  VIDEOSIZE_160x120 129 
#define  VIDEOSIZE_176x144 128 
 int /*<<< orphan*/  ibmcam_model2_Packet1 (struct uvd*,int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  ibmcam_model3_Packet1 (struct uvd*,int,unsigned short) ; 
 int /*<<< orphan*/  ibmcam_veio (struct uvd*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mod2_hue ; 
 int /*<<< orphan*/  usb_clear_halt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvisocpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ibmcam_set_hue(struct uvd *uvd)
{
	switch (IBMCAM_T(uvd)->camera_model) {
	case IBMCAM_MODEL_2:
	{
		unsigned short hue = uvd->vpic.hue >> 9; /* 0 .. 7F */
		if (uvd->vpic_old.hue == hue)
			return;
		uvd->vpic_old.hue = hue;
		ibmcam_model2_Packet1(uvd, mod2_hue, hue);
		/* ibmcam_model2_Packet1(uvd, mod2_saturation, sat); */
		break;
	}
	case IBMCAM_MODEL_3:
	{
#if 0 /* This seems not to work. No problem, will fix programmatically */
		unsigned short hue = 0x05 + (uvd->vpic.hue / (0xFFFF / (0x37 - 0x05 + 1)));
		RESTRICT_TO_RANGE(hue, 0x05, 0x37);
		if (uvd->vpic_old.hue == hue)
			return;
		uvd->vpic_old.hue = hue;
		ibmcam_veio(uvd, 0, 0x0000, 0x010c);	/* Stop */
		ibmcam_model3_Packet1(uvd, 0x007e, hue);
		ibmcam_veio(uvd, 0, 0x0001, 0x0114);
		ibmcam_veio(uvd, 0, 0x00c0, 0x010c);	/* Go! */
		usb_clear_halt(uvd->dev, usb_rcvisocpipe(uvd->dev, uvd->video_endp));
		ibmcam_veio(uvd, 0, 0x0001, 0x0113);
#endif
		break;
	}
	case IBMCAM_MODEL_4:
	{
		unsigned short r_gain, g_gain, b_gain, hue;

		/*
		 * I am not sure r/g/b_gain variables exactly control gain
		 * of those channels. Most likely they subtly change some
		 * very internal image processing settings in the camera.
		 * In any case, here is what they do, and feel free to tweak:
		 *
		 * r_gain: seriously affects red gain
		 * g_gain: seriously affects green gain
		 * b_gain: seriously affects blue gain
		 * hue: changes average color from violet (0) to red (0xFF)
		 *
		 * These settings are preset for a decent white balance in
		 * 320x240, 352x288 modes. Low-res modes exhibit higher contrast
		 * and therefore may need different values here.
		 */
		hue = 20 + (uvd->vpic.hue >> 9);
		switch (uvd->videosize) {
		case VIDEOSIZE_128x96:
			r_gain = 90;
			g_gain = 166;
			b_gain = 175;
			break;
		case VIDEOSIZE_160x120:
			r_gain = 70;
			g_gain = 166;
			b_gain = 185;
			break;
		case VIDEOSIZE_176x144:
			r_gain = 160;
			g_gain = 175;
			b_gain = 185;
			break;
		default:
			r_gain = 120;
			g_gain = 166;
			b_gain = 175;
			break;
		}
		RESTRICT_TO_RANGE(hue, 1, 0x7f);

		ibmcam_veio(uvd, 0, 0x00aa, 0x012d);
		ibmcam_veio(uvd, 0, 0x001e, 0x012f);
		ibmcam_veio(uvd, 0, 0xd141, 0x0124);
		ibmcam_veio(uvd, 0, g_gain, 0x0127);	/* Green gain */
		ibmcam_veio(uvd, 0, r_gain, 0x012e);	/* Red gain */
		ibmcam_veio(uvd, 0, b_gain, 0x0130);	/* Blue gain */
		ibmcam_veio(uvd, 0, 0x8a28, 0x0124);
		ibmcam_veio(uvd, 0, hue,    0x012d);	/* Hue */
		ibmcam_veio(uvd, 0, 0xf545, 0x0124);
		break;
	}
	default:
		break;
	}
}