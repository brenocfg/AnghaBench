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
struct TYPE_2__ {int icache_line; scalar_t__ icache_size; scalar_t__ use_icache; } ;

/* Variables and functions */
 int /*<<< orphan*/  __disable_icache () ; 
 int /*<<< orphan*/  __enable_icache () ; 
 int /*<<< orphan*/  __invalidate_icache (unsigned int) ; 
 TYPE_1__ cpuinfo ; 
 int /*<<< orphan*/  local_irq_restore (unsigned int) ; 
 int /*<<< orphan*/  local_irq_save (unsigned int) ; 
 unsigned long min (scalar_t__,unsigned long) ; 

void __invalidate_icache_range(unsigned long start, unsigned long end)
{
	unsigned int i;
	unsigned flags;
	unsigned int align;

	if (cpuinfo.use_icache) {
		/*
		 * No need to cover entire cache range,
		 * just cover cache footprint
		 */
		end = min(start + cpuinfo.icache_size, end);
		align = ~(cpuinfo.icache_line - 1);
		start &= align; /* Make sure we are aligned */
		/* Push end up to the next cache line */
		end = ((end & align) + cpuinfo.icache_line);

		local_irq_save(flags);
		__disable_icache();

		for (i = start; i < end; i += cpuinfo.icache_line)
			__invalidate_icache(i);

		__enable_icache();
		local_irq_restore(flags);
	}
}