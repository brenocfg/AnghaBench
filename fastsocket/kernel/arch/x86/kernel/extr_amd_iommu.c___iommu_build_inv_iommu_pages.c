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
struct iommu_cmd {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_INV_IOMMU_PAGES ; 
 int /*<<< orphan*/  CMD_INV_IOMMU_PAGES_PDE_MASK ; 
 int /*<<< orphan*/  CMD_INV_IOMMU_PAGES_SIZE_MASK ; 
 int /*<<< orphan*/  CMD_SET_TYPE (struct iommu_cmd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_MASK ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct iommu_cmd*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __iommu_build_inv_iommu_pages(struct iommu_cmd *cmd, u64 address,
					  u16 domid, int pde, int s)
{
	memset(cmd, 0, sizeof(*cmd));
	address &= PAGE_MASK;
	CMD_SET_TYPE(cmd, CMD_INV_IOMMU_PAGES);
	cmd->data[1] |= domid;
	cmd->data[2] = lower_32_bits(address);
	cmd->data[3] = upper_32_bits(address);
	if (s) /* size bit - we flush more than one 4kb page */
		cmd->data[2] |= CMD_INV_IOMMU_PAGES_SIZE_MASK;
	if (pde) /* PDE bit - we wan't flush everything not only the PTEs */
		cmd->data[2] |= CMD_INV_IOMMU_PAGES_PDE_MASK;
}