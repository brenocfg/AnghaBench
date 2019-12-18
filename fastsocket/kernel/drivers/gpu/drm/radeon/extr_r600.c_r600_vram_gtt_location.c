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
typedef  scalar_t__ u64 ;
struct radeon_mc {int mc_vram_size; int real_vram_size; scalar_t__ gtt_start; scalar_t__ gtt_end; scalar_t__ vram_start; scalar_t__ vram_end; } ;
struct TYPE_2__ {scalar_t__ gtt_base_align; } ;
struct radeon_device {int flags; TYPE_1__ mc; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MC_VM_FB_LOCATION ; 
 int RADEON_IS_AGP ; 
 int RADEON_IS_IGP ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  radeon_gtt_location (struct radeon_device*,struct radeon_mc*) ; 
 int /*<<< orphan*/  radeon_vram_location (struct radeon_device*,TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static void r600_vram_gtt_location(struct radeon_device *rdev, struct radeon_mc *mc)
{
	u64 size_bf, size_af;

	if (mc->mc_vram_size > 0xE0000000) {
		/* leave room for at least 512M GTT */
		dev_warn(rdev->dev, "limiting VRAM\n");
		mc->real_vram_size = 0xE0000000;
		mc->mc_vram_size = 0xE0000000;
	}
	if (rdev->flags & RADEON_IS_AGP) {
		size_bf = mc->gtt_start;
		size_af = 0xFFFFFFFF - mc->gtt_end;
		if (size_bf > size_af) {
			if (mc->mc_vram_size > size_bf) {
				dev_warn(rdev->dev, "limiting VRAM\n");
				mc->real_vram_size = size_bf;
				mc->mc_vram_size = size_bf;
			}
			mc->vram_start = mc->gtt_start - mc->mc_vram_size;
		} else {
			if (mc->mc_vram_size > size_af) {
				dev_warn(rdev->dev, "limiting VRAM\n");
				mc->real_vram_size = size_af;
				mc->mc_vram_size = size_af;
			}
			mc->vram_start = mc->gtt_end + 1;
		}
		mc->vram_end = mc->vram_start + mc->mc_vram_size - 1;
		dev_info(rdev->dev, "VRAM: %lluM 0x%08llX - 0x%08llX (%lluM used)\n",
				mc->mc_vram_size >> 20, mc->vram_start,
				mc->vram_end, mc->real_vram_size >> 20);
	} else {
		u64 base = 0;
		if (rdev->flags & RADEON_IS_IGP) {
			base = RREG32(MC_VM_FB_LOCATION) & 0xFFFF;
			base <<= 24;
		}
		radeon_vram_location(rdev, &rdev->mc, base);
		rdev->mc.gtt_base_align = 0;
		radeon_gtt_location(rdev, mc);
	}
}