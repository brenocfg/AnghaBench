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
struct TYPE_2__ {unsigned int icache_size; unsigned int icache_line; scalar_t__ use_icache; } ;

/* Variables and functions */
 int /*<<< orphan*/  __disable_icache () ; 
 int /*<<< orphan*/  __enable_icache () ; 
 int /*<<< orphan*/  __invalidate_icache (unsigned int) ; 
 TYPE_1__ cpuinfo ; 
 int /*<<< orphan*/  local_irq_restore (unsigned int) ; 
 int /*<<< orphan*/  local_irq_save (unsigned int) ; 

void __invalidate_icache_all(void)
{
	unsigned int i;
	unsigned flags;

	if (cpuinfo.use_icache) {
		local_irq_save(flags);
		__disable_icache();

		/* Just loop through cache size and invalidate, no need to add
			CACHE_BASE address */
		for (i = 0; i < cpuinfo.icache_size;
			i += cpuinfo.icache_line)
				__invalidate_icache(i);

		__enable_icache();
		local_irq_restore(flags);
	}
}