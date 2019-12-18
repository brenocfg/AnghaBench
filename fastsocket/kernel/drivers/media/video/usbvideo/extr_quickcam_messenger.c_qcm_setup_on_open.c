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
struct TYPE_2__ {int /*<<< orphan*/  whiteness; int /*<<< orphan*/  brightness; int /*<<< orphan*/  contrast; int /*<<< orphan*/  colour; int /*<<< orphan*/  hue; } ;
struct uvd {TYPE_1__ vpic; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_RET (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qcm_camera_on (struct uvd*) ; 
 int /*<<< orphan*/  qcm_sensor_set_exposure (struct uvd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qcm_sensor_set_gains (struct uvd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qcm_sensor_set_shutter (struct uvd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qcm_set_camera_size (struct uvd*) ; 

__attribute__((used)) static int qcm_setup_on_open(struct uvd *uvd)
{
	int ret;

	CHECK_RET(ret, qcm_sensor_set_gains(uvd, uvd->vpic.hue,
				uvd->vpic.colour, uvd->vpic.contrast));
	CHECK_RET(ret, qcm_sensor_set_exposure(uvd, uvd->vpic.brightness));
	CHECK_RET(ret, qcm_sensor_set_shutter(uvd, uvd->vpic.whiteness));
	CHECK_RET(ret, qcm_set_camera_size(uvd));
	CHECK_RET(ret, qcm_camera_on(uvd));
	return 0;
}