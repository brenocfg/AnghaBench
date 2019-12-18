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
struct fhci_hcd {void* dfs_irq_stat; void* dfs_regs; int /*<<< orphan*/  dfs_root; } ;
struct device {int dummy; } ;
struct TYPE_3__ {struct device* controller; } ;
struct TYPE_4__ {TYPE_1__ self; } ;

/* Variables and functions */
 int S_IFREG ; 
 int S_IRUGO ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  debugfs_create_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct fhci_hcd*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  fhci_dfs_irq_stat_fops ; 
 int /*<<< orphan*/  fhci_dfs_regs_fops ; 
 TYPE_2__* fhci_to_hcd (struct fhci_hcd*) ; 
 int /*<<< orphan*/  usb_debug_root ; 

void fhci_dfs_create(struct fhci_hcd *fhci)
{
	struct device *dev = fhci_to_hcd(fhci)->self.controller;

	fhci->dfs_root = debugfs_create_dir(dev_name(dev), usb_debug_root);
	if (!fhci->dfs_root) {
		WARN_ON(1);
		return;
	}

	fhci->dfs_regs = debugfs_create_file("regs", S_IFREG | S_IRUGO,
		fhci->dfs_root, fhci, &fhci_dfs_regs_fops);

	fhci->dfs_irq_stat = debugfs_create_file("irq_stat",
		S_IFREG | S_IRUGO, fhci->dfs_root, fhci,
		&fhci_dfs_irq_stat_fops);

	WARN_ON(!fhci->dfs_regs || !fhci->dfs_irq_stat);
}