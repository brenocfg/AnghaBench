#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ppnum_t ;
struct TYPE_4__ {int cache_linesize; } ;
typedef  TYPE_1__ i386_cpu_info_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int PAGE_SIZE ; 
 scalar_t__ PHYSMAP_PTOV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __clflush (void*) ; 
 TYPE_1__* cpuid_info () ; 
 int /*<<< orphan*/  i386_ptob (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mfence () ; 
 int /*<<< orphan*/  ml_set_interrupts_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,TYPE_1__*) ; 

void
cache_flush_page_phys(ppnum_t pa)
{
	boolean_t	istate;
	unsigned char	*cacheline_addr;
	i386_cpu_info_t	*cpuid_infop = cpuid_info();
	int		cacheline_size;
	int		cachelines_to_flush;

	cacheline_size = cpuid_infop->cache_linesize;
	if (cacheline_size == 0)
		panic("cacheline_size=0 cpuid_infop=%p\n", cpuid_infop);
	cachelines_to_flush = PAGE_SIZE/cacheline_size;

	mfence();

	istate = ml_set_interrupts_enabled(FALSE);

	for (cacheline_addr = (unsigned char *)PHYSMAP_PTOV(i386_ptob(pa));
	     cachelines_to_flush > 0;
	     cachelines_to_flush--, cacheline_addr += cacheline_size) {
		__clflush((void *) cacheline_addr);
	}

	(void) ml_set_interrupts_enabled(istate);

	mfence();
}