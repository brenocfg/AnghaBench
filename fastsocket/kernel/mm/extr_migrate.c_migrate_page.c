#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct address_space {int dummy; } ;
typedef  enum migrate_mode { ____Placeholder_migrate_mode } migrate_mode ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int MIGRATE_ASYNC ; 
 int MIGRATE_SYNC ; 
 int PF_SWAPWRITE ; 
 TYPE_1__* current ; 
 int do_migrate_page (struct address_space*,struct page*,struct page*,int) ; 

int migrate_page(struct address_space *mapping,
		struct page *newpage, struct page *page)
{
	enum migrate_mode mode = MIGRATE_ASYNC;

	/*
	 * RHEL: we pass in async vs synchronous migration by overloading
	 * PF_SWAPWRITE in current flags, since adding a parameter here
	 * would break the kABI.  This does lose us MIGRATE_SYNC_LIGHT.
	 */
	if (current->flags & PF_SWAPWRITE)
		mode = MIGRATE_SYNC;

	return do_migrate_page(mapping, newpage, page, mode);
}