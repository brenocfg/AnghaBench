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
struct fscache_cookie {int /*<<< orphan*/  stores_lock; int /*<<< orphan*/  stores; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (void**) ; 
 int /*<<< orphan*/  FSCACHE_COOKIE_PENDING_TAG ; 
 int /*<<< orphan*/  _enter (char*) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 int /*<<< orphan*/  page_cache_release (void*) ; 
 int /*<<< orphan*/  radix_tree_delete (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int radix_tree_gang_lookup_tag (int /*<<< orphan*/ *,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void fscache_invalidate_writes(struct fscache_cookie *cookie)
{
	struct page *page;
	void *results[16];
	int n, i;

	_enter("");

	for (;;) {
		spin_lock(&cookie->stores_lock);
		n = radix_tree_gang_lookup_tag(&cookie->stores, results, 0,
					       ARRAY_SIZE(results),
					       FSCACHE_COOKIE_PENDING_TAG);
		if (n == 0) {
			spin_unlock(&cookie->stores_lock);
			break;
		}

		for (i = n - 1; i >= 0; i--) {
			page = results[i];
			radix_tree_delete(&cookie->stores, page->index);
		}

		spin_unlock(&cookie->stores_lock);

		for (i = n - 1; i >= 0; i--)
			page_cache_release(results[i]);
	}

	_leave("");
}