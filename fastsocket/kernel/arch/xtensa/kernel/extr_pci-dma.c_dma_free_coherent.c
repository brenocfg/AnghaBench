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
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 long XCHAL_KSEG_BYPASS_VADDR ; 
 long XCHAL_KSEG_CACHED_VADDR ; 
 long XCHAL_KSEG_SIZE ; 
 int /*<<< orphan*/  free_pages (long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (size_t) ; 

void dma_free_coherent(struct device *hwdev, size_t size,
			 void *vaddr, dma_addr_t dma_handle)
{
	long addr=(long)vaddr+XCHAL_KSEG_CACHED_VADDR-XCHAL_KSEG_BYPASS_VADDR;

	if (addr < 0 || addr >= XCHAL_KSEG_SIZE)
		BUG();

	free_pages(addr, get_order(size));
}