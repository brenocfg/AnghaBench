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
struct page {int /*<<< orphan*/  lru; } ;
struct list_head {int dummy; } ;
struct address_space {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (struct list_head*) ; 
 struct page* list_to_page (struct list_head*) ; 
 int /*<<< orphan*/  read_cache_pages_invalidate_page (struct address_space*,struct page*) ; 

__attribute__((used)) static void read_cache_pages_invalidate_pages(struct address_space *mapping,
					      struct list_head *pages)
{
	struct page *victim;

	while (!list_empty(pages)) {
		victim = list_to_page(pages);
		list_del(&victim->lru);
		read_cache_pages_invalidate_page(mapping, victim);
	}
}