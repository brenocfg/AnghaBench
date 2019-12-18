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
 int /*<<< orphan*/  clean_dcache_line (void*) ; 
 int /*<<< orphan*/  flush_write_buffer () ; 
 int /*<<< orphan*/  invalidate_icache_line (void*) ; 

__attribute__((used)) static inline void __flush_icache_range(unsigned long start, unsigned long end)
{
	unsigned long v, linesz;

	linesz = boot_cpu_data.dcache.linesz;
	for (v = start; v < end; v += linesz) {
		clean_dcache_line((void *)v);
		invalidate_icache_line((void *)v);
	}

	flush_write_buffer();
}