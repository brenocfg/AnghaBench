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
 int /*<<< orphan*/  INC_STATS_COUNTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  domain_flush_single ; 
 int /*<<< orphan*/  iommu_queue_inv_iommu_pages (struct amd_iommu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void iommu_flush_tlb(struct amd_iommu *iommu, u16 domid)
{
	u64 address = CMD_INV_IOMMU_ALL_PAGES_ADDRESS;

	INC_STATS_COUNTER(domain_flush_single);

	iommu_queue_inv_iommu_pages(iommu, address, domid, 0, 1);
}