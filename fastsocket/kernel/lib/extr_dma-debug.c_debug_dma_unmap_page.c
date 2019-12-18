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
struct dma_debug_entry {size_t size; int direction; int /*<<< orphan*/  type; int /*<<< orphan*/  dev_addr; struct device* dev; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  check_unmap (struct dma_debug_entry*) ; 
 int /*<<< orphan*/  dma_debug_page ; 
 int /*<<< orphan*/  dma_debug_single ; 
 int /*<<< orphan*/  global_disable ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void debug_dma_unmap_page(struct device *dev, dma_addr_t addr,
			  size_t size, int direction, bool map_single)
{
	struct dma_debug_entry ref = {
		.type           = dma_debug_page,
		.dev            = dev,
		.dev_addr       = addr,
		.size           = size,
		.direction      = direction,
	};

	if (unlikely(global_disable))
		return;

	if (map_single)
		ref.type = dma_debug_single;

	check_unmap(&ref);
}