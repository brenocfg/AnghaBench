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
struct pci_dev {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;
struct netxen_legacy_intr_set {int /*<<< orphan*/  pci_int_reg; int /*<<< orphan*/  tgt_mask_reg; int /*<<< orphan*/  tgt_status_reg; int /*<<< orphan*/  int_vec_bit; } ;
struct TYPE_3__ {scalar_t__ revision_id; size_t pci_func; } ;
struct netxen_adapter {int max_sds_rings; int flags; TYPE_2__* msix_entries; TYPE_1__ ahw; void* tgt_status_reg; scalar_t__ rss_supported; scalar_t__ msix_supported; void* crb_int_state_reg; void* isr_int_vec; void* pci_int_reg; void* tgt_mask_reg; int /*<<< orphan*/  int_vec_bit; struct pci_dev* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  vector; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRB_INT_VECTOR ; 
 int /*<<< orphan*/  ISR_INT_STATE_REG ; 
 int /*<<< orphan*/  ISR_INT_VECTOR ; 
 scalar_t__ MSIX_ENTRIES_PER_ADAPTER ; 
 int NETXEN_NIC_MSIX_ENABLED ; 
 int NETXEN_NIC_MSI_ENABLED ; 
 scalar_t__ NX_P3_B0 ; 
 scalar_t__ NX_P3_B1 ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 struct netxen_legacy_intr_set* legacy_intr ; 
 int /*<<< orphan*/ * msi_tgt_status ; 
 void* netxen_get_ioaddr (struct netxen_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netxen_init_msix_entries (struct netxen_adapter*,int) ; 
 int /*<<< orphan*/  netxen_set_msix_bit (struct pci_dev*,int) ; 
 scalar_t__ num_online_cpus () ; 
 int /*<<< orphan*/  pci_disable_msix (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_enable_msi (struct pci_dev*) ; 
 int pci_enable_msix (struct pci_dev*,TYPE_2__*,int) ; 
 scalar_t__ use_msi ; 

__attribute__((used)) static void
netxen_setup_intr(struct netxen_adapter *adapter)
{
	struct netxen_legacy_intr_set *legacy_intrp;
	struct pci_dev *pdev = adapter->pdev;
	int err, num_msix;

	if (adapter->rss_supported) {
		num_msix = (num_online_cpus() >= MSIX_ENTRIES_PER_ADAPTER) ?
			MSIX_ENTRIES_PER_ADAPTER : 2;
	} else
		num_msix = 1;

	adapter->max_sds_rings = 1;

	adapter->flags &= ~(NETXEN_NIC_MSI_ENABLED | NETXEN_NIC_MSIX_ENABLED);

	if (adapter->ahw.revision_id >= NX_P3_B0)
		legacy_intrp = &legacy_intr[adapter->ahw.pci_func];
	else
		legacy_intrp = &legacy_intr[0];

	adapter->int_vec_bit = legacy_intrp->int_vec_bit;
	adapter->tgt_status_reg = netxen_get_ioaddr(adapter,
			legacy_intrp->tgt_status_reg);
	adapter->tgt_mask_reg = netxen_get_ioaddr(adapter,
			legacy_intrp->tgt_mask_reg);
	adapter->pci_int_reg = netxen_get_ioaddr(adapter,
			legacy_intrp->pci_int_reg);
	adapter->isr_int_vec = netxen_get_ioaddr(adapter, ISR_INT_VECTOR);

	if (adapter->ahw.revision_id >= NX_P3_B1)
		adapter->crb_int_state_reg = netxen_get_ioaddr(adapter,
			ISR_INT_STATE_REG);
	else
		adapter->crb_int_state_reg = netxen_get_ioaddr(adapter,
			CRB_INT_VECTOR);

	netxen_set_msix_bit(pdev, 0);

	if (adapter->msix_supported) {

		netxen_init_msix_entries(adapter, num_msix);
		err = pci_enable_msix(pdev, adapter->msix_entries, num_msix);
		if (err == 0) {
			adapter->flags |= NETXEN_NIC_MSIX_ENABLED;
			netxen_set_msix_bit(pdev, 1);

			if (adapter->rss_supported)
				adapter->max_sds_rings = num_msix;

			dev_info(&pdev->dev, "using msi-x interrupts\n");
			return;
		}

		if (err > 0)
			pci_disable_msix(pdev);

		/* fall through for msi */
	}

	if (use_msi && !pci_enable_msi(pdev)) {
		adapter->flags |= NETXEN_NIC_MSI_ENABLED;
		adapter->tgt_status_reg = netxen_get_ioaddr(adapter,
				msi_tgt_status[adapter->ahw.pci_func]);
		dev_info(&pdev->dev, "using msi interrupts\n");
		adapter->msix_entries[0].vector = pdev->irq;
		return;
	}

	dev_info(&pdev->dev, "using legacy interrupts\n");
	adapter->msix_entries[0].vector = pdev->irq;
}