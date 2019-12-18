#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct radeon_ring {unsigned int ring_size; unsigned int rptr_offs; unsigned int rptr_reg; unsigned int wptr_reg; int ptr_reg_shift; int ptr_reg_mask; int nop; int ptr_mask; int ring_free_dw; int idx; int /*<<< orphan*/ * next_rptr_cpu_addr; scalar_t__ next_rptr_gpu_addr; int /*<<< orphan*/ * ring_obj; int /*<<< orphan*/  ring; int /*<<< orphan*/  gpu_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/ * wb; scalar_t__ gpu_addr; scalar_t__ enabled; } ;
struct radeon_device {TYPE_1__ wb; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  RADEON_GEM_DOMAIN_GTT ; 
 int RADEON_WB_RING0_NEXT_RPTR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int radeon_bo_create (struct radeon_device*,unsigned int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int radeon_bo_kmap (int /*<<< orphan*/ *,void**) ; 
 int radeon_bo_pin (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int radeon_bo_reserve (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  radeon_bo_unreserve (int /*<<< orphan*/ *) ; 
 scalar_t__ radeon_debugfs_ring_init (struct radeon_device*,struct radeon_ring*) ; 
 int /*<<< orphan*/  radeon_ring_lockup_update (struct radeon_ring*) ; 
 scalar_t__ unlikely (int) ; 

int radeon_ring_init(struct radeon_device *rdev, struct radeon_ring *ring, unsigned ring_size,
		     unsigned rptr_offs, unsigned rptr_reg, unsigned wptr_reg,
		     u32 ptr_reg_shift, u32 ptr_reg_mask, u32 nop)
{
	int r;

	ring->ring_size = ring_size;
	ring->rptr_offs = rptr_offs;
	ring->rptr_reg = rptr_reg;
	ring->wptr_reg = wptr_reg;
	ring->ptr_reg_shift = ptr_reg_shift;
	ring->ptr_reg_mask = ptr_reg_mask;
	ring->nop = nop;
	/* Allocate ring buffer */
	if (ring->ring_obj == NULL) {
		r = radeon_bo_create(rdev, ring->ring_size, PAGE_SIZE, true,
				     RADEON_GEM_DOMAIN_GTT,
				     NULL, &ring->ring_obj);
		if (r) {
			dev_err(rdev->dev, "(%d) ring create failed\n", r);
			return r;
		}
		r = radeon_bo_reserve(ring->ring_obj, false);
		if (unlikely(r != 0))
			return r;
		r = radeon_bo_pin(ring->ring_obj, RADEON_GEM_DOMAIN_GTT,
					&ring->gpu_addr);
		if (r) {
			radeon_bo_unreserve(ring->ring_obj);
			dev_err(rdev->dev, "(%d) ring pin failed\n", r);
			return r;
		}
		r = radeon_bo_kmap(ring->ring_obj,
				       (void **)&ring->ring);
		radeon_bo_unreserve(ring->ring_obj);
		if (r) {
			dev_err(rdev->dev, "(%d) ring map failed\n", r);
			return r;
		}
	}
	ring->ptr_mask = (ring->ring_size / 4) - 1;
	ring->ring_free_dw = ring->ring_size / 4;
	if (rdev->wb.enabled) {
		u32 index = RADEON_WB_RING0_NEXT_RPTR + (ring->idx * 4);
		ring->next_rptr_gpu_addr = rdev->wb.gpu_addr + index;
		ring->next_rptr_cpu_addr = &rdev->wb.wb[index/4];
	}
	if (radeon_debugfs_ring_init(rdev, ring)) {
		DRM_ERROR("Failed to register debugfs file for rings !\n");
	}
	radeon_ring_lockup_update(ring);
	return 0;
}