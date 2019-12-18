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
struct dma_debug_entry {scalar_t__ dev; scalar_t__ dev_addr; scalar_t__ size; } ;

/* Variables and functions */

__attribute__((used)) static bool containing_match(struct dma_debug_entry *a,
			     struct dma_debug_entry *b)
{
	if (a->dev != b->dev)
		return false;

	if ((b->dev_addr <= a->dev_addr) &&
	    ((b->dev_addr + b->size) >= (a->dev_addr + a->size)))
		return true;

	return false;
}