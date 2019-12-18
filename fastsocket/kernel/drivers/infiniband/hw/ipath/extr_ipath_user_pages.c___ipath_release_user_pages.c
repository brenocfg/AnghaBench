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

/* Variables and functions */
 int /*<<< orphan*/  MM ; 
 int /*<<< orphan*/  ipath_cdbg (int /*<<< orphan*/ ,char*,unsigned long,unsigned long,struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  set_page_dirty_lock (struct page*) ; 

__attribute__((used)) static void __ipath_release_user_pages(struct page **p, size_t num_pages,
				   int dirty)
{
	size_t i;

	for (i = 0; i < num_pages; i++) {
		ipath_cdbg(MM, "%lu/%lu put_page %p\n", (unsigned long) i,
			   (unsigned long) num_pages, p[i]);
		if (dirty)
			set_page_dirty_lock(p[i]);
		put_page(p[i]);
	}
}