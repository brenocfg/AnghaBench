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
struct TYPE_2__ {int /*<<< orphan*/  current_memory_agp; } ;

/* Variables and functions */
 int /*<<< orphan*/  __free_pages (struct page*,int) ; 
 TYPE_1__* agp_bridge ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  set_pages_wb (struct page*,int) ; 

__attribute__((used)) static void i8xx_destroy_pages(struct page *page)
{
	if (page == NULL)
		return;

	set_pages_wb(page, 4);
	put_page(page);
	__free_pages(page, 2);
	atomic_dec(&agp_bridge->current_memory_agp);
}