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
struct ttm_mem_type_manager {int /*<<< orphan*/  bdev; } ;
struct ttm_mem_reg {int /*<<< orphan*/  mm_node; } ;
struct nouveau_mem {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* put ) (struct nouveau_fb*,struct nouveau_mem**) ;} ;
struct nouveau_fb {TYPE_1__ ram; } ;
struct nouveau_drm {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 struct nouveau_drm* nouveau_bdev (int /*<<< orphan*/ ) ; 
 struct nouveau_fb* nouveau_fb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nouveau_mem_node_cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct nouveau_fb*,struct nouveau_mem**) ; 

__attribute__((used)) static void
nouveau_vram_manager_del(struct ttm_mem_type_manager *man,
			 struct ttm_mem_reg *mem)
{
	struct nouveau_drm *drm = nouveau_bdev(man->bdev);
	struct nouveau_fb *pfb = nouveau_fb(drm->device);
	nouveau_mem_node_cleanup(mem->mm_node);
	pfb->ram.put(pfb, (struct nouveau_mem **)&mem->mm_node);
}