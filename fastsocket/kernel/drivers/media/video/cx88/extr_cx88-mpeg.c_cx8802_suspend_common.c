#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int dummy; } ;
struct cx88_core {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int disabled; } ;
struct TYPE_3__ {int /*<<< orphan*/  timeout; int /*<<< orphan*/  active; } ;
struct cx8802_dev {TYPE_2__ state; struct cx88_core* core; int /*<<< orphan*/  slock; TYPE_1__ mpegq; } ;
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 int /*<<< orphan*/  cx8802_stop_dma (struct cx8802_dev*) ; 
 int /*<<< orphan*/  cx88_shutdown (struct cx88_core*) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintk (int,char*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_choose_state (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct cx8802_dev* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_save_state (struct pci_dev*) ; 
 scalar_t__ pci_set_power_state (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cx8802_suspend_common(struct pci_dev *pci_dev, pm_message_t state)
{
	struct cx8802_dev *dev = pci_get_drvdata(pci_dev);
	struct cx88_core *core = dev->core;

	/* stop mpeg dma */
	spin_lock(&dev->slock);
	if (!list_empty(&dev->mpegq.active)) {
		dprintk( 2, "suspend\n" );
		printk("%s: suspend mpeg\n", core->name);
		cx8802_stop_dma(dev);
		del_timer(&dev->mpegq.timeout);
	}
	spin_unlock(&dev->slock);

	/* FIXME -- shutdown device */
	cx88_shutdown(dev->core);

	pci_save_state(pci_dev);
	if (0 != pci_set_power_state(pci_dev, pci_choose_state(pci_dev, state))) {
		pci_disable_device(pci_dev);
		dev->state.disabled = 1;
	}
	return 0;
}