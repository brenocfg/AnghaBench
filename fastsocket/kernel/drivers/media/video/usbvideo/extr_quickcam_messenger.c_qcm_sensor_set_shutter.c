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
struct uvd {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_RET (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qcm_stv_setb (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int qcm_sensor_set_shutter(struct uvd *uvd, int whiteness)
{
	int ret;
	/* some rescaling as done by the qc-usb-messenger code */
	if (whiteness > 0xC000)
		whiteness = 0xC000 + (whiteness & 0x3FFF)*8;

	CHECK_RET(ret, qcm_stv_setb(uvd->dev, 0x143D,
				(whiteness >> 8) & 0xFF));
	CHECK_RET(ret, qcm_stv_setb(uvd->dev, 0x143E,
				(whiteness >> 16) & 0x03));
	CHECK_RET(ret, qcm_stv_setb(uvd->dev, 0x143F, 0x01));

	return 0;
}