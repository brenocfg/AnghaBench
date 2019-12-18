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
struct amd_iommu {int /*<<< orphan*/  lock; scalar_t__ mmio_base; } ;

/* Variables and functions */
 unsigned long EXIT_LOOP_COUNT ; 
 int /*<<< orphan*/  INC_STATS_COUNTER (int /*<<< orphan*/ ) ; 
 unsigned int MMIO_STATUS_COM_WAIT_INT_MASK ; 
 scalar_t__ MMIO_STATUS_OFFSET ; 
 int /*<<< orphan*/  compl_wait ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  reset_iommu_command_buffer (struct amd_iommu*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static void __iommu_wait_for_completion(struct amd_iommu *iommu)
{
	int ready = 0;
	unsigned status = 0;
	unsigned long i = 0;

	INC_STATS_COUNTER(compl_wait);

	while (!ready && (i < EXIT_LOOP_COUNT)) {
		++i;
		/* wait for the bit to become one */
		status = readl(iommu->mmio_base + MMIO_STATUS_OFFSET);
		ready = status & MMIO_STATUS_COM_WAIT_INT_MASK;
	}

	/* set bit back to zero */
	status &= ~MMIO_STATUS_COM_WAIT_INT_MASK;
	writel(status, iommu->mmio_base + MMIO_STATUS_OFFSET);

	if (unlikely(i == EXIT_LOOP_COUNT)) {
		spin_unlock(&iommu->lock);
		reset_iommu_command_buffer(iommu);
		spin_lock(&iommu->lock);
	}
}