#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct soc_camera_host {TYPE_2__ v4l2_dev; struct sh_mobile_ceu_dev* priv; } ;
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;
struct soc_camera_device {int /*<<< orphan*/  devnum; TYPE_3__ dev; } ;
struct sh_mobile_ceu_dev {struct soc_camera_device* icd; int /*<<< orphan*/  lock; TYPE_1__* active; } ;
struct TYPE_4__ {int /*<<< orphan*/  done; int /*<<< orphan*/  state; int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CAPSR ; 
 int /*<<< orphan*/  CEIER ; 
 int /*<<< orphan*/  VIDEOBUF_ERROR ; 
 int /*<<< orphan*/  ceu_write (struct sh_mobile_ceu_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct soc_camera_host* to_soc_camera_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sh_mobile_ceu_remove_device(struct soc_camera_device *icd)
{
	struct soc_camera_host *ici = to_soc_camera_host(icd->dev.parent);
	struct sh_mobile_ceu_dev *pcdev = ici->priv;
	unsigned long flags;

	BUG_ON(icd != pcdev->icd);

	/* disable capture, disable interrupts */
	ceu_write(pcdev, CEIER, 0);
	ceu_write(pcdev, CAPSR, 1 << 16); /* reset */

	/* make sure active buffer is canceled */
	spin_lock_irqsave(&pcdev->lock, flags);
	if (pcdev->active) {
		list_del(&pcdev->active->queue);
		pcdev->active->state = VIDEOBUF_ERROR;
		wake_up_all(&pcdev->active->done);
		pcdev->active = NULL;
	}
	spin_unlock_irqrestore(&pcdev->lock, flags);

	pm_runtime_put_sync(ici->v4l2_dev.dev);

	dev_info(icd->dev.parent,
		 "SuperH Mobile CEU driver detached from camera %d\n",
		 icd->devnum);

	pcdev->icd = NULL;
}