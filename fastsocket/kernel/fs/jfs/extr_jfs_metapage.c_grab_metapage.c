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
struct metapage {int /*<<< orphan*/  page; int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int /*<<< orphan*/  jfs_info (char*,struct metapage*) ; 
 int /*<<< orphan*/  lock_metapage (struct metapage*) ; 
 int /*<<< orphan*/  lock_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_cache_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_page (int /*<<< orphan*/ ) ; 

void grab_metapage(struct metapage * mp)
{
	jfs_info("grab_metapage: mp = 0x%p", mp);
	page_cache_get(mp->page);
	lock_page(mp->page);
	mp->count++;
	lock_metapage(mp);
	unlock_page(mp->page);
}