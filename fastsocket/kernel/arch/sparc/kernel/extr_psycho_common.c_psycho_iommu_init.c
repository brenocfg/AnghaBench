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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct pci_pbm_info {int /*<<< orphan*/  numa_node; scalar_t__ controller_regs; struct iommu* iommu; } ;
struct iommu {scalar_t__ iommu_control; scalar_t__ iommu_tsbbase; int /*<<< orphan*/  page_table; scalar_t__ iommu_ctxflush; scalar_t__ write_complete_reg; scalar_t__ iommu_tags; scalar_t__ iommu_flush; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ PSYCHO_IOMMU_CONTROL ; 
 int PSYCHO_IOMMU_CTRL_DENAB ; 
 int PSYCHO_IOMMU_CTRL_ENAB ; 
 int PSYCHO_IOMMU_CTRL_TBWSZ ; 
 int PSYCHO_IOMMU_CTRL_TSBSZ ; 
 scalar_t__ PSYCHO_IOMMU_FLUSH ; 
 scalar_t__ PSYCHO_IOMMU_TAG ; 
 scalar_t__ PSYCHO_IOMMU_TSBBASE ; 
 int PSYCHO_IOMMU_TSBSZ_128K ; 
 int PSYCHO_IOMMU_TSBSZ_64K ; 
 int __pa (int /*<<< orphan*/ ) ; 
 int iommu_table_init (struct iommu*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psycho_iommu_flush (struct pci_pbm_info*) ; 
 int upa_readq (scalar_t__) ; 
 int /*<<< orphan*/  upa_writeq (int,scalar_t__) ; 

int psycho_iommu_init(struct pci_pbm_info *pbm, int tsbsize,
		      u32 dvma_offset, u32 dma_mask,
		      unsigned long write_complete_offset)
{
	struct iommu *iommu = pbm->iommu;
	u64 control;
	int err;

	iommu->iommu_control  = pbm->controller_regs + PSYCHO_IOMMU_CONTROL;
	iommu->iommu_tsbbase  = pbm->controller_regs + PSYCHO_IOMMU_TSBBASE;
	iommu->iommu_flush    = pbm->controller_regs + PSYCHO_IOMMU_FLUSH;
	iommu->iommu_tags     = pbm->controller_regs + PSYCHO_IOMMU_TAG;
	iommu->write_complete_reg = (pbm->controller_regs +
				     write_complete_offset);

	iommu->iommu_ctxflush = 0;

	control = upa_readq(iommu->iommu_control);
	control |= PSYCHO_IOMMU_CTRL_DENAB;
	upa_writeq(control, iommu->iommu_control);

	psycho_iommu_flush(pbm);

	/* Leave diag mode enabled for full-flushing done in pci_iommu.c */
	err = iommu_table_init(iommu, tsbsize * 1024 * 8,
			       dvma_offset, dma_mask, pbm->numa_node);
	if (err)
		return err;

	upa_writeq(__pa(iommu->page_table), iommu->iommu_tsbbase);

	control = upa_readq(iommu->iommu_control);
	control &= ~(PSYCHO_IOMMU_CTRL_TSBSZ | PSYCHO_IOMMU_CTRL_TBWSZ);
	control |= PSYCHO_IOMMU_CTRL_ENAB;

	switch (tsbsize) {
	case 64:
		control |= PSYCHO_IOMMU_TSBSZ_64K;
		break;
	case 128:
		control |= PSYCHO_IOMMU_TSBSZ_128K;
		break;
	default:
		return -EINVAL;
	}

	upa_writeq(control, iommu->iommu_control);

	return 0;

}