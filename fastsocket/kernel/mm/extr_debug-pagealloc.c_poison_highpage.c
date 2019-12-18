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

__attribute__((used)) static void poison_highpage(struct page *page)
{
	/*
	 * Page poisoning for highmem pages is not implemented.
	 *
	 * This can be called from interrupt contexts.
	 * So we need to create a new kmap_atomic slot for this
	 * application and it will need interrupt protection.
	 */
}