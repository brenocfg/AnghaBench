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
#define  VIDEOSIZE_128x96 130 
#define  VIDEOSIZE_176x144 129 
#define  VIDEOSIZE_352x288 128 
 int contrast_14 ; 
 int /*<<< orphan*/  ibmcam_PacketFormat2 (struct uvd*,int,int) ; 
 int /*<<< orphan*/  ibmcam_Packet_Format1 (struct uvd*,int,int) ; 
 int /*<<< orphan*/  ibmcam_veio (struct uvd*,int,int,int) ; 
 int light_27 ; 
 int lighting ; 
 int sharp_13 ; 

__attribute__((used)) static int ibmcam_model1_setup(struct uvd *uvd)
{
	const int ntries = 5;
	int i;

	ibmcam_veio(uvd, 1, 0x00, 0x0128);
	ibmcam_veio(uvd, 1, 0x00, 0x0100);
	ibmcam_veio(uvd, 0, 0x01, 0x0100);	/* LED On  */
	ibmcam_veio(uvd, 1, 0x00, 0x0100);
	ibmcam_veio(uvd, 0, 0x81, 0x0100);	/* LED Off */
	ibmcam_veio(uvd, 1, 0x00, 0x0100);
	ibmcam_veio(uvd, 0, 0x01, 0x0100);	/* LED On  */
	ibmcam_veio(uvd, 0, 0x01, 0x0108);

	ibmcam_veio(uvd, 0, 0x03, 0x0112);
	ibmcam_veio(uvd, 1, 0x00, 0x0115);
	ibmcam_veio(uvd, 0, 0x06, 0x0115);
	ibmcam_veio(uvd, 1, 0x00, 0x0116);
	ibmcam_veio(uvd, 0, 0x44, 0x0116);
	ibmcam_veio(uvd, 1, 0x00, 0x0116);
	ibmcam_veio(uvd, 0, 0x40, 0x0116);
	ibmcam_veio(uvd, 1, 0x00, 0x0115);
	ibmcam_veio(uvd, 0, 0x0e, 0x0115);
	ibmcam_veio(uvd, 0, 0x19, 0x012c);

	ibmcam_Packet_Format1(uvd, 0x00, 0x1e);
	ibmcam_Packet_Format1(uvd, 0x39, 0x0d);
	ibmcam_Packet_Format1(uvd, 0x39, 0x09);
	ibmcam_Packet_Format1(uvd, 0x3b, 0x00);
	ibmcam_Packet_Format1(uvd, 0x28, 0x22);
	ibmcam_Packet_Format1(uvd, light_27, 0);
	ibmcam_Packet_Format1(uvd, 0x2b, 0x1f);
	ibmcam_Packet_Format1(uvd, 0x39, 0x08);

	for (i=0; i < ntries; i++)
		ibmcam_Packet_Format1(uvd, 0x2c, 0x00);

	for (i=0; i < ntries; i++)
		ibmcam_Packet_Format1(uvd, 0x30, 0x14);

	ibmcam_PacketFormat2(uvd, 0x39, 0x02);
	ibmcam_PacketFormat2(uvd, 0x01, 0xe1);
	ibmcam_PacketFormat2(uvd, 0x02, 0xcd);
	ibmcam_PacketFormat2(uvd, 0x03, 0xcd);
	ibmcam_PacketFormat2(uvd, 0x04, 0xfa);
	ibmcam_PacketFormat2(uvd, 0x3f, 0xff);
	ibmcam_PacketFormat2(uvd, 0x39, 0x00);

	ibmcam_PacketFormat2(uvd, 0x39, 0x02);
	ibmcam_PacketFormat2(uvd, 0x0a, 0x37);
	ibmcam_PacketFormat2(uvd, 0x0b, 0xb8);
	ibmcam_PacketFormat2(uvd, 0x0c, 0xf3);
	ibmcam_PacketFormat2(uvd, 0x0d, 0xe3);
	ibmcam_PacketFormat2(uvd, 0x0e, 0x0d);
	ibmcam_PacketFormat2(uvd, 0x0f, 0xf2);
	ibmcam_PacketFormat2(uvd, 0x10, 0xd5);
	ibmcam_PacketFormat2(uvd, 0x11, 0xba);
	ibmcam_PacketFormat2(uvd, 0x12, 0x53);
	ibmcam_PacketFormat2(uvd, 0x3f, 0xff);
	ibmcam_PacketFormat2(uvd, 0x39, 0x00);

	ibmcam_PacketFormat2(uvd, 0x39, 0x02);
	ibmcam_PacketFormat2(uvd, 0x16, 0x00);
	ibmcam_PacketFormat2(uvd, 0x17, 0x28);
	ibmcam_PacketFormat2(uvd, 0x18, 0x7d);
	ibmcam_PacketFormat2(uvd, 0x19, 0xbe);
	ibmcam_PacketFormat2(uvd, 0x3f, 0xff);
	ibmcam_PacketFormat2(uvd, 0x39, 0x00);

	for (i=0; i < ntries; i++)
		ibmcam_Packet_Format1(uvd, 0x00, 0x18);
	for (i=0; i < ntries; i++)
		ibmcam_Packet_Format1(uvd, 0x13, 0x18);
	for (i=0; i < ntries; i++)
		ibmcam_Packet_Format1(uvd, 0x14, 0x06);

	/* This is default brightness */
	for (i=0; i < ntries; i++)
		ibmcam_Packet_Format1(uvd, 0x31, 0x37);
	for (i=0; i < ntries; i++)
		ibmcam_Packet_Format1(uvd, 0x32, 0x46);
	for (i=0; i < ntries; i++)
		ibmcam_Packet_Format1(uvd, 0x33, 0x55);

	ibmcam_Packet_Format1(uvd, 0x2e, 0x04);
	for (i=0; i < ntries; i++)
		ibmcam_Packet_Format1(uvd, 0x2d, 0x04);
	for (i=0; i < ntries; i++)
		ibmcam_Packet_Format1(uvd, 0x29, 0x80);
	ibmcam_Packet_Format1(uvd, 0x2c, 0x01);
	ibmcam_Packet_Format1(uvd, 0x30, 0x17);
	ibmcam_Packet_Format1(uvd, 0x39, 0x08);
	for (i=0; i < ntries; i++)
		ibmcam_Packet_Format1(uvd, 0x34, 0x00);

	ibmcam_veio(uvd, 0, 0x00, 0x0101);
	ibmcam_veio(uvd, 0, 0x00, 0x010a);

	switch (uvd->videosize) {
	case VIDEOSIZE_128x96:
		ibmcam_veio(uvd, 0, 0x80, 0x0103);
		ibmcam_veio(uvd, 0, 0x60, 0x0105);
		ibmcam_veio(uvd, 0, 0x0c, 0x010b);
		ibmcam_veio(uvd, 0, 0x04, 0x011b);	/* Same everywhere */
		ibmcam_veio(uvd, 0, 0x0b, 0x011d);
		ibmcam_veio(uvd, 0, 0x00, 0x011e);	/* Same everywhere */
		ibmcam_veio(uvd, 0, 0x00, 0x0129);
		break;
	case VIDEOSIZE_176x144:
		ibmcam_veio(uvd, 0, 0xb0, 0x0103);
		ibmcam_veio(uvd, 0, 0x8f, 0x0105);
		ibmcam_veio(uvd, 0, 0x06, 0x010b);
		ibmcam_veio(uvd, 0, 0x04, 0x011b);	/* Same everywhere */
		ibmcam_veio(uvd, 0, 0x0d, 0x011d);
		ibmcam_veio(uvd, 0, 0x00, 0x011e);	/* Same everywhere */
		ibmcam_veio(uvd, 0, 0x03, 0x0129);
		break;
	case VIDEOSIZE_352x288:
		ibmcam_veio(uvd, 0, 0xb0, 0x0103);
		ibmcam_veio(uvd, 0, 0x90, 0x0105);
		ibmcam_veio(uvd, 0, 0x02, 0x010b);
		ibmcam_veio(uvd, 0, 0x04, 0x011b);	/* Same everywhere */
		ibmcam_veio(uvd, 0, 0x05, 0x011d);
		ibmcam_veio(uvd, 0, 0x00, 0x011e);	/* Same everywhere */
		ibmcam_veio(uvd, 0, 0x00, 0x0129);
		break;
	}

	ibmcam_veio(uvd, 0, 0xff, 0x012b);

	/* This is another brightness - don't know why */
	for (i=0; i < ntries; i++)
		ibmcam_Packet_Format1(uvd, 0x31, 0xc3);
	for (i=0; i < ntries; i++)
		ibmcam_Packet_Format1(uvd, 0x32, 0xd2);
	for (i=0; i < ntries; i++)
		ibmcam_Packet_Format1(uvd, 0x33, 0xe1);

	/* Default contrast */
	for (i=0; i < ntries; i++)
		ibmcam_Packet_Format1(uvd, contrast_14, 0x0a);

	/* Default sharpness */
	for (i=0; i < 2; i++)
		ibmcam_PacketFormat2(uvd, sharp_13, 0x1a);	/* Level 4 FIXME */

	/* Default lighting conditions */
	ibmcam_Packet_Format1(uvd, light_27, lighting); /* 0=Bright 2=Low */

	/* Assorted init */

	switch (uvd->videosize) {
	case VIDEOSIZE_128x96:
		ibmcam_Packet_Format1(uvd, 0x2b, 0x1e);
		ibmcam_veio(uvd, 0, 0xc9, 0x0119);	/* Same everywhere */
		ibmcam_veio(uvd, 0, 0x80, 0x0109);	/* Same everywhere */
		ibmcam_veio(uvd, 0, 0x36, 0x0102);
		ibmcam_veio(uvd, 0, 0x1a, 0x0104);
		ibmcam_veio(uvd, 0, 0x04, 0x011a);	/* Same everywhere */
		ibmcam_veio(uvd, 0, 0x2b, 0x011c);
		ibmcam_veio(uvd, 0, 0x23, 0x012a);	/* Same everywhere */
#if 0
		ibmcam_veio(uvd, 0, 0x00, 0x0106);
		ibmcam_veio(uvd, 0, 0x38, 0x0107);
#else
		ibmcam_veio(uvd, 0, 0x02, 0x0106);
		ibmcam_veio(uvd, 0, 0x2a, 0x0107);
#endif
		break;
	case VIDEOSIZE_176x144:
		ibmcam_Packet_Format1(uvd, 0x2b, 0x1e);
		ibmcam_veio(uvd, 0, 0xc9, 0x0119);	/* Same everywhere */
		ibmcam_veio(uvd, 0, 0x80, 0x0109);	/* Same everywhere */
		ibmcam_veio(uvd, 0, 0x04, 0x0102);
		ibmcam_veio(uvd, 0, 0x02, 0x0104);
		ibmcam_veio(uvd, 0, 0x04, 0x011a);	/* Same everywhere */
		ibmcam_veio(uvd, 0, 0x2b, 0x011c);
		ibmcam_veio(uvd, 0, 0x23, 0x012a);	/* Same everywhere */
		ibmcam_veio(uvd, 0, 0x01, 0x0106);
		ibmcam_veio(uvd, 0, 0xca, 0x0107);
		break;
	case VIDEOSIZE_352x288:
		ibmcam_Packet_Format1(uvd, 0x2b, 0x1f);
		ibmcam_veio(uvd, 0, 0xc9, 0x0119);	/* Same everywhere */
		ibmcam_veio(uvd, 0, 0x80, 0x0109);	/* Same everywhere */
		ibmcam_veio(uvd, 0, 0x08, 0x0102);
		ibmcam_veio(uvd, 0, 0x01, 0x0104);
		ibmcam_veio(uvd, 0, 0x04, 0x011a);	/* Same everywhere */
		ibmcam_veio(uvd, 0, 0x2f, 0x011c);
		ibmcam_veio(uvd, 0, 0x23, 0x012a);	/* Same everywhere */
		ibmcam_veio(uvd, 0, 0x03, 0x0106);
		ibmcam_veio(uvd, 0, 0xf6, 0x0107);
		break;
	}
	return (CAMERA_IS_OPERATIONAL(uvd) ? 0 : -EFAULT);
}