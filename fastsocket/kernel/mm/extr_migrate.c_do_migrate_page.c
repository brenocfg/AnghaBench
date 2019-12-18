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
struct address_space {int dummy; } ;
typedef  enum migrate_mode { ____Placeholder_migrate_mode } migrate_mode ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageWriteback (struct page*) ; 
 int /*<<< orphan*/  migrate_page_copy (struct page*,struct page*) ; 
 int migrate_page_move_mapping (struct address_space*,struct page*,struct page*,int /*<<< orphan*/ *,int) ; 

int do_migrate_page(struct address_space *mapping,
		struct page *newpage, struct page *page, enum migrate_mode mode)
{
	int rc;

	BUG_ON(PageWriteback(page));	/* Writeback must be complete */

	rc = migrate_page_move_mapping(mapping, newpage, page, NULL, mode);

	if (rc)
		return rc;

	migrate_page_copy(newpage, page);
	return 0;
}