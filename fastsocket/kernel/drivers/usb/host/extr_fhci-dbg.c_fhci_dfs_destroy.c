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
struct fhci_hcd {scalar_t__ dfs_root; scalar_t__ dfs_regs; scalar_t__ dfs_irq_stat; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove (scalar_t__) ; 

void fhci_dfs_destroy(struct fhci_hcd *fhci)
{
	if (!fhci->dfs_root)
		return;

	if (fhci->dfs_irq_stat)
		debugfs_remove(fhci->dfs_irq_stat);

	if (fhci->dfs_regs)
		debugfs_remove(fhci->dfs_regs);

	debugfs_remove(fhci->dfs_root);
}