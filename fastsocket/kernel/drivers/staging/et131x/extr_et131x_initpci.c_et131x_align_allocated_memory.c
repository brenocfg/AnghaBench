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
typedef  int uint64_t ;
struct et131x_adapter {int dummy; } ;

/* Variables and functions */

void et131x_align_allocated_memory(struct et131x_adapter *adapter,
				   uint64_t *phys_addr,
				   uint64_t *offset, uint64_t mask)
{
	uint64_t new_addr;

	*offset = 0;

	new_addr = *phys_addr & ~mask;

	if (new_addr != *phys_addr) {
		/* Move to next aligned block */
		new_addr += mask + 1;
		/* Return offset for adjusting virt addr */
		*offset = new_addr - *phys_addr;
		/* Return new physical address */
		*phys_addr = new_addr;
	}
}