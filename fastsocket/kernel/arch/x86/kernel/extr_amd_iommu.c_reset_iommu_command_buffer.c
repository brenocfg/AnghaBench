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
struct amd_iommu {int reset_in_progress; } ;

/* Variables and functions */
 int /*<<< orphan*/  amd_iommu_reset_cmd_buffer (struct amd_iommu*) ; 
 int /*<<< orphan*/  flush_all_devices_for_iommu (struct amd_iommu*) ; 
 int /*<<< orphan*/  flush_all_domains_on_iommu (struct amd_iommu*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static void reset_iommu_command_buffer(struct amd_iommu *iommu)
{
	pr_err("AMD-Vi: Resetting IOMMU command buffer\n");

	if (iommu->reset_in_progress)
		panic("AMD-Vi: ILLEGAL_COMMAND_ERROR while resetting command buffer\n");

	iommu->reset_in_progress = true;

	amd_iommu_reset_cmd_buffer(iommu);
	flush_all_devices_for_iommu(iommu);
	flush_all_domains_on_iommu(iommu);

	iommu->reset_in_progress = false;
}