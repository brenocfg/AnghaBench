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
struct uvd {int videosize; } ;

/* Variables and functions */
 scalar_t__ CAMERA_IS_OPERATIONAL (struct uvd*) ; 
 int EFAULT ; 
#define  VIDEOSIZE_176x144 131 
#define  VIDEOSIZE_320x240 130 
#define  VIDEOSIZE_352x240 129 
#define  VIDEOSIZE_352x288 128 
 int /*<<< orphan*/  ibmcam_veio (struct uvd*,int,int,int) ; 

__attribute__((used)) static int ibmcam_model2_setup(struct uvd *uvd)
{
	ibmcam_veio(uvd, 0, 0x0000, 0x0100);	/* LED on */
	ibmcam_veio(uvd, 1, 0x0000, 0x0116);
	ibmcam_veio(uvd, 0, 0x0060, 0x0116);
	ibmcam_veio(uvd, 0, 0x0002, 0x0112);
	ibmcam_veio(uvd, 0, 0x00bc, 0x012c);
	ibmcam_veio(uvd, 0, 0x0008, 0x012b);
	ibmcam_veio(uvd, 0, 0x0000, 0x0108);
	ibmcam_veio(uvd, 0, 0x0001, 0x0133);
	ibmcam_veio(uvd, 0, 0x0001, 0x0102);
	switch (uvd->videosize) {
	case VIDEOSIZE_176x144:
		ibmcam_veio(uvd, 0, 0x002c, 0x0103);	/* All except 320x240 */
		ibmcam_veio(uvd, 0, 0x0000, 0x0104);	/* Same */
		ibmcam_veio(uvd, 0, 0x0024, 0x0105);	/* 176x144, 352x288 */
		ibmcam_veio(uvd, 0, 0x00b9, 0x010a);	/* Unique to this mode */
		ibmcam_veio(uvd, 0, 0x0038, 0x0119);	/* Unique to this mode */
		ibmcam_veio(uvd, 0, 0x0003, 0x0106);	/* Same */
		ibmcam_veio(uvd, 0, 0x0090, 0x0107);	/* Unique to every mode*/
		break;
	case VIDEOSIZE_320x240:
		ibmcam_veio(uvd, 0, 0x0028, 0x0103);	/* Unique to this mode */
		ibmcam_veio(uvd, 0, 0x0000, 0x0104);	/* Same */
		ibmcam_veio(uvd, 0, 0x001e, 0x0105);	/* 320x240, 352x240 */
		ibmcam_veio(uvd, 0, 0x0039, 0x010a);	/* All except 176x144 */
		ibmcam_veio(uvd, 0, 0x0070, 0x0119);	/* All except 176x144 */
		ibmcam_veio(uvd, 0, 0x0003, 0x0106);	/* Same */
		ibmcam_veio(uvd, 0, 0x0098, 0x0107);	/* Unique to every mode*/
		break;
	case VIDEOSIZE_352x240:
		ibmcam_veio(uvd, 0, 0x002c, 0x0103);	/* All except 320x240 */
		ibmcam_veio(uvd, 0, 0x0000, 0x0104);	/* Same */
		ibmcam_veio(uvd, 0, 0x001e, 0x0105);	/* 320x240, 352x240 */
		ibmcam_veio(uvd, 0, 0x0039, 0x010a);	/* All except 176x144 */
		ibmcam_veio(uvd, 0, 0x0070, 0x0119);	/* All except 176x144 */
		ibmcam_veio(uvd, 0, 0x0003, 0x0106);	/* Same */
		ibmcam_veio(uvd, 0, 0x00da, 0x0107);	/* Unique to every mode*/
		break;
	case VIDEOSIZE_352x288:
		ibmcam_veio(uvd, 0, 0x002c, 0x0103);	/* All except 320x240 */
		ibmcam_veio(uvd, 0, 0x0000, 0x0104);	/* Same */
		ibmcam_veio(uvd, 0, 0x0024, 0x0105);	/* 176x144, 352x288 */
		ibmcam_veio(uvd, 0, 0x0039, 0x010a);	/* All except 176x144 */
		ibmcam_veio(uvd, 0, 0x0070, 0x0119);	/* All except 176x144 */
		ibmcam_veio(uvd, 0, 0x0003, 0x0106);	/* Same */
		ibmcam_veio(uvd, 0, 0x00fe, 0x0107);	/* Unique to every mode*/
		break;
	}
	return (CAMERA_IS_OPERATIONAL(uvd) ? 0 : -EFAULT);
}