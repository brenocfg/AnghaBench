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
typedef  int /*<<< orphan*/  u16 ;
struct amd_iommu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_INV_IOMMU_ALL_PAGES_ADDRESS ; 
 int /*<<< orphan*/  PAGE_MASK ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 unsigned int iommu_num_pages (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_queue_inv_iommu_pages (struct amd_iommu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int iommu_flush_pages(struct amd_iommu *iommu, u16 domid,
		u64 address, size_t size)
{
	int s = 0;
	unsigned pages = iommu_num_pages(address, size, PAGE_SIZE);

	address &= PAGE_MASK;

	if (pages > 1) {
		/*
		 * If we have to flush more than one page, flush all
		 * TLB entries for this domain
		 */
		address = CMD_INV_IOMMU_ALL_PAGES_ADDRESS;
		s = 1;
	}

	iommu_queue_inv_iommu_pages(iommu, address, domid, 0, s);

	return 0;
}