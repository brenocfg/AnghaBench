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
 int min (int,int) ; 
 int /*<<< orphan*/  qcm_stv_setb (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int qcm_sensor_set_exposure(struct uvd *uvd, int exposure)
{
	int ret;
	int formedval;

	/* calculation was from qc-usb-messenger driver */
	formedval = ( exposure >> 12 );

	/* max value for formedval is 14 */
	formedval = min(formedval, 14);

	CHECK_RET(ret, qcm_stv_setb(uvd->dev,
			0x143A, 0xF0 | formedval));
	CHECK_RET(ret, qcm_stv_setb(uvd->dev, 0x143F, 0x01));
	return 0;
}