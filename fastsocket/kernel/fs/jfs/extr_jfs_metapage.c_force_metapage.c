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
struct page {int dummy; } ;
struct metapage {int /*<<< orphan*/  flag; struct page* page; } ;

/* Variables and functions */
 int /*<<< orphan*/  META_forcewrite ; 
 int /*<<< orphan*/  META_sync ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jfs_info (char*,struct metapage*) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int /*<<< orphan*/  page_cache_get (struct page*) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 
 int /*<<< orphan*/  write_one_page (struct page*,int) ; 

void force_metapage(struct metapage *mp)
{
	struct page *page = mp->page;
	jfs_info("force_metapage: mp = 0x%p", mp);
	set_bit(META_forcewrite, &mp->flag);
	clear_bit(META_sync, &mp->flag);
	page_cache_get(page);
	lock_page(page);
	set_page_dirty(page);
	write_one_page(page, 1);
	clear_bit(META_forcewrite, &mp->flag);
	page_cache_release(page);
}