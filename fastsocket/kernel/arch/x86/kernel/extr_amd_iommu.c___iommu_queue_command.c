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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct iommu_cmd {int dummy; } ;
struct amd_iommu {int cmd_buf_size; scalar_t__ mmio_base; int /*<<< orphan*/ * cmd_buf; } ;

/* Variables and functions */
 int CMD_BUFFER_UNINITIALIZED ; 
 int ENOMEM ; 
 scalar_t__ MMIO_CMD_HEAD_OFFSET ; 
 scalar_t__ MMIO_CMD_TAIL_OFFSET ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  memcpy_toio (int /*<<< orphan*/ *,struct iommu_cmd*,int) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int __iommu_queue_command(struct amd_iommu *iommu, struct iommu_cmd *cmd)
{
	u32 tail, head;
	u8 *target;

	WARN_ON(iommu->cmd_buf_size & CMD_BUFFER_UNINITIALIZED);
	tail = readl(iommu->mmio_base + MMIO_CMD_TAIL_OFFSET);
	target = iommu->cmd_buf + tail;
	memcpy_toio(target, cmd, sizeof(*cmd));
	tail = (tail + sizeof(*cmd)) % iommu->cmd_buf_size;
	head = readl(iommu->mmio_base + MMIO_CMD_HEAD_OFFSET);
	if (tail == head)
		return -ENOMEM;
	writel(tail, iommu->mmio_base + MMIO_CMD_TAIL_OFFSET);

	return 0;
}