#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int dummy; } ;
struct jmb38x_ms_host {int /*<<< orphan*/  lock; TYPE_1__* req; scalar_t__ addr; int /*<<< orphan*/  notify; } ;
struct jmb38x_ms {int host_cnt; TYPE_3__** hosts; TYPE_2__* pdev; } ;
struct TYPE_9__ {int /*<<< orphan*/  request; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  error; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETIME ; 
 scalar_t__ INT_SIGNAL_ENABLE ; 
 scalar_t__ INT_STATUS_ENABLE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  jmb38x_ms_complete_cmd (TYPE_3__*,int) ; 
 int /*<<< orphan*/  jmb38x_ms_dummy_submit ; 
 int /*<<< orphan*/  jmb38x_ms_free_host (TYPE_3__*) ; 
 int /*<<< orphan*/  kfree (struct jmb38x_ms*) ; 
 struct jmb38x_ms_host* memstick_priv (TYPE_3__*) ; 
 int /*<<< orphan*/  memstick_remove_host (TYPE_3__*) ; 
 int /*<<< orphan*/  mmiowb () ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct jmb38x_ms* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void jmb38x_ms_remove(struct pci_dev *dev)
{
	struct jmb38x_ms *jm = pci_get_drvdata(dev);
	struct jmb38x_ms_host *host;
	int cnt;
	unsigned long flags;

	for (cnt = 0; cnt < jm->host_cnt; ++cnt) {
		if (!jm->hosts[cnt])
			break;

		host = memstick_priv(jm->hosts[cnt]);

		jm->hosts[cnt]->request = jmb38x_ms_dummy_submit;
		tasklet_kill(&host->notify);
		writel(0, host->addr + INT_SIGNAL_ENABLE);
		writel(0, host->addr + INT_STATUS_ENABLE);
		mmiowb();
		dev_dbg(&jm->pdev->dev, "interrupts off\n");
		spin_lock_irqsave(&host->lock, flags);
		if (host->req) {
			host->req->error = -ETIME;
			jmb38x_ms_complete_cmd(jm->hosts[cnt], 1);
		}
		spin_unlock_irqrestore(&host->lock, flags);

		memstick_remove_host(jm->hosts[cnt]);
		dev_dbg(&jm->pdev->dev, "host removed\n");

		jmb38x_ms_free_host(jm->hosts[cnt]);
	}

	pci_set_drvdata(dev, NULL);
	pci_release_regions(dev);
	pci_disable_device(dev);
	kfree(jm);
}