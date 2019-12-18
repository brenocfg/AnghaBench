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
struct uvd {int /*<<< orphan*/  video_endp; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int camera_model; } ;

/* Variables and functions */
#define  IBMCAM_MODEL_1 131 
#define  IBMCAM_MODEL_2 130 
#define  IBMCAM_MODEL_3 129 
#define  IBMCAM_MODEL_4 128 
 TYPE_1__* IBMCAM_T (struct uvd*) ; 
 int /*<<< orphan*/  ibmcam_model1_setup_after_video_if (struct uvd*) ; 
 int /*<<< orphan*/  ibmcam_model2_setup_after_video_if (struct uvd*) ; 
 int /*<<< orphan*/  ibmcam_model3_setup_after_video_if (struct uvd*) ; 
 int /*<<< orphan*/  ibmcam_model4_setup_after_video_if (struct uvd*) ; 
 int /*<<< orphan*/  ibmcam_veio (struct uvd*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ibmcam_video_stop (struct uvd*) ; 
 int /*<<< orphan*/  usb_clear_halt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvisocpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ibmcam_reinit_iso(struct uvd *uvd, int do_stop)
{
	switch (IBMCAM_T(uvd)->camera_model) {
	case IBMCAM_MODEL_1:
		if (do_stop)
			ibmcam_video_stop(uvd);
		ibmcam_veio(uvd, 0, 0x0001, 0x0114);
		ibmcam_veio(uvd, 0, 0x00c0, 0x010c);
		usb_clear_halt(uvd->dev, usb_rcvisocpipe(uvd->dev, uvd->video_endp));
		ibmcam_model1_setup_after_video_if(uvd);
		break;
	case IBMCAM_MODEL_2:
		ibmcam_model2_setup_after_video_if(uvd);
		break;
	case IBMCAM_MODEL_3:
		ibmcam_video_stop(uvd);
		ibmcam_model3_setup_after_video_if(uvd);
		break;
	case IBMCAM_MODEL_4:
		ibmcam_model4_setup_after_video_if(uvd);
		break;
	}
}