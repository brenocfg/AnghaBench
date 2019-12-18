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
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDP_MEM_COHERENCY_FLUSH_CNTL ; 
 int /*<<< orphan*/  VM_INVALIDATE_REQUEST ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 

void cayman_pcie_gart_tlb_flush(struct radeon_device *rdev)
{
	/* flush hdp cache */
	WREG32(HDP_MEM_COHERENCY_FLUSH_CNTL, 0x1);

	/* bits 0-7 are the VM contexts0-7 */
	WREG32(VM_INVALIDATE_REQUEST, 1);
}