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
struct fscache_cookie {int /*<<< orphan*/  stores; } ;

/* Variables and functions */
 void* radix_tree_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

bool __fscache_check_page_write(struct fscache_cookie *cookie, struct page *page)
{
	void *val;

	rcu_read_lock();
	val = radix_tree_lookup(&cookie->stores, page->index);
	rcu_read_unlock();

	return val != NULL;
}