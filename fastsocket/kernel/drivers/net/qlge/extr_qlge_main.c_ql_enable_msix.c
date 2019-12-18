#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ql_adapter {int intr_count; int /*<<< orphan*/  ndev; int /*<<< orphan*/  flags; int /*<<< orphan*/  pdev; TYPE_1__* msi_x_entry; } ;
struct msix_entry {int dummy; } ;
struct TYPE_4__ {int entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 scalar_t__ LEG_IRQ ; 
 scalar_t__ MSIX_IRQ ; 
 scalar_t__ MSI_IRQ ; 
 int /*<<< orphan*/  QL_MSIX_ENABLED ; 
 int /*<<< orphan*/  QL_MSI_ENABLED ; 
 int /*<<< orphan*/  ifup ; 
 TYPE_1__* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  netif_info (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  netif_printk (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netif_warn (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pci_enable_msi (int /*<<< orphan*/ ) ; 
 int pci_enable_msix (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 scalar_t__ qlge_irq_type ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ql_enable_msix(struct ql_adapter *qdev)
{
	int i, err;

	/* Get the MSIX vectors. */
	if (qlge_irq_type == MSIX_IRQ) {
		/* Try to alloc space for the msix struct,
		 * if it fails then go to MSI/legacy.
		 */
		qdev->msi_x_entry = kcalloc(qdev->intr_count,
					    sizeof(struct msix_entry),
					    GFP_KERNEL);
		if (!qdev->msi_x_entry) {
			qlge_irq_type = MSI_IRQ;
			goto msi;
		}

		for (i = 0; i < qdev->intr_count; i++)
			qdev->msi_x_entry[i].entry = i;

		/* Loop to get our vectors.  We start with
		 * what we want and settle for what we get.
		 */
		do {
			err = pci_enable_msix(qdev->pdev,
				qdev->msi_x_entry, qdev->intr_count);
			if (err > 0)
				qdev->intr_count = err;
		} while (err > 0);

		if (err < 0) {
			kfree(qdev->msi_x_entry);
			qdev->msi_x_entry = NULL;
			netif_warn(qdev, ifup, qdev->ndev,
				   "MSI-X Enable failed, trying MSI.\n");
			qdev->intr_count = 1;
			qlge_irq_type = MSI_IRQ;
		} else if (err == 0) {
			set_bit(QL_MSIX_ENABLED, &qdev->flags);
			netif_info(qdev, ifup, qdev->ndev,
				   "MSI-X Enabled, got %d vectors.\n",
				   qdev->intr_count);
			return;
		}
	}
msi:
	qdev->intr_count = 1;
	if (qlge_irq_type == MSI_IRQ) {
		if (!pci_enable_msi(qdev->pdev)) {
			set_bit(QL_MSI_ENABLED, &qdev->flags);
			netif_info(qdev, ifup, qdev->ndev,
				   "Running with MSI interrupts.\n");
			return;
		}
	}
	qlge_irq_type = LEG_IRQ;
	netif_printk(qdev, ifup, KERN_DEBUG, qdev->ndev,
		     "Running with legacy interrupts.\n");
}