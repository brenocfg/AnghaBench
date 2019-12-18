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
struct uvd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_RET (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qcm_sensor_set_exposure (struct uvd*,int) ; 
 int /*<<< orphan*/  qcm_sensor_set_gains (struct uvd*,int,int,int) ; 

__attribute__((used)) static int qcm_sensor_setlevels(struct uvd *uvd, int brightness, int contrast,
					int hue, int colour)
{
	int ret;
	/* brightness is exposure, contrast is gain, colour is saturation */
	CHECK_RET(ret,
		qcm_sensor_set_exposure(uvd, brightness));
	CHECK_RET(ret, qcm_sensor_set_gains(uvd, hue, colour, contrast));

	return 0;
}