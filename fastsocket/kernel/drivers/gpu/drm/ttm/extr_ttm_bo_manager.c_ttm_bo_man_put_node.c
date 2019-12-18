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
struct ttm_range_manager {int /*<<< orphan*/  lock; } ;
struct ttm_mem_type_manager {scalar_t__ priv; } ;
struct ttm_mem_reg {int /*<<< orphan*/ * mm_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_mm_put_block (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ttm_bo_man_put_node(struct ttm_mem_type_manager *man,
				struct ttm_mem_reg *mem)
{
	struct ttm_range_manager *rman = (struct ttm_range_manager *) man->priv;

	if (mem->mm_node) {
		spin_lock(&rman->lock);
		drm_mm_put_block(mem->mm_node);
		spin_unlock(&rman->lock);
		mem->mm_node = NULL;
	}
}