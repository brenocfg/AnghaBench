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
typedef  int u16 ;
struct pci_pbm_info {unsigned long pbm_regs; TYPE_1__* pci_bus; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  self; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  PCI_STATUS ; 
 int PCI_STATUS_PARITY ; 
 int PCI_STATUS_REC_MASTER_ABORT ; 
 int PCI_STATUS_REC_TARGET_ABORT ; 
 int PCI_STATUS_SIG_SYSTEM_ERROR ; 
 int PCI_STATUS_SIG_TARGET_ABORT ; 
 unsigned long SCHIZO_PCICTRL_BUS_UNUS ; 
 unsigned long SCHIZO_PCICTRL_DTO_ERR ; 
 unsigned long SCHIZO_PCICTRL_RTRY_ERR ; 
 unsigned long SCHIZO_PCICTRL_SBH_ERR ; 
 unsigned long SCHIZO_PCICTRL_SERR ; 
 unsigned long SCHIZO_PCICTRL_TTO_ERR ; 
 unsigned long SCHIZO_PCI_CTRL ; 
 int /*<<< orphan*/  pci_read_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,...) ; 
 unsigned long upa_readq (unsigned long) ; 
 int /*<<< orphan*/  upa_writeq (unsigned long,unsigned long) ; 

__attribute__((used)) static irqreturn_t schizo_pcierr_intr_other(struct pci_pbm_info *pbm)
{
	unsigned long csr_reg, csr, csr_error_bits;
	irqreturn_t ret = IRQ_NONE;
	u16 stat;

	csr_reg = pbm->pbm_regs + SCHIZO_PCI_CTRL;
	csr = upa_readq(csr_reg);
	csr_error_bits =
		csr & (SCHIZO_PCICTRL_BUS_UNUS |
		       SCHIZO_PCICTRL_TTO_ERR |
		       SCHIZO_PCICTRL_RTRY_ERR |
		       SCHIZO_PCICTRL_DTO_ERR |
		       SCHIZO_PCICTRL_SBH_ERR |
		       SCHIZO_PCICTRL_SERR);
	if (csr_error_bits) {
		/* Clear the errors.  */
		upa_writeq(csr, csr_reg);

		/* Log 'em.  */
		if (csr_error_bits & SCHIZO_PCICTRL_BUS_UNUS)
			printk("%s: Bus unusable error asserted.\n",
			       pbm->name);
		if (csr_error_bits & SCHIZO_PCICTRL_TTO_ERR)
			printk("%s: PCI TRDY# timeout error asserted.\n",
			       pbm->name);
		if (csr_error_bits & SCHIZO_PCICTRL_RTRY_ERR)
			printk("%s: PCI excessive retry error asserted.\n",
			       pbm->name);
		if (csr_error_bits & SCHIZO_PCICTRL_DTO_ERR)
			printk("%s: PCI discard timeout error asserted.\n",
			       pbm->name);
		if (csr_error_bits & SCHIZO_PCICTRL_SBH_ERR)
			printk("%s: PCI streaming byte hole error asserted.\n",
			       pbm->name);
		if (csr_error_bits & SCHIZO_PCICTRL_SERR)
			printk("%s: PCI SERR signal asserted.\n",
			       pbm->name);
		ret = IRQ_HANDLED;
	}
	pci_read_config_word(pbm->pci_bus->self, PCI_STATUS, &stat);
	if (stat & (PCI_STATUS_PARITY |
		    PCI_STATUS_SIG_TARGET_ABORT |
		    PCI_STATUS_REC_TARGET_ABORT |
		    PCI_STATUS_REC_MASTER_ABORT |
		    PCI_STATUS_SIG_SYSTEM_ERROR)) {
		printk("%s: PCI bus error, PCI_STATUS[%04x]\n",
		       pbm->name, stat);
		pci_write_config_word(pbm->pci_bus->self, PCI_STATUS, 0xffff);
		ret = IRQ_HANDLED;
	}
	return ret;
}