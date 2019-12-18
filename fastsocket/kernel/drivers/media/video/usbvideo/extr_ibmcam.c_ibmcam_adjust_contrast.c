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
struct TYPE_5__ {unsigned char contrast; } ;
struct TYPE_4__ {int contrast; } ;
struct uvd {int /*<<< orphan*/  video_endp; int /*<<< orphan*/  dev; TYPE_2__ vpic_old; TYPE_1__ vpic; } ;
struct TYPE_6__ {int camera_model; } ;

/* Variables and functions */
#define  IBMCAM_MODEL_1 131 
#define  IBMCAM_MODEL_2 130 
#define  IBMCAM_MODEL_3 129 
#define  IBMCAM_MODEL_4 128 
 TYPE_3__* IBMCAM_T (struct uvd*) ; 
 int /*<<< orphan*/  RESTRICT_TO_RANGE (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  contrast_14 ; 
 int /*<<< orphan*/  ibmcam_Packet_Format1 (struct uvd*,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  ibmcam_model3_Packet1 (struct uvd*,int,unsigned short) ; 
 int /*<<< orphan*/  ibmcam_send_FF_04_02 (struct uvd*) ; 
 int /*<<< orphan*/  ibmcam_veio (struct uvd*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  usb_clear_halt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvisocpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ibmcam_adjust_contrast(struct uvd *uvd)
{
	unsigned char a_contrast = uvd->vpic.contrast >> 12;
	unsigned char new_contrast;

	if (a_contrast >= 16)
		a_contrast = 15;
	new_contrast = 15 - a_contrast;
	if (new_contrast == uvd->vpic_old.contrast)
		return;
	uvd->vpic_old.contrast = new_contrast;
	switch (IBMCAM_T(uvd)->camera_model) {
	case IBMCAM_MODEL_1:
	{
		const int ntries = 5;
		int i;
		for (i=0; i < ntries; i++) {
			ibmcam_Packet_Format1(uvd, contrast_14, new_contrast);
			ibmcam_send_FF_04_02(uvd);
		}
		break;
	}
	case IBMCAM_MODEL_2:
	case IBMCAM_MODEL_4:
		/* Models 2, 4 do not have this control; implemented in software. */
		break;
	case IBMCAM_MODEL_3:
	{	/* Preset hardware values */
		static const struct {
			unsigned short cv1;
			unsigned short cv2;
			unsigned short cv3;
		} cv[7] = {
			{ 0x05, 0x05, 0x0f },	/* Minimum */
			{ 0x04, 0x04, 0x16 },
			{ 0x02, 0x03, 0x16 },
			{ 0x02, 0x08, 0x16 },
			{ 0x01, 0x0c, 0x16 },
			{ 0x01, 0x0e, 0x16 },
			{ 0x01, 0x10, 0x16 }	/* Maximum */
		};
		int i = a_contrast / 2;
		RESTRICT_TO_RANGE(i, 0, 6);
		ibmcam_veio(uvd, 0, 0x0000, 0x010c);	/* Stop */
		ibmcam_model3_Packet1(uvd, 0x0067, cv[i].cv1);
		ibmcam_model3_Packet1(uvd, 0x005b, cv[i].cv2);
		ibmcam_model3_Packet1(uvd, 0x005c, cv[i].cv3);
		ibmcam_veio(uvd, 0, 0x0001, 0x0114);
		ibmcam_veio(uvd, 0, 0x00c0, 0x010c);	/* Go! */
		usb_clear_halt(uvd->dev, usb_rcvisocpipe(uvd->dev, uvd->video_endp));
		break;
	}
	default:
		break;
	}
}