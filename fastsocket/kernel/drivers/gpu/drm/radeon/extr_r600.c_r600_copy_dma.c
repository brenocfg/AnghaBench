#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int u32 ;
struct radeon_semaphore {int dummy; } ;
struct radeon_ring {int /*<<< orphan*/  idx; } ;
struct radeon_fence {int /*<<< orphan*/  ring; } ;
struct radeon_device {struct radeon_ring* ring; TYPE_2__* asic; } ;
struct TYPE_3__ {int dma_ring_index; } ;
struct TYPE_4__ {TYPE_1__ copy; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 
 int DMA_PACKET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DMA_PACKET_COPY ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 unsigned int RADEON_GPU_PAGE_SHIFT ; 
 int radeon_fence_emit (struct radeon_device*,struct radeon_fence**,int /*<<< orphan*/ ) ; 
 scalar_t__ radeon_fence_need_sync (struct radeon_fence*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_fence_note_sync (struct radeon_fence*,int /*<<< orphan*/ ) ; 
 int radeon_ring_lock (struct radeon_device*,struct radeon_ring*,int) ; 
 int /*<<< orphan*/  radeon_ring_unlock_commit (struct radeon_device*,struct radeon_ring*) ; 
 int /*<<< orphan*/  radeon_ring_unlock_undo (struct radeon_device*,struct radeon_ring*) ; 
 int /*<<< orphan*/  radeon_ring_write (struct radeon_ring*,int) ; 
 int radeon_semaphore_create (struct radeon_device*,struct radeon_semaphore**) ; 
 int /*<<< orphan*/  radeon_semaphore_free (struct radeon_device*,struct radeon_semaphore**,struct radeon_fence*) ; 
 int /*<<< orphan*/  radeon_semaphore_sync_rings (struct radeon_device*,struct radeon_semaphore*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int upper_32_bits (int) ; 

int r600_copy_dma(struct radeon_device *rdev,
		  uint64_t src_offset, uint64_t dst_offset,
		  unsigned num_gpu_pages,
		  struct radeon_fence **fence)
{
	struct radeon_semaphore *sem = NULL;
	int ring_index = rdev->asic->copy.dma_ring_index;
	struct radeon_ring *ring = &rdev->ring[ring_index];
	u32 size_in_dw, cur_size_in_dw;
	int i, num_loops;
	int r = 0;

	r = radeon_semaphore_create(rdev, &sem);
	if (r) {
		DRM_ERROR("radeon: moving bo (%d).\n", r);
		return r;
	}

	size_in_dw = (num_gpu_pages << RADEON_GPU_PAGE_SHIFT) / 4;
	num_loops = DIV_ROUND_UP(size_in_dw, 0xFFFE);
	r = radeon_ring_lock(rdev, ring, num_loops * 4 + 8);
	if (r) {
		DRM_ERROR("radeon: moving bo (%d).\n", r);
		radeon_semaphore_free(rdev, &sem, NULL);
		return r;
	}

	if (radeon_fence_need_sync(*fence, ring->idx)) {
		radeon_semaphore_sync_rings(rdev, sem, (*fence)->ring,
					    ring->idx);
		radeon_fence_note_sync(*fence, ring->idx);
	} else {
		radeon_semaphore_free(rdev, &sem, NULL);
	}

	for (i = 0; i < num_loops; i++) {
		cur_size_in_dw = size_in_dw;
		if (cur_size_in_dw > 0xFFFE)
			cur_size_in_dw = 0xFFFE;
		size_in_dw -= cur_size_in_dw;
		radeon_ring_write(ring, DMA_PACKET(DMA_PACKET_COPY, 0, 0, cur_size_in_dw));
		radeon_ring_write(ring, dst_offset & 0xfffffffc);
		radeon_ring_write(ring, src_offset & 0xfffffffc);
		radeon_ring_write(ring, (((upper_32_bits(dst_offset) & 0xff) << 16) |
					 (upper_32_bits(src_offset) & 0xff)));
		src_offset += cur_size_in_dw * 4;
		dst_offset += cur_size_in_dw * 4;
	}

	r = radeon_fence_emit(rdev, fence, ring->idx);
	if (r) {
		radeon_ring_unlock_undo(rdev, ring);
		return r;
	}

	radeon_ring_unlock_commit(rdev, ring);
	radeon_semaphore_free(rdev, &sem, *fence);

	return r;
}