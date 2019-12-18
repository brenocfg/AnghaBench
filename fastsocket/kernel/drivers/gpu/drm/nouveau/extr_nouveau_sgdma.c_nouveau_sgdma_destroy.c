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
struct ttm_tt {int dummy; } ;
struct nouveau_sgdma_be {int /*<<< orphan*/  ttm; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct nouveau_sgdma_be*) ; 
 int /*<<< orphan*/  ttm_dma_tt_fini (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nouveau_sgdma_destroy(struct ttm_tt *ttm)
{
	struct nouveau_sgdma_be *nvbe = (struct nouveau_sgdma_be *)ttm;

	if (ttm) {
		ttm_dma_tt_fini(&nvbe->ttm);
		kfree(nvbe);
	}
}