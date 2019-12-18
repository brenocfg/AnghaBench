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
struct soc_camera_host {struct mx3_camera_dev* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct soc_camera_device {int /*<<< orphan*/  devnum; TYPE_1__ dev; } ;
struct mx3_camera_dev {struct soc_camera_device* icd; int /*<<< orphan*/  clk; struct idmac_channel** idmac_channel; } ;
struct idmac_channel {int /*<<< orphan*/  dma_chan; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_release_channel (int /*<<< orphan*/ *) ; 
 struct soc_camera_host* to_soc_camera_host (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mx3_camera_remove_device(struct soc_camera_device *icd)
{
	struct soc_camera_host *ici = to_soc_camera_host(icd->dev.parent);
	struct mx3_camera_dev *mx3_cam = ici->priv;
	struct idmac_channel **ichan = &mx3_cam->idmac_channel[0];

	BUG_ON(icd != mx3_cam->icd);

	if (*ichan) {
		dma_release_channel(&(*ichan)->dma_chan);
		*ichan = NULL;
	}

	clk_disable(mx3_cam->clk);

	mx3_cam->icd = NULL;

	dev_info(icd->dev.parent, "MX3 Camera driver detached from camera %d\n",
		 icd->devnum);
}