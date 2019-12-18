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
 int /*<<< orphan*/  __dma_free (struct device*,size_t,struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (void*) ; 
 struct page* phys_to_page (int /*<<< orphan*/ ) ; 

void dma_free_writecombine(struct device *dev, size_t size,
			   void *cpu_addr, dma_addr_t handle)
{
	struct page *page;

	iounmap(cpu_addr);

	page = phys_to_page(handle);
	__dma_free(dev, size, page, handle);
}