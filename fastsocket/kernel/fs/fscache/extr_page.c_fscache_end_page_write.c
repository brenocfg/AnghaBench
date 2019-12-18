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
struct page {int /*<<< orphan*/  index; } ;
struct fscache_object {int /*<<< orphan*/  lock; struct fscache_cookie* cookie; } ;
struct fscache_cookie {int /*<<< orphan*/  flags; int /*<<< orphan*/  stores_lock; int /*<<< orphan*/  stores; } ;

/* Variables and functions */
 int /*<<< orphan*/  FSCACHE_COOKIE_PENDING_TAG ; 
 int /*<<< orphan*/  FSCACHE_COOKIE_STORING_TAG ; 
 int /*<<< orphan*/  fscache_n_store_radix_deletes ; 
 int /*<<< orphan*/  fscache_stat (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 struct page* radix_tree_delete (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radix_tree_tag_clear (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radix_tree_tag_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fscache_end_page_write(struct fscache_object *object,
				   struct page *page)
{
	struct fscache_cookie *cookie;
	struct page *xpage = NULL;

	spin_lock(&object->lock);
	cookie = object->cookie;
	if (cookie) {
		/* delete the page from the tree if it is now no longer
		 * pending */
		spin_lock(&cookie->stores_lock);
		radix_tree_tag_clear(&cookie->stores, page->index,
				     FSCACHE_COOKIE_STORING_TAG);
		if (!radix_tree_tag_get(&cookie->stores, page->index,
					FSCACHE_COOKIE_PENDING_TAG)) {
			fscache_stat(&fscache_n_store_radix_deletes);
			xpage = radix_tree_delete(&cookie->stores, page->index);
		}
		spin_unlock(&cookie->stores_lock);
		wake_up_bit(&cookie->flags, 0);
	}
	spin_unlock(&object->lock);
	if (xpage)
		page_cache_release(xpage);
}