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
typedef  int /*<<< orphan*/  u64 ;
struct pci_pbm_info {unsigned long controller_regs; } ;

/* Variables and functions */
 scalar_t__ PSYCHO_IOMMU_DATA ; 
 scalar_t__ PSYCHO_IOMMU_TAG ; 
 int /*<<< orphan*/  upa_readq (scalar_t__) ; 
 int /*<<< orphan*/  upa_writeq (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void psycho_record_iommu_tags_and_data(struct pci_pbm_info *pbm,
					      u64 *tag, u64 *data)
{
	int i;

	for (i = 0; i < 16; i++) {
		unsigned long base = pbm->controller_regs;
		unsigned long off = i * 8UL;

		tag[i] = upa_readq(base + PSYCHO_IOMMU_TAG+off);
		data[i] = upa_readq(base + PSYCHO_IOMMU_DATA+off);

		/* Now clear out the entry. */
		upa_writeq(0, base + PSYCHO_IOMMU_TAG + off);
		upa_writeq(0, base + PSYCHO_IOMMU_DATA + off);
	}
}