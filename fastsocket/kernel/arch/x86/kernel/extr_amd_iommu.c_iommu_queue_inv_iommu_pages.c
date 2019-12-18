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
struct iommu_cmd {int dummy; } ;
struct amd_iommu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __iommu_build_inv_iommu_pages (struct iommu_cmd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int iommu_queue_command (struct amd_iommu*,struct iommu_cmd*) ; 

__attribute__((used)) static int iommu_queue_inv_iommu_pages(struct amd_iommu *iommu,
		u64 address, u16 domid, int pde, int s)
{
	struct iommu_cmd cmd;
	int ret;

	__iommu_build_inv_iommu_pages(&cmd, address, domid, pde, s);

	ret = iommu_queue_command(iommu, &cmd);

	return ret;
}