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
struct soc_camera_host {struct mx1_camera_dev* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct soc_camera_device {int /*<<< orphan*/  devnum; TYPE_1__ dev; } ;
struct mx1_camera_dev {struct soc_camera_device* icd; int /*<<< orphan*/  dma_chan; scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ CSICR1 ; 
 unsigned int CSI_IRQ_MASK ; 
 unsigned int __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writel (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_dma_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mx1_camera_deactivate (struct mx1_camera_dev*) ; 
 struct soc_camera_host* to_soc_camera_host (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mx1_camera_remove_device(struct soc_camera_device *icd)
{
	struct soc_camera_host *ici = to_soc_camera_host(icd->dev.parent);
	struct mx1_camera_dev *pcdev = ici->priv;
	unsigned int csicr1;

	BUG_ON(icd != pcdev->icd);

	/* disable interrupts */
	csicr1 = __raw_readl(pcdev->base + CSICR1) & ~CSI_IRQ_MASK;
	__raw_writel(csicr1, pcdev->base + CSICR1);

	/* Stop DMA engine */
	imx_dma_disable(pcdev->dma_chan);

	dev_info(icd->dev.parent, "MX1 Camera driver detached from camera %d\n",
		 icd->devnum);

	mx1_camera_deactivate(pcdev);

	pcdev->icd = NULL;
}