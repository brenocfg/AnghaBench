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
struct ps3_system_bus_device {int /*<<< orphan*/  d_region; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  free_pages (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (size_t) ; 
 struct ps3_system_bus_device* ps3_dev_to_system_bus_dev (struct device*) ; 
 int /*<<< orphan*/  ps3_dma_unmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void ps3_free_coherent(struct device *_dev, size_t size, void *vaddr,
	dma_addr_t dma_handle)
{
	struct ps3_system_bus_device *dev = ps3_dev_to_system_bus_dev(_dev);

	ps3_dma_unmap(dev->d_region, dma_handle, size);
	free_pages((unsigned long)vaddr, get_order(size));
}