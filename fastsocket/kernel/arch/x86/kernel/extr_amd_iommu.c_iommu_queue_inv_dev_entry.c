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
typedef  int /*<<< orphan*/  u16 ;
struct iommu_cmd {int /*<<< orphan*/ * data; } ;
struct amd_iommu {int dummy; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CMD_INV_DEV_ENTRY ; 
 int /*<<< orphan*/  CMD_SET_TYPE (struct iommu_cmd*,int /*<<< orphan*/ ) ; 
 int iommu_queue_command (struct amd_iommu*,struct iommu_cmd*) ; 
 int /*<<< orphan*/  memset (struct iommu_cmd*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int iommu_queue_inv_dev_entry(struct amd_iommu *iommu, u16 devid)
{
	struct iommu_cmd cmd;
	int ret;

	BUG_ON(iommu == NULL);

	memset(&cmd, 0, sizeof(cmd));
	CMD_SET_TYPE(&cmd, CMD_INV_DEV_ENTRY);
	cmd.data[0] = devid;

	ret = iommu_queue_command(iommu, &cmd);

	return ret;
}