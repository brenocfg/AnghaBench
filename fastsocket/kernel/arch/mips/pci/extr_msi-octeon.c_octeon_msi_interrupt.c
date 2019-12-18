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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {scalar_t__ action; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_NPI_NPI_MSI_RCV ; 
 int /*<<< orphan*/  CVMX_PEXP_NPEI_MSI_RCV0 ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ OCTEON_DMA_BAR_TYPE_PCIE ; 
 int /*<<< orphan*/  OCTEON_FEATURE_PCIE ; 
 int OCTEON_IRQ_MSI_BIT0 ; 
 int /*<<< orphan*/  cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,unsigned long long) ; 
 int /*<<< orphan*/  do_IRQ (int) ; 
 int fls64 (int /*<<< orphan*/ ) ; 
 TYPE_1__* irq_desc ; 
 scalar_t__ octeon_dma_bar_type ; 
 scalar_t__ octeon_has_feature (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static irqreturn_t octeon_msi_interrupt(int cpl, void *dev_id)
{
	uint64_t msi_bits;
	int irq;

	if (octeon_dma_bar_type == OCTEON_DMA_BAR_TYPE_PCIE)
		msi_bits = cvmx_read_csr(CVMX_PEXP_NPEI_MSI_RCV0);
	else
		msi_bits = cvmx_read_csr(CVMX_NPI_NPI_MSI_RCV);
	irq = fls64(msi_bits);
	if (irq) {
		irq += OCTEON_IRQ_MSI_BIT0 - 1;
		if (irq_desc[irq].action) {
			do_IRQ(irq);
			return IRQ_HANDLED;
		} else {
			pr_err("Spurious MSI interrupt %d\n", irq);
			if (octeon_has_feature(OCTEON_FEATURE_PCIE)) {
				/* These chips have PCIe */
				cvmx_write_csr(CVMX_PEXP_NPEI_MSI_RCV0,
					       1ull << (irq -
							OCTEON_IRQ_MSI_BIT0));
			} else {
				/* These chips have PCI */
				cvmx_write_csr(CVMX_NPI_NPI_MSI_RCV,
					       1ull << (irq -
							OCTEON_IRQ_MSI_BIT0));
			}
		}
	}
	return IRQ_NONE;
}