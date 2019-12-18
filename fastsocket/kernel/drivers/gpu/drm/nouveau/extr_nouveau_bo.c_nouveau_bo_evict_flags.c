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
struct ttm_placement {int dummy; } ;
struct TYPE_2__ {int mem_type; } ;
struct ttm_buffer_object {TYPE_1__ mem; } ;
struct nouveau_bo {struct ttm_placement placement; } ;

/* Variables and functions */
 int /*<<< orphan*/  TTM_PL_FLAG_SYSTEM ; 
 int /*<<< orphan*/  TTM_PL_FLAG_TT ; 
#define  TTM_PL_VRAM 128 
 struct nouveau_bo* nouveau_bo (struct ttm_buffer_object*) ; 
 int /*<<< orphan*/  nouveau_bo_placement_set (struct nouveau_bo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nouveau_bo_evict_flags(struct ttm_buffer_object *bo, struct ttm_placement *pl)
{
	struct nouveau_bo *nvbo = nouveau_bo(bo);

	switch (bo->mem.mem_type) {
	case TTM_PL_VRAM:
		nouveau_bo_placement_set(nvbo, TTM_PL_FLAG_TT,
					 TTM_PL_FLAG_SYSTEM);
		break;
	default:
		nouveau_bo_placement_set(nvbo, TTM_PL_FLAG_SYSTEM, 0);
		break;
	}

	*pl = nvbo->placement;
}