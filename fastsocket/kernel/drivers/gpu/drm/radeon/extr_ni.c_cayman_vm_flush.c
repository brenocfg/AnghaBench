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
struct radeon_vm {int id; int pd_gpu_addr; } ;
struct radeon_ring {int dummy; } ;
struct radeon_device {struct radeon_ring* ring; } ;

/* Variables and functions */
 scalar_t__ HDP_MEM_COHERENCY_FLUSH_CNTL ; 
 int PACKET0 (scalar_t__,int /*<<< orphan*/ ) ; 
 int PACKET3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PACKET3_PFP_SYNC_ME ; 
 scalar_t__ VM_CONTEXT0_PAGE_TABLE_BASE_ADDR ; 
 scalar_t__ VM_INVALIDATE_REQUEST ; 
 int /*<<< orphan*/  radeon_ring_write (struct radeon_ring*,int) ; 

void cayman_vm_flush(struct radeon_device *rdev, int ridx, struct radeon_vm *vm)
{
	struct radeon_ring *ring = &rdev->ring[ridx];

	if (vm == NULL)
		return;

	radeon_ring_write(ring, PACKET0(VM_CONTEXT0_PAGE_TABLE_BASE_ADDR + (vm->id << 2), 0));
	radeon_ring_write(ring, vm->pd_gpu_addr >> 12);

	/* flush hdp cache */
	radeon_ring_write(ring, PACKET0(HDP_MEM_COHERENCY_FLUSH_CNTL, 0));
	radeon_ring_write(ring, 0x1);

	/* bits 0-7 are the VM contexts0-7 */
	radeon_ring_write(ring, PACKET0(VM_INVALIDATE_REQUEST, 0));
	radeon_ring_write(ring, 1 << vm->id);

	/* sync PFP to ME, otherwise we might get invalid PFP reads */
	radeon_ring_write(ring, PACKET3(PACKET3_PFP_SYNC_ME, 0));
	radeon_ring_write(ring, 0x0);
}