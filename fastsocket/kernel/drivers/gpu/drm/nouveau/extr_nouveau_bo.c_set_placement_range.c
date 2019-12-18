#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int u32 ;
struct TYPE_6__ {int size; } ;
struct nouveau_fb {TYPE_1__ ram; } ;
struct nouveau_drm {int /*<<< orphan*/  device; } ;
struct TYPE_9__ {int fpfn; int lpfn; } ;
struct TYPE_7__ {int num_pages; } ;
struct TYPE_8__ {TYPE_2__ mem; int /*<<< orphan*/  bdev; } ;
struct nouveau_bo {int tile_flags; TYPE_4__ placement; TYPE_3__ bo; scalar_t__ tile_mode; } ;
struct TYPE_10__ {scalar_t__ card_type; } ;

/* Variables and functions */
 int NOUVEAU_GEM_TILE_ZETA ; 
 scalar_t__ NV_10 ; 
 int PAGE_SHIFT ; 
 int TTM_PL_FLAG_VRAM ; 
 struct nouveau_drm* nouveau_bdev (int /*<<< orphan*/ ) ; 
 struct nouveau_fb* nouveau_fb (int /*<<< orphan*/ ) ; 
 TYPE_5__* nv_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
set_placement_range(struct nouveau_bo *nvbo, uint32_t type)
{
	struct nouveau_drm *drm = nouveau_bdev(nvbo->bo.bdev);
	struct nouveau_fb *pfb = nouveau_fb(drm->device);
	u32 vram_pages = pfb->ram.size >> PAGE_SHIFT;

	if (nv_device(drm->device)->card_type == NV_10 &&
	    nvbo->tile_mode && (type & TTM_PL_FLAG_VRAM) &&
	    nvbo->bo.mem.num_pages < vram_pages / 4) {
		/*
		 * Make sure that the color and depth buffers are handled
		 * by independent memory controller units. Up to a 9x
		 * speed up when alpha-blending and depth-test are enabled
		 * at the same time.
		 */
		if (nvbo->tile_flags & NOUVEAU_GEM_TILE_ZETA) {
			nvbo->placement.fpfn = vram_pages / 2;
			nvbo->placement.lpfn = ~0;
		} else {
			nvbo->placement.fpfn = 0;
			nvbo->placement.lpfn = vram_pages / 2;
		}
	}
}