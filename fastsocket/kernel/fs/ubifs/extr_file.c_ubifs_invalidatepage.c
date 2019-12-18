#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ubifs_info {int /*<<< orphan*/  dirty_pg_cnt; } ;
struct page {TYPE_1__* mapping; } ;
struct inode {TYPE_2__* i_sb; } ;
struct TYPE_4__ {struct ubifs_info* s_fs_info; } ;
struct TYPE_3__ {struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPageChecked (struct page*) ; 
 int /*<<< orphan*/  ClearPagePrivate (struct page*) ; 
 scalar_t__ PageChecked (struct page*) ; 
 int /*<<< orphan*/  PagePrivate (struct page*) ; 
 int /*<<< orphan*/  atomic_long_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_existing_page_budget (struct ubifs_info*) ; 
 int /*<<< orphan*/  release_new_page_budget (struct ubifs_info*) ; 
 int /*<<< orphan*/  ubifs_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ubifs_invalidatepage(struct page *page, unsigned long offset)
{
	struct inode *inode = page->mapping->host;
	struct ubifs_info *c = inode->i_sb->s_fs_info;

	ubifs_assert(PagePrivate(page));
	if (offset)
		/* Partial page remains dirty */
		return;

	if (PageChecked(page))
		release_new_page_budget(c);
	else
		release_existing_page_budget(c);

	atomic_long_dec(&c->dirty_pg_cnt);
	ClearPagePrivate(page);
	ClearPageChecked(page);
}