#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct radeon_ring {int /*<<< orphan*/  ring_size; } ;
struct TYPE_6__ {int /*<<< orphan*/  installed; } ;
struct radeon_device {int flags; int /*<<< orphan*/  dev; struct radeon_ring* ring; TYPE_3__ irq; TYPE_2__* asic; int /*<<< orphan*/  rlc_fw; int /*<<< orphan*/  pfp_fw; int /*<<< orphan*/  me_fw; int /*<<< orphan*/  mc_fw; } ;
struct TYPE_4__ {int /*<<< orphan*/ * copy; } ;
struct TYPE_5__ {TYPE_1__ copy; } ;

/* Variables and functions */
 scalar_t__ ASIC_IS_DCE5 (struct radeon_device*) ; 
 int /*<<< orphan*/  DMA_PACKET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_PACKET_NOP ; 
 int /*<<< orphan*/  DMA_RB_RPTR ; 
 int /*<<< orphan*/  DMA_RB_WPTR ; 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int /*<<< orphan*/  R600_CP_RB_RPTR ; 
 int /*<<< orphan*/  R600_CP_RB_WPTR ; 
 size_t R600_RING_TYPE_DMA_INDEX ; 
 int /*<<< orphan*/  R600_WB_DMA_RPTR_OFFSET ; 
 int /*<<< orphan*/  RADEON_CP_PACKET2 ; 
 int RADEON_IS_AGP ; 
 size_t RADEON_RING_TYPE_GFX_INDEX ; 
 int /*<<< orphan*/  RADEON_WB_CP_RPTR_OFFSET ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  evergreen_agp_enable (struct radeon_device*) ; 
 int evergreen_blit_init (struct radeon_device*) ; 
 int evergreen_cp_load_microcode (struct radeon_device*) ; 
 int evergreen_cp_resume (struct radeon_device*) ; 
 int /*<<< orphan*/  evergreen_gpu_init (struct radeon_device*) ; 
 int /*<<< orphan*/  evergreen_irq_set (struct radeon_device*) ; 
 int /*<<< orphan*/  evergreen_mc_program (struct radeon_device*) ; 
 int evergreen_pcie_gart_enable (struct radeon_device*) ; 
 int /*<<< orphan*/  evergreen_pcie_gen2_enable (struct radeon_device*) ; 
 int ni_init_microcode (struct radeon_device*) ; 
 int ni_mc_load_microcode (struct radeon_device*) ; 
 int r600_audio_init (struct radeon_device*) ; 
 int /*<<< orphan*/  r600_blit_fini (struct radeon_device*) ; 
 int r600_dma_resume (struct radeon_device*) ; 
 int r600_init_microcode (struct radeon_device*) ; 
 int r600_irq_init (struct radeon_device*) ; 
 int r600_vram_scratch_init (struct radeon_device*) ; 
 int radeon_fence_driver_start_ring (struct radeon_device*,size_t) ; 
 int radeon_ib_pool_init (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_irq_kms_fini (struct radeon_device*) ; 
 int radeon_irq_kms_init (struct radeon_device*) ; 
 int radeon_ring_init (struct radeon_device*,struct radeon_ring*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int radeon_wb_init (struct radeon_device*) ; 

__attribute__((used)) static int evergreen_startup(struct radeon_device *rdev)
{
	struct radeon_ring *ring = &rdev->ring[RADEON_RING_TYPE_GFX_INDEX];
	int r;

	/* enable pcie gen2 link */
	evergreen_pcie_gen2_enable(rdev);

	if (ASIC_IS_DCE5(rdev)) {
		if (!rdev->me_fw || !rdev->pfp_fw || !rdev->rlc_fw || !rdev->mc_fw) {
			r = ni_init_microcode(rdev);
			if (r) {
				DRM_ERROR("Failed to load firmware!\n");
				return r;
			}
		}
		r = ni_mc_load_microcode(rdev);
		if (r) {
			DRM_ERROR("Failed to load MC firmware!\n");
			return r;
		}
	} else {
		if (!rdev->me_fw || !rdev->pfp_fw || !rdev->rlc_fw) {
			r = r600_init_microcode(rdev);
			if (r) {
				DRM_ERROR("Failed to load firmware!\n");
				return r;
			}
		}
	}

	r = r600_vram_scratch_init(rdev);
	if (r)
		return r;

	evergreen_mc_program(rdev);
	if (rdev->flags & RADEON_IS_AGP) {
		evergreen_agp_enable(rdev);
	} else {
		r = evergreen_pcie_gart_enable(rdev);
		if (r)
			return r;
	}
	evergreen_gpu_init(rdev);

	r = evergreen_blit_init(rdev);
	if (r) {
		r600_blit_fini(rdev);
		rdev->asic->copy.copy = NULL;
		dev_warn(rdev->dev, "failed blitter (%d) falling back to memcpy\n", r);
	}

	/* allocate wb buffer */
	r = radeon_wb_init(rdev);
	if (r)
		return r;

	r = radeon_fence_driver_start_ring(rdev, RADEON_RING_TYPE_GFX_INDEX);
	if (r) {
		dev_err(rdev->dev, "failed initializing CP fences (%d).\n", r);
		return r;
	}

	r = radeon_fence_driver_start_ring(rdev, R600_RING_TYPE_DMA_INDEX);
	if (r) {
		dev_err(rdev->dev, "failed initializing DMA fences (%d).\n", r);
		return r;
	}

	/* Enable IRQ */
	if (!rdev->irq.installed) {
		r = radeon_irq_kms_init(rdev);
		if (r)
			return r;
	}

	r = r600_irq_init(rdev);
	if (r) {
		DRM_ERROR("radeon: IH init failed (%d).\n", r);
		radeon_irq_kms_fini(rdev);
		return r;
	}
	evergreen_irq_set(rdev);

	r = radeon_ring_init(rdev, ring, ring->ring_size, RADEON_WB_CP_RPTR_OFFSET,
			     R600_CP_RB_RPTR, R600_CP_RB_WPTR,
			     0, 0xfffff, RADEON_CP_PACKET2);
	if (r)
		return r;

	ring = &rdev->ring[R600_RING_TYPE_DMA_INDEX];
	r = radeon_ring_init(rdev, ring, ring->ring_size, R600_WB_DMA_RPTR_OFFSET,
			     DMA_RB_RPTR, DMA_RB_WPTR,
			     2, 0x3fffc, DMA_PACKET(DMA_PACKET_NOP, 0, 0));
	if (r)
		return r;

	r = evergreen_cp_load_microcode(rdev);
	if (r)
		return r;
	r = evergreen_cp_resume(rdev);
	if (r)
		return r;
	r = r600_dma_resume(rdev);
	if (r)
		return r;

	r = radeon_ib_pool_init(rdev);
	if (r) {
		dev_err(rdev->dev, "IB initialization failed (%d).\n", r);
		return r;
	}

	r = r600_audio_init(rdev);
	if (r) {
		DRM_ERROR("radeon: audio init failed\n");
		return r;
	}

	return 0;
}