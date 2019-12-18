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
struct dma_attrs {int dummy; } ;
struct device {int dummy; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 unsigned long PAGE_MASK ; 
 int /*<<< orphan*/  sba_map_page (struct device*,int /*<<< orphan*/ ,unsigned long,size_t,int,struct dma_attrs*) ; 
 int /*<<< orphan*/  virt_to_page (void*) ; 

__attribute__((used)) static dma_addr_t sba_map_single_attrs(struct device *dev, void *addr,
				       size_t size, enum dma_data_direction dir,
				       struct dma_attrs *attrs)
{
	return sba_map_page(dev, virt_to_page(addr),
			    (unsigned long)addr & ~PAGE_MASK, size, dir, attrs);
}