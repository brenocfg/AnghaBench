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
typedef  unsigned int addr64_t ;
struct TYPE_2__ {unsigned int cache_linesize; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHYSMAP_PTOV (unsigned int) ; 
 int /*<<< orphan*/  __clflush (int /*<<< orphan*/ ) ; 
 TYPE_1__* cpuid_info () ; 
 int /*<<< orphan*/  mfence () ; 

void dcache_incoherent_io_store64(addr64_t pa, unsigned int count)
{
	addr64_t  linesize = cpuid_info()->cache_linesize;
	addr64_t  bound = (pa + count + linesize - 1) & ~(linesize - 1);

	mfence();

	while (pa < bound) {
		__clflush(PHYSMAP_PTOV(pa));
		pa += linesize;
	}

	mfence();
}