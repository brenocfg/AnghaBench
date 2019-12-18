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
struct iommu_cmd {int /*<<< orphan*/ * data; } ;
struct amd_iommu {int dummy; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_COMPL_WAIT ; 
 int /*<<< orphan*/  CMD_COMPL_WAIT_INT_MASK ; 
 int /*<<< orphan*/  CMD_SET_TYPE (struct iommu_cmd*,int /*<<< orphan*/ ) ; 
 int __iommu_queue_command (struct amd_iommu*,struct iommu_cmd*) ; 
 int /*<<< orphan*/  memset (struct iommu_cmd*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int __iommu_completion_wait(struct amd_iommu *iommu)
{
	struct iommu_cmd cmd;

	 memset(&cmd, 0, sizeof(cmd));
	 cmd.data[0] = CMD_COMPL_WAIT_INT_MASK;
	 CMD_SET_TYPE(&cmd, CMD_COMPL_WAIT);

	 return __iommu_queue_command(iommu, &cmd);
}