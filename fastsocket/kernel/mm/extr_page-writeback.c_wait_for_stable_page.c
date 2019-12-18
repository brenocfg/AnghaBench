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
struct page {int dummy; } ;
struct backing_dev_info {int dummy; } ;
struct address_space {TYPE_2__* host; struct backing_dev_info* backing_dev_info; } ;
struct TYPE_4__ {TYPE_1__* i_sb; } ;
struct TYPE_3__ {int s_flags; } ;

/* Variables and functions */
 int MS_SNAP_STABLE ; 
 int /*<<< orphan*/  bdi_cap_stable_pages_required (struct backing_dev_info*) ; 
 struct address_space* page_mapping (struct page*) ; 
 int /*<<< orphan*/  wait_on_page_writeback (struct page*) ; 

void wait_for_stable_page(struct page *page)
{
	struct address_space *mapping = page_mapping(page);
	struct backing_dev_info *bdi = mapping->backing_dev_info;

	if (!bdi_cap_stable_pages_required(bdi))
		return;
#ifdef CONFIG_NEED_BOUNCE_POOL
	if (mapping->host->i_sb->s_flags & MS_SNAP_STABLE)
		return;
#endif /* CONFIG_NEED_BOUNCE_POOL */

	wait_on_page_writeback(page);
}