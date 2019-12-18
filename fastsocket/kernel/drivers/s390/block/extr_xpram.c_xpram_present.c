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

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ __get_free_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int xpram_page_in (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xpram_present(void)
{
	unsigned long mem_page;
	int rc;

	mem_page = (unsigned long) __get_free_page(GFP_KERNEL);
	if (!mem_page)
		return -ENOMEM;
	rc = xpram_page_in(mem_page, 0);
	free_page(mem_page);
	return rc ? -ENXIO : 0;
}