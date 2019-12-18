#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  kobj; int /*<<< orphan*/ * pools; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_ALL_PAGES ; 
 int NUM_POOLS ; 
 TYPE_1__* _manager ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  ttm_page_pool_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttm_pool_mm_shrink_fini (TYPE_1__*) ; 

void ttm_page_alloc_fini(void)
{
	int i;

	pr_info("Finalizing pool allocator\n");
	ttm_pool_mm_shrink_fini(_manager);

	for (i = 0; i < NUM_POOLS; ++i)
		ttm_page_pool_free(&_manager->pools[i], FREE_ALL_PAGES);

	kobject_put(&_manager->kobj);
	_manager = NULL;
}