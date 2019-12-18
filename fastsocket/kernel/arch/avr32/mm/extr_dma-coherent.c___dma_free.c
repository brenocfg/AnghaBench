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
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int PAGE_ALIGN (size_t) ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  __free_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __dma_free(struct device *dev, size_t size,
		       struct page *page, dma_addr_t handle)
{
	struct page *end = page + (PAGE_ALIGN(size) >> PAGE_SHIFT);

	while (page < end)
		__free_page(page++);
}