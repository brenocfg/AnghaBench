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
typedef  unsigned int uint64_t ;
typedef  unsigned int addr64_t ;
struct TYPE_2__ {unsigned int cache_linesize; } ;

/* Variables and functions */
 int /*<<< orphan*/  __clflush (void*) ; 
 TYPE_1__* cpuid_info () ; 
 int /*<<< orphan*/  dcache_incoherent_io_flush64 (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  mfence () ; 

void
flush_dcache64(addr64_t addr, unsigned count, int phys)
{
	if (phys) {
		dcache_incoherent_io_flush64(addr, count);
	}
	else {
		uint64_t  linesize = cpuid_info()->cache_linesize;
		addr64_t  bound = (addr + count + linesize -1) & ~(linesize - 1);
		mfence();
		while (addr < bound) {
			__clflush((void *) (uintptr_t) addr);
			addr += linesize;
		}
		mfence();
	}
}