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
struct ttm_tt {scalar_t__ state; scalar_t__ caching_state; int num_pages; int /*<<< orphan*/  page_flags; struct page* swap_storage; TYPE_2__* bdev; struct page** pages; } ;
struct page {int dummy; } ;
typedef  struct page file ;
struct address_space {int dummy; } ;
struct TYPE_6__ {struct address_space* i_mapping; } ;
struct TYPE_5__ {TYPE_1__* driver; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* ttm_tt_unpopulate ) (struct ttm_tt*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IS_ERR (struct page*) ; 
 int PAGE_SHIFT ; 
 int PTR_ERR (struct page*) ; 
 int /*<<< orphan*/  TTM_PAGE_FLAG_PERSISTENT_SWAP ; 
 int /*<<< orphan*/  TTM_PAGE_FLAG_SWAPPED ; 
 int /*<<< orphan*/  copy_highpage (struct page*,struct page*) ; 
 TYPE_3__* file_inode (struct page*) ; 
 int /*<<< orphan*/  fput (struct page*) ; 
 int /*<<< orphan*/  mark_page_accessed (struct page*) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 
 struct page* shmem_file_setup (char*,int,int /*<<< orphan*/ ) ; 
 struct page* shmem_read_mapping_page (struct address_space*,int) ; 
 int /*<<< orphan*/  stub1 (struct ttm_tt*) ; 
 scalar_t__ tt_cached ; 
 scalar_t__ tt_unbound ; 
 scalar_t__ tt_unpopulated ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int ttm_tt_swapout(struct ttm_tt *ttm, struct file *persistent_swap_storage)
{
	struct address_space *swap_space;
	struct file *swap_storage;
	struct page *from_page;
	struct page *to_page;
	int i;
	int ret = -ENOMEM;

	BUG_ON(ttm->state != tt_unbound && ttm->state != tt_unpopulated);
	BUG_ON(ttm->caching_state != tt_cached);

	if (!persistent_swap_storage) {
		swap_storage = shmem_file_setup("ttm swap",
						ttm->num_pages << PAGE_SHIFT,
						0);
		if (unlikely(IS_ERR(swap_storage))) {
			pr_err("Failed allocating swap storage\n");
			return PTR_ERR(swap_storage);
		}
	} else
		swap_storage = persistent_swap_storage;

	swap_space = file_inode(swap_storage)->i_mapping;

	for (i = 0; i < ttm->num_pages; ++i) {
		from_page = ttm->pages[i];
		if (unlikely(from_page == NULL))
			continue;
		to_page = shmem_read_mapping_page(swap_space, i);
		if (unlikely(IS_ERR(to_page))) {
			ret = PTR_ERR(to_page);
			goto out_err;
		}
		copy_highpage(to_page, from_page);
		set_page_dirty(to_page);
		mark_page_accessed(to_page);
		page_cache_release(to_page);
	}

	ttm->bdev->driver->ttm_tt_unpopulate(ttm);
	ttm->swap_storage = swap_storage;
	ttm->page_flags |= TTM_PAGE_FLAG_SWAPPED;
	if (persistent_swap_storage)
		ttm->page_flags |= TTM_PAGE_FLAG_PERSISTENT_SWAP;

	return 0;
out_err:
	if (!persistent_swap_storage)
		fput(swap_storage);

	return ret;
}