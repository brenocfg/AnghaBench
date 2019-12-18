#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned int dcache_size; unsigned int dcache_line; scalar_t__ use_dcache; } ;

/* Variables and functions */
 int /*<<< orphan*/  __disable_dcache () ; 
 int /*<<< orphan*/  __enable_dcache () ; 
 int /*<<< orphan*/  __invalidate_dcache (unsigned int) ; 
 TYPE_1__ cpuinfo ; 
 int /*<<< orphan*/  local_irq_restore (unsigned int) ; 
 int /*<<< orphan*/  local_irq_save (unsigned int) ; 

void __invalidate_dcache_all(void)
{
	unsigned int i;
	unsigned flags;

	if (cpuinfo.use_dcache) {
		local_irq_save(flags);
		__disable_dcache();

		/*
		 * Just loop through cache size and invalidate,
		 * no need to add CACHE_BASE address
		 */
		for (i = 0; i < cpuinfo.dcache_size;
			i += cpuinfo.dcache_line)
				__invalidate_dcache(i);

		__enable_dcache();
		local_irq_restore(flags);
	}
}