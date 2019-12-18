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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  dma; } ;
struct omap24xxcam_device {int /*<<< orphan*/  dev; TYPE_1__ sgdma; int /*<<< orphan*/  mmio_base; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_IRQSTATUS ; 
 int CAM_IRQSTATUS_CC_IRQ ; 
 int CAM_IRQSTATUS_DMA_IRQ0 ; 
 int CAM_IRQSTATUS_DMA_IRQ1 ; 
 int CAM_IRQSTATUS_DMA_IRQ2 ; 
 int CAM_IRQSTATUS_MMU_IRQ ; 
 int /*<<< orphan*/  IRQ_RETVAL (unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  omap24xxcam_core_isr (struct omap24xxcam_device*) ; 
 int /*<<< orphan*/  omap24xxcam_dma_isr (int /*<<< orphan*/ *) ; 
 int omap24xxcam_reg_in (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t omap24xxcam_isr(int irq, void *arg)
{
	struct omap24xxcam_device *cam = (struct omap24xxcam_device *)arg;
	u32 irqstatus;
	unsigned int irqhandled = 0;

	irqstatus = omap24xxcam_reg_in(cam->mmio_base, CAM_IRQSTATUS);

	if (irqstatus &
	    (CAM_IRQSTATUS_DMA_IRQ2 | CAM_IRQSTATUS_DMA_IRQ1
	     | CAM_IRQSTATUS_DMA_IRQ0)) {
		omap24xxcam_dma_isr(&cam->sgdma.dma);
		irqhandled = 1;
	}
	if (irqstatus & CAM_IRQSTATUS_CC_IRQ) {
		omap24xxcam_core_isr(cam);
		irqhandled = 1;
	}
	if (irqstatus & CAM_IRQSTATUS_MMU_IRQ)
		dev_err(cam->dev, "unhandled camera MMU interrupt!\n");

	return IRQ_RETVAL(irqhandled);
}