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
 int /*<<< orphan*/  unmap_page_from_agp (struct page*) ; 

__attribute__((used)) static int set_pages_array_wb(struct page **pages, int addrinarray)
{
#ifdef TTM_HAS_AGP
	int i;

	for (i = 0; i < addrinarray; i++)
		unmap_page_from_agp(pages[i]);
#endif
	return 0;
}