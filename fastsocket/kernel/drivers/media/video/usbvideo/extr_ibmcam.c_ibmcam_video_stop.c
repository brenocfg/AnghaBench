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
struct uvd {int dummy; } ;
struct TYPE_2__ {int camera_model; int /*<<< orphan*/  initialized; } ;

/* Variables and functions */
#define  IBMCAM_MODEL_1 131 
#define  IBMCAM_MODEL_2 130 
#define  IBMCAM_MODEL_3 129 
#define  IBMCAM_MODEL_4 128 
 TYPE_1__* IBMCAM_T (struct uvd*) ; 
 int /*<<< orphan*/  ibmcam_model2_Packet1 (struct uvd*,int,int) ; 
 int /*<<< orphan*/  ibmcam_model3_Packet1 (struct uvd*,int,int) ; 
 int /*<<< orphan*/  ibmcam_send_FF_04_02 (struct uvd*) ; 
 int /*<<< orphan*/  ibmcam_veio (struct uvd*,int,int,int) ; 

__attribute__((used)) static void ibmcam_video_stop(struct uvd *uvd)
{
	switch (IBMCAM_T(uvd)->camera_model) {
	case IBMCAM_MODEL_1:
		ibmcam_veio(uvd, 0, 0x00, 0x010c);
		ibmcam_veio(uvd, 0, 0x00, 0x010c);
		ibmcam_veio(uvd, 0, 0x01, 0x0114);
		ibmcam_veio(uvd, 0, 0xc0, 0x010c);
		ibmcam_veio(uvd, 0, 0x00, 0x010c);
		ibmcam_send_FF_04_02(uvd);
		ibmcam_veio(uvd, 1, 0x00, 0x0100);
		ibmcam_veio(uvd, 0, 0x81, 0x0100);	/* LED Off */
		break;
	case IBMCAM_MODEL_2:
case IBMCAM_MODEL_4:
		ibmcam_veio(uvd, 0, 0x0000, 0x010c);	/* Stop the camera */

		ibmcam_model2_Packet1(uvd, 0x0030, 0x0004);

		ibmcam_veio(uvd, 0, 0x0080, 0x0100);	/* LED Off */
		ibmcam_veio(uvd, 0, 0x0020, 0x0111);
		ibmcam_veio(uvd, 0, 0x00a0, 0x0111);

		ibmcam_model2_Packet1(uvd, 0x0030, 0x0002);

		ibmcam_veio(uvd, 0, 0x0020, 0x0111);
		ibmcam_veio(uvd, 0, 0x0000, 0x0112);
		break;
	case IBMCAM_MODEL_3:
#if 1
		ibmcam_veio(uvd, 0, 0x0000, 0x010c);

		/* Here we are supposed to select video interface alt. setting 0 */
		ibmcam_veio(uvd, 0, 0x0006, 0x012c);

		ibmcam_model3_Packet1(uvd, 0x0046, 0x0000);

		ibmcam_veio(uvd, 1, 0x0000, 0x0116);
		ibmcam_veio(uvd, 0, 0x0064, 0x0116);
		ibmcam_veio(uvd, 1, 0x0000, 0x0115);
		ibmcam_veio(uvd, 0, 0x0003, 0x0115);
		ibmcam_veio(uvd, 0, 0x0008, 0x0123);
		ibmcam_veio(uvd, 0, 0x0000, 0x0117);
		ibmcam_veio(uvd, 0, 0x0000, 0x0112);
		ibmcam_veio(uvd, 0, 0x0080, 0x0100);
		IBMCAM_T(uvd)->initialized = 0;
#endif
		break;
	} /* switch */
}