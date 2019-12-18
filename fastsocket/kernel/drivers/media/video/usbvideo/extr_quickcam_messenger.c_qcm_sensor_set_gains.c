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
typedef  int u16 ;
struct uvd {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_RET (int,int /*<<< orphan*/ ) ; 
 int max (int,int) ; 
 int /*<<< orphan*/  qcm_hsv2rgb (int,int,int,int*,int*,int*) ; 
 int /*<<< orphan*/  qcm_stv_setb (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int qcm_sensor_set_gains(struct uvd *uvd, u16 hue,
	u16 saturation, u16 value)
{
	int ret;
	u16 r=0,g=0,b=0;

	/* this code is based on qc-usb-messenger */
	qcm_hsv2rgb(hue, saturation, value, &r, &g, &b);

	r >>= 12;
	g >>= 12;
	b >>= 12;

	/* min val is 8 */
	r = max((u16) 8, r);
	g = max((u16) 8, g);
	b = max((u16) 8, b);

	r |= 0x30;
	g |= 0x30;
	b |= 0x30;

	/* set the r,g,b gain registers */
	CHECK_RET(ret, qcm_stv_setb(uvd->dev, 0x0509, r));
	CHECK_RET(ret, qcm_stv_setb(uvd->dev, 0x050A, g));
	CHECK_RET(ret, qcm_stv_setb(uvd->dev, 0x050B, b));

	/* doing as qc-usb did */
	CHECK_RET(ret, qcm_stv_setb(uvd->dev, 0x050C, 0x2A));
	CHECK_RET(ret, qcm_stv_setb(uvd->dev, 0x050D, 0x01));
	CHECK_RET(ret, qcm_stv_setb(uvd->dev, 0x143F, 0x01));

	return 0;
}