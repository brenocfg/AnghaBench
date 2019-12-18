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
struct omap24xxcam_device {scalar_t__ mmio_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  CC_CTRL_DMA ; 
 int CC_CTRL_DMA_EN ; 
 int /*<<< orphan*/  CC_IRQENABLE ; 
 int CC_IRQENABLE_FIFO_OF_IRQ ; 
 int CC_IRQENABLE_FSC_ERR_IRQ ; 
 int CC_IRQENABLE_FW_ERR_IRQ ; 
 int CC_IRQENABLE_SSC_ERR_IRQ ; 
 scalar_t__ CC_REG_OFFSET ; 
 int /*<<< orphan*/  CC_SYSCONFIG ; 
 int CC_SYSCONFIG_AUTOIDLE ; 
 int DMA_THRESHOLD ; 
 int /*<<< orphan*/  omap24xxcam_reg_out (scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void omap24xxcam_core_hwinit(const struct omap24xxcam_device *cam)
{
	/*
	 * Setting the camera core AUTOIDLE bit causes problems with frame
	 * synchronization, so we will clear the AUTOIDLE bit instead.
	 */
	omap24xxcam_reg_out(cam->mmio_base + CC_REG_OFFSET, CC_SYSCONFIG,
			    CC_SYSCONFIG_AUTOIDLE);

	/* program the camera interface DMA packet size */
	omap24xxcam_reg_out(cam->mmio_base + CC_REG_OFFSET, CC_CTRL_DMA,
			    CC_CTRL_DMA_EN | (DMA_THRESHOLD / 4 - 1));

	/* enable camera core error interrupts */
	omap24xxcam_reg_out(cam->mmio_base + CC_REG_OFFSET, CC_IRQENABLE,
			    CC_IRQENABLE_FW_ERR_IRQ
			    | CC_IRQENABLE_FSC_ERR_IRQ
			    | CC_IRQENABLE_SSC_ERR_IRQ
			    | CC_IRQENABLE_FIFO_OF_IRQ);
}