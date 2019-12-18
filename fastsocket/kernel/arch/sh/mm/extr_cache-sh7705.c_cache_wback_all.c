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
struct TYPE_3__ {unsigned long ways; unsigned long sets; unsigned long entry_shift; scalar_t__ way_incr; scalar_t__ linesz; } ;
struct TYPE_4__ {TYPE_1__ dcache; } ;

/* Variables and functions */
 unsigned long CACHE_OC_ADDRESS_ARRAY ; 
 int SH_CACHE_UPDATED ; 
 int SH_CACHE_VALID ; 
 unsigned long ctrl_inl (unsigned long) ; 
 int /*<<< orphan*/  ctrl_outl (unsigned long,unsigned long) ; 
 TYPE_2__ current_cpu_data ; 

__attribute__((used)) static inline void cache_wback_all(void)
{
	unsigned long ways, waysize, addrstart;

	ways = current_cpu_data.dcache.ways;
	waysize = current_cpu_data.dcache.sets;
	waysize <<= current_cpu_data.dcache.entry_shift;

	addrstart = CACHE_OC_ADDRESS_ARRAY;

	do {
		unsigned long addr;

		for (addr = addrstart;
		     addr < addrstart + waysize;
		     addr += current_cpu_data.dcache.linesz) {
			unsigned long data;
			int v = SH_CACHE_UPDATED | SH_CACHE_VALID;

			data = ctrl_inl(addr);

			if ((data & v) == v)
				ctrl_outl(data & ~v, addr);

		}

		addrstart += current_cpu_data.dcache.way_incr;
	} while (--ways);
}