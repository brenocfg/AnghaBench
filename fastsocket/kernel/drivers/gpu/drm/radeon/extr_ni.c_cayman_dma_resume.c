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
typedef  int u32 ;
struct radeon_ring {int ring_size; int gpu_addr; int wptr; int rptr; int ready; int /*<<< orphan*/  idx; } ;
struct TYPE_4__ {int /*<<< orphan*/  real_vram_size; } ;
struct TYPE_3__ {int gpu_addr; scalar_t__ enabled; } ;
struct radeon_device {TYPE_2__ mc; TYPE_1__ wb; struct radeon_ring* ring; } ;

/* Variables and functions */
 size_t CAYMAN_RING_TYPE_DMA1_INDEX ; 
 int CAYMAN_WB_DMA1_RPTR_OFFSET ; 
 int CMD_VMID_FORCE ; 
 int CTXEMPTY_INT_ENABLE ; 
 int DMA0_REGISTER_OFFSET ; 
 int DMA1_REGISTER_OFFSET ; 
 int DMA_CNTL ; 
 int DMA_IB_CNTL ; 
 int DMA_IB_ENABLE ; 
 int DMA_IB_SWAP_ENABLE ; 
 int DMA_RB_BASE ; 
 int DMA_RB_CNTL ; 
 int DMA_RB_ENABLE ; 
 int DMA_RB_RPTR ; 
 int DMA_RB_RPTR_ADDR_HI ; 
 int DMA_RB_RPTR_ADDR_LO ; 
 int DMA_RB_SWAP_ENABLE ; 
 int DMA_RB_WPTR ; 
 int DMA_RPTR_WRITEBACK_ENABLE ; 
 int DMA_RPTR_WRITEBACK_SWAP_ENABLE ; 
 int DMA_SEM_INCOMPLETE_TIMER_CNTL ; 
 int DMA_SEM_WAIT_FAIL_TIMER_CNTL ; 
 size_t R600_RING_TYPE_DMA_INDEX ; 
 int R600_WB_DMA_RPTR_OFFSET ; 
 int RREG32 (int) ; 
 int SOFT_RESET_DMA ; 
 int SOFT_RESET_DMA1 ; 
 int SRBM_SOFT_RESET ; 
 int /*<<< orphan*/  WREG32 (int,int) ; 
 int drm_order (int) ; 
 int radeon_ring_test (struct radeon_device*,int /*<<< orphan*/ ,struct radeon_ring*) ; 
 int /*<<< orphan*/  radeon_ttm_set_active_vram_size (struct radeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int upper_32_bits (int) ; 

int cayman_dma_resume(struct radeon_device *rdev)
{
	struct radeon_ring *ring;
	u32 rb_cntl, dma_cntl, ib_cntl;
	u32 rb_bufsz;
	u32 reg_offset, wb_offset;
	int i, r;

	/* Reset dma */
	WREG32(SRBM_SOFT_RESET, SOFT_RESET_DMA | SOFT_RESET_DMA1);
	RREG32(SRBM_SOFT_RESET);
	udelay(50);
	WREG32(SRBM_SOFT_RESET, 0);

	for (i = 0; i < 2; i++) {
		if (i == 0) {
			ring = &rdev->ring[R600_RING_TYPE_DMA_INDEX];
			reg_offset = DMA0_REGISTER_OFFSET;
			wb_offset = R600_WB_DMA_RPTR_OFFSET;
		} else {
			ring = &rdev->ring[CAYMAN_RING_TYPE_DMA1_INDEX];
			reg_offset = DMA1_REGISTER_OFFSET;
			wb_offset = CAYMAN_WB_DMA1_RPTR_OFFSET;
		}

		WREG32(DMA_SEM_INCOMPLETE_TIMER_CNTL + reg_offset, 0);
		WREG32(DMA_SEM_WAIT_FAIL_TIMER_CNTL + reg_offset, 0);

		/* Set ring buffer size in dwords */
		rb_bufsz = drm_order(ring->ring_size / 4);
		rb_cntl = rb_bufsz << 1;
#ifdef __BIG_ENDIAN
		rb_cntl |= DMA_RB_SWAP_ENABLE | DMA_RPTR_WRITEBACK_SWAP_ENABLE;
#endif
		WREG32(DMA_RB_CNTL + reg_offset, rb_cntl);

		/* Initialize the ring buffer's read and write pointers */
		WREG32(DMA_RB_RPTR + reg_offset, 0);
		WREG32(DMA_RB_WPTR + reg_offset, 0);

		/* set the wb address whether it's enabled or not */
		WREG32(DMA_RB_RPTR_ADDR_HI + reg_offset,
		       upper_32_bits(rdev->wb.gpu_addr + wb_offset) & 0xFF);
		WREG32(DMA_RB_RPTR_ADDR_LO + reg_offset,
		       ((rdev->wb.gpu_addr + wb_offset) & 0xFFFFFFFC));

		if (rdev->wb.enabled)
			rb_cntl |= DMA_RPTR_WRITEBACK_ENABLE;

		WREG32(DMA_RB_BASE + reg_offset, ring->gpu_addr >> 8);

		/* enable DMA IBs */
		ib_cntl = DMA_IB_ENABLE | CMD_VMID_FORCE;
#ifdef __BIG_ENDIAN
		ib_cntl |= DMA_IB_SWAP_ENABLE;
#endif
		WREG32(DMA_IB_CNTL + reg_offset, ib_cntl);

		dma_cntl = RREG32(DMA_CNTL + reg_offset);
		dma_cntl &= ~CTXEMPTY_INT_ENABLE;
		WREG32(DMA_CNTL + reg_offset, dma_cntl);

		ring->wptr = 0;
		WREG32(DMA_RB_WPTR + reg_offset, ring->wptr << 2);

		ring->rptr = RREG32(DMA_RB_RPTR + reg_offset) >> 2;

		WREG32(DMA_RB_CNTL + reg_offset, rb_cntl | DMA_RB_ENABLE);

		ring->ready = true;

		r = radeon_ring_test(rdev, ring->idx, ring);
		if (r) {
			ring->ready = false;
			return r;
		}
	}

	radeon_ttm_set_active_vram_size(rdev, rdev->mc.real_vram_size);

	return 0;
}