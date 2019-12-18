#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ttm_mem_global {int /*<<< orphan*/  kobj; } ;
struct TYPE_6__ {unsigned int max_size; int /*<<< orphan*/  alloc_size; int /*<<< orphan*/  small; } ;
struct TYPE_7__ {int /*<<< orphan*/  kobj; TYPE_1__ options; int /*<<< orphan*/  uc_pool_dma32; int /*<<< orphan*/  wc_pool_dma32; int /*<<< orphan*/  uc_pool; int /*<<< orphan*/  wc_pool; } ;

/* Variables and functions */
 int GFP_DMA32 ; 
 int GFP_HIGHUSER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int GFP_USER ; 
 int /*<<< orphan*/  NUM_PAGES_TO_ALLOC ; 
 int /*<<< orphan*/  SMALL_ALLOCATION ; 
 int /*<<< orphan*/  WARN_ON (TYPE_2__*) ; 
 TYPE_2__* _manager ; 
 int kobject_init_and_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 TYPE_2__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  ttm_page_pool_init_locked (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  ttm_pool_kobj_type ; 
 int /*<<< orphan*/  ttm_pool_mm_shrink_init (TYPE_2__*) ; 
 scalar_t__ unlikely (int) ; 

int ttm_page_alloc_init(struct ttm_mem_global *glob, unsigned max_pages)
{
	int ret;

	WARN_ON(_manager);

	pr_info("Initializing pool allocator\n");

	_manager = kzalloc(sizeof(*_manager), GFP_KERNEL);

	ttm_page_pool_init_locked(&_manager->wc_pool, GFP_HIGHUSER, "wc");

	ttm_page_pool_init_locked(&_manager->uc_pool, GFP_HIGHUSER, "uc");

	ttm_page_pool_init_locked(&_manager->wc_pool_dma32,
				  GFP_USER | GFP_DMA32, "wc dma");

	ttm_page_pool_init_locked(&_manager->uc_pool_dma32,
				  GFP_USER | GFP_DMA32, "uc dma");

	_manager->options.max_size = max_pages;
	_manager->options.small = SMALL_ALLOCATION;
	_manager->options.alloc_size = NUM_PAGES_TO_ALLOC;

	ret = kobject_init_and_add(&_manager->kobj, &ttm_pool_kobj_type,
				   &glob->kobj, "pool");
	if (unlikely(ret != 0)) {
		kobject_put(&_manager->kobj);
		_manager = NULL;
		return ret;
	}

	ttm_pool_mm_shrink_init(_manager);

	return 0;
}