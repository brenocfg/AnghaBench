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
struct ttm_tt {unsigned int num_pages; int /*<<< orphan*/  state; int /*<<< orphan*/  caching_state; int /*<<< orphan*/  page_flags; scalar_t__* pages; TYPE_1__* glob; } ;
struct TYPE_2__ {int /*<<< orphan*/  mem_glob; } ;

/* Variables and functions */
 int /*<<< orphan*/  tt_unpopulated ; 
 int /*<<< orphan*/  ttm_mem_global_free_page (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ttm_put_pages (scalar_t__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ttm_pool_unpopulate(struct ttm_tt *ttm)
{
	unsigned i;

	for (i = 0; i < ttm->num_pages; ++i) {
		if (ttm->pages[i]) {
			ttm_mem_global_free_page(ttm->glob->mem_glob,
						 ttm->pages[i]);
			ttm_put_pages(&ttm->pages[i], 1,
				      ttm->page_flags,
				      ttm->caching_state);
		}
	}
	ttm->state = tt_unpopulated;
}