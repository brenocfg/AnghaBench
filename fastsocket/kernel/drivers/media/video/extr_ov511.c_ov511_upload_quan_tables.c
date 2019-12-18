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
struct usb_ov511 {int dummy; } ;

/* Variables and functions */
 scalar_t__ ENABLE_UV_QUANTABLE ; 
 scalar_t__ ENABLE_Y_QUANTABLE ; 
 int OV511_QUANTABLESIZE ; 
 int /*<<< orphan*/  PDEBUG (int,char*) ; 
 int R511_COMP_LUT_BEGIN ; 
 int reg_w (struct usb_ov511*,int,unsigned char) ; 
 unsigned char* uvQuanTable511 ; 
 unsigned char* yQuanTable511 ; 

__attribute__((used)) static int
ov511_upload_quan_tables(struct usb_ov511 *ov)
{
	unsigned char *pYTable = yQuanTable511;
	unsigned char *pUVTable = uvQuanTable511;
	unsigned char val0, val1;
	int i, rc, reg = R511_COMP_LUT_BEGIN;

	PDEBUG(4, "Uploading quantization tables");

	for (i = 0; i < OV511_QUANTABLESIZE / 2; i++) {
		if (ENABLE_Y_QUANTABLE)	{
			val0 = *pYTable++;
			val1 = *pYTable++;
			val0 &= 0x0f;
			val1 &= 0x0f;
			val0 |= val1 << 4;
			rc = reg_w(ov, reg, val0);
			if (rc < 0)
				return rc;
		}

		if (ENABLE_UV_QUANTABLE) {
			val0 = *pUVTable++;
			val1 = *pUVTable++;
			val0 &= 0x0f;
			val1 &= 0x0f;
			val0 |= val1 << 4;
			rc = reg_w(ov, reg + OV511_QUANTABLESIZE/2, val0);
			if (rc < 0)
				return rc;
		}

		reg++;
	}

	return 0;
}