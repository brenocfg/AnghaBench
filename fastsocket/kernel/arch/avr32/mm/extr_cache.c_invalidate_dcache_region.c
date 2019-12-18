#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned long linesz; } ;
struct TYPE_4__ {TYPE_1__ dcache; } ;

/* Variables and functions */
 TYPE_2__ boot_cpu_data ; 
 int /*<<< orphan*/  flush_dcache_line (void*) ; 
 int /*<<< orphan*/  flush_write_buffer () ; 
 int /*<<< orphan*/  invalidate_dcache_line (void*) ; 

void invalidate_dcache_region(void *start, size_t size)
{
	unsigned long v, begin, end, linesz, mask;

	linesz = boot_cpu_data.dcache.linesz;
	mask = linesz - 1;

	/* when first and/or last cachelines are shared, flush them
	 * instead of invalidating ... never discard valid data!
	 */
	begin = (unsigned long)start;
	end = begin + size;

	if (begin & mask) {
		flush_dcache_line(start);
		begin += linesz;
	}
	if (end & mask) {
		flush_dcache_line((void *)end);
		end &= ~mask;
	}

	/* remaining cachelines only need invalidation */
	for (v = begin; v < end; v += linesz)
		invalidate_dcache_line((void *)v);
	flush_write_buffer();
}