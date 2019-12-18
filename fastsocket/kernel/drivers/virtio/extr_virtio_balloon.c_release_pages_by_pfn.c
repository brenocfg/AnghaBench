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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  __free_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfn_to_page (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  totalram_pages ; 

__attribute__((used)) static void release_pages_by_pfn(const u32 pfns[], unsigned int num)
{
	unsigned int i;

	for (i = 0; i < num; i++) {
		__free_page(pfn_to_page(pfns[i]));
		totalram_pages++;
	}
}