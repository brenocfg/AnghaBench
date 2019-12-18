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
struct omap24xxcam_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  mmio_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_SYSCONFIG ; 
 int /*<<< orphan*/  CAM_SYSCONFIG_SOFTRESET ; 
 int /*<<< orphan*/  CAM_SYSSTATUS ; 
 int CAM_SYSSTATUS_RESETDONE ; 
 int RESET_TIMEOUT_NS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ndelay (int) ; 
 int omap24xxcam_reg_in (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap24xxcam_reg_out (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void omap24xxcam_poweron_reset(struct omap24xxcam_device *cam)
{
	int max_loop = RESET_TIMEOUT_NS;

	/* Reset whole camera subsystem */
	omap24xxcam_reg_out(cam->mmio_base,
			    CAM_SYSCONFIG,
			    CAM_SYSCONFIG_SOFTRESET);

	/* Wait till it's finished */
	while (!(omap24xxcam_reg_in(cam->mmio_base, CAM_SYSSTATUS)
		 & CAM_SYSSTATUS_RESETDONE)
	       && --max_loop) {
		ndelay(1);
	}

	if (!(omap24xxcam_reg_in(cam->mmio_base, CAM_SYSSTATUS)
	      & CAM_SYSSTATUS_RESETDONE))
		dev_err(cam->dev, "camera soft reset timeout\n");
}