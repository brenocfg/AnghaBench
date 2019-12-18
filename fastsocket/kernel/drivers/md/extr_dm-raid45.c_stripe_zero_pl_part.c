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
struct stripe {int dummy; } ;
struct page_list {struct page_list* next; int /*<<< orphan*/  page; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PL (struct stripe*,int) ; 
 unsigned int SECTORS_PER_PAGE ; 
 unsigned int chunk_pages (unsigned int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_address (int /*<<< orphan*/ ) ; 
 struct page_list* pl_elem (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void stripe_zero_pl_part(struct stripe *stripe, int p,
				unsigned start, unsigned count)
{
	unsigned o = start / SECTORS_PER_PAGE, pages = chunk_pages(count);
	/* Get offset into the page_list. */
	struct page_list *pl = pl_elem(PL(stripe, p), o);

	BUG_ON(!pl);
	while (pl && pages--) {
		BUG_ON(!pl->page);
		memset(page_address(pl->page), 0, PAGE_SIZE);
		pl = pl->next;
	}
}