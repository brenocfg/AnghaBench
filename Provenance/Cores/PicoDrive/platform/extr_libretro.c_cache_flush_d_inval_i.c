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

/* Variables and functions */
 int MS_CACHE_ONLY ; 
 int MS_INVALIDATE_ICACHE ; 
 int MS_SYNC ; 
 int /*<<< orphan*/  __clear_cache (void*,void*) ; 
 int /*<<< orphan*/  msync (void*,int,int) ; 
 int /*<<< orphan*/  sys_dcache_flush (void*,size_t) ; 
 int /*<<< orphan*/  sys_icache_invalidate (void*,size_t) ; 

void cache_flush_d_inval_i(void *start, void *end)
{
#ifdef __arm__
#if defined(__BLACKBERRY_QNX__)
	msync(start, end - start, MS_SYNC | MS_CACHE_ONLY | MS_INVALIDATE_ICACHE);
#elif defined(__MACH__)
	size_t len = (char *)end - (char *)start;
	sys_dcache_flush(start, len);
	sys_icache_invalidate(start, len);
#else
	__clear_cache(start, end);
#endif
#endif
}