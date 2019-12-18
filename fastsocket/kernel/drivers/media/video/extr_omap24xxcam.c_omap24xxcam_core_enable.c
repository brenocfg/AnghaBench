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
struct omap24xxcam_device {int /*<<< orphan*/  cc_ctrl; scalar_t__ mmio_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  CC_CTRL ; 
 scalar_t__ CC_REG_OFFSET ; 
 int /*<<< orphan*/  omap24xxcam_reg_out (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void omap24xxcam_core_enable(const struct omap24xxcam_device *cam)
{

	omap24xxcam_reg_out(cam->mmio_base + CC_REG_OFFSET, CC_CTRL,
			    cam->cc_ctrl);
}