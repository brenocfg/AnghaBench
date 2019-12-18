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
struct TYPE_5__ {TYPE_1__* man; } ;
struct TYPE_6__ {TYPE_2__ bdev; } ;
struct radeon_device {TYPE_3__ mman; } ;
struct drm_info_list {char* name; int /*<<< orphan*/ * data; scalar_t__ driver_features; int /*<<< orphan*/ * show; } ;
struct TYPE_4__ {int /*<<< orphan*/ * priv; } ;

/* Variables and functions */
 int RADEON_DEBUGFS_MEM_TYPES ; 
 size_t TTM_PL_TT ; 
 size_t TTM_PL_VRAM ; 
 int radeon_debugfs_add_files (struct radeon_device*,struct drm_info_list*,unsigned int) ; 
 int /*<<< orphan*/  radeon_mm_dump_table ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 
 scalar_t__ swiotlb_nr_tbl () ; 
 int /*<<< orphan*/  ttm_dma_page_alloc_debugfs ; 
 int /*<<< orphan*/  ttm_page_alloc_debugfs ; 

__attribute__((used)) static int radeon_ttm_debugfs_init(struct radeon_device *rdev)
{
#if defined(CONFIG_DEBUG_FS)
	static struct drm_info_list radeon_mem_types_list[RADEON_DEBUGFS_MEM_TYPES+2];
	static char radeon_mem_types_names[RADEON_DEBUGFS_MEM_TYPES+2][32];
	unsigned i;

	for (i = 0; i < RADEON_DEBUGFS_MEM_TYPES; i++) {
		if (i == 0)
			sprintf(radeon_mem_types_names[i], "radeon_vram_mm");
		else
			sprintf(radeon_mem_types_names[i], "radeon_gtt_mm");
		radeon_mem_types_list[i].name = radeon_mem_types_names[i];
		radeon_mem_types_list[i].show = &radeon_mm_dump_table;
		radeon_mem_types_list[i].driver_features = 0;
		if (i == 0)
			radeon_mem_types_list[i].data = rdev->mman.bdev.man[TTM_PL_VRAM].priv;
		else
			radeon_mem_types_list[i].data = rdev->mman.bdev.man[TTM_PL_TT].priv;

	}
	/* Add ttm page pool to debugfs */
	sprintf(radeon_mem_types_names[i], "ttm_page_pool");
	radeon_mem_types_list[i].name = radeon_mem_types_names[i];
	radeon_mem_types_list[i].show = &ttm_page_alloc_debugfs;
	radeon_mem_types_list[i].driver_features = 0;
	radeon_mem_types_list[i++].data = NULL;
#ifdef CONFIG_SWIOTLB
	if (swiotlb_nr_tbl()) {
		sprintf(radeon_mem_types_names[i], "ttm_dma_page_pool");
		radeon_mem_types_list[i].name = radeon_mem_types_names[i];
		radeon_mem_types_list[i].show = &ttm_dma_page_alloc_debugfs;
		radeon_mem_types_list[i].driver_features = 0;
		radeon_mem_types_list[i++].data = NULL;
	}
#endif
	return radeon_debugfs_add_files(rdev, radeon_mem_types_list, i);

#endif
	return 0;
}