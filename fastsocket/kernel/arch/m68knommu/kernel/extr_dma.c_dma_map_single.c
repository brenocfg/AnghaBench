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
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  flush_dcache_range (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  virt_to_phys (void*) ; 

dma_addr_t dma_map_single(struct device *dev, void *addr, size_t size,
			  enum dma_data_direction dir)
{
	dma_addr_t handle = virt_to_phys(addr);
	flush_dcache_range(handle, size);
	return handle;
}