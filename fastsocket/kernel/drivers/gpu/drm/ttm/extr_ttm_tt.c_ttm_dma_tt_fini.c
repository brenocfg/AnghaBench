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
struct ttm_tt {int /*<<< orphan*/ * pages; } ;
struct ttm_dma_tt {int /*<<< orphan*/ * dma_address; struct ttm_tt ttm; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_free_large (int /*<<< orphan*/ *) ; 

void ttm_dma_tt_fini(struct ttm_dma_tt *ttm_dma)
{
	struct ttm_tt *ttm = &ttm_dma->ttm;

	drm_free_large(ttm->pages);
	ttm->pages = NULL;
	drm_free_large(ttm_dma->dma_address);
	ttm_dma->dma_address = NULL;
}