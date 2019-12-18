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
typedef  int /*<<< orphan*/  u32 ;
struct qlcnic_legacy_intr_set {int /*<<< orphan*/  tgt_mask_reg; int /*<<< orphan*/  tgt_status_reg; int /*<<< orphan*/  int_vec_bit; } ;
struct qlcnic_hardware_context {size_t pci_func; int /*<<< orphan*/  int_vec_bit; } ;
struct qlcnic_adapter {TYPE_1__* msix_entries; void* crb_int_state_reg; void* isr_int_vec; void* tgt_mask_reg; void* tgt_status_reg; struct qlcnic_hardware_context* ahw; int /*<<< orphan*/  flags; struct pci_dev* pdev; } ;
struct pci_dev {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  vector; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ISR_INT_STATE_REG ; 
 int /*<<< orphan*/  ISR_INT_VECTOR ; 
 int /*<<< orphan*/  QLCNIC_MSI_ENABLED ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 struct qlcnic_legacy_intr_set* legacy_intr ; 
 int /*<<< orphan*/ * msi_tgt_status ; 
 int /*<<< orphan*/  pci_enable_msi (struct pci_dev*) ; 
 void* qlcnic_get_ioaddr (struct qlcnic_hardware_context*,int /*<<< orphan*/ ) ; 
 scalar_t__ qlcnic_use_msi ; 
 scalar_t__ qlcnic_use_msi_x ; 

__attribute__((used)) static int qlcnic_enable_msi_legacy(struct qlcnic_adapter *adapter)
{
	int err = 0;
	u32 offset, mask_reg;
	const struct qlcnic_legacy_intr_set *legacy_intrp;
	struct qlcnic_hardware_context *ahw = adapter->ahw;
	struct pci_dev *pdev = adapter->pdev;

	if (qlcnic_use_msi && !pci_enable_msi(pdev)) {
		adapter->flags |= QLCNIC_MSI_ENABLED;
		offset = msi_tgt_status[adapter->ahw->pci_func];
		adapter->tgt_status_reg = qlcnic_get_ioaddr(adapter->ahw,
							    offset);
		dev_info(&pdev->dev, "using msi interrupts\n");
		adapter->msix_entries[0].vector = pdev->irq;
		return err;
	}
	if (qlcnic_use_msi || qlcnic_use_msi_x)
		return -EOPNOTSUPP;

	legacy_intrp = &legacy_intr[adapter->ahw->pci_func];
	adapter->ahw->int_vec_bit = legacy_intrp->int_vec_bit;
	offset = legacy_intrp->tgt_status_reg;
	adapter->tgt_status_reg = qlcnic_get_ioaddr(ahw, offset);
	mask_reg = legacy_intrp->tgt_mask_reg;
	adapter->tgt_mask_reg = qlcnic_get_ioaddr(ahw, mask_reg);
	adapter->isr_int_vec = qlcnic_get_ioaddr(ahw, ISR_INT_VECTOR);
	adapter->crb_int_state_reg = qlcnic_get_ioaddr(ahw, ISR_INT_STATE_REG);
	dev_info(&pdev->dev, "using legacy interrupts\n");
	adapter->msix_entries[0].vector = pdev->irq;
	return err;
}