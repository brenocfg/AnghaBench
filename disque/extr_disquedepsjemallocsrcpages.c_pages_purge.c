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

bool
pages_purge(void *addr, size_t size)
{
	bool unzeroed;

#ifdef _WIN32
	VirtualAlloc(addr, size, MEM_RESET, PAGE_READWRITE);
	unzeroed = true;
#elif defined(JEMALLOC_HAVE_MADVISE)
#  ifdef JEMALLOC_PURGE_MADVISE_DONTNEED
#    define JEMALLOC_MADV_PURGE MADV_DONTNEED
#    define JEMALLOC_MADV_ZEROS true
#  elif defined(JEMALLOC_PURGE_MADVISE_FREE)
#    define JEMALLOC_MADV_PURGE MADV_FREE
#    define JEMALLOC_MADV_ZEROS false
#  else
#    error "No madvise(2) flag defined for purging unused dirty pages."
#  endif
	int err = madvise(addr, size, JEMALLOC_MADV_PURGE);
	unzeroed = (!JEMALLOC_MADV_ZEROS || err != 0);
#  undef JEMALLOC_MADV_PURGE
#  undef JEMALLOC_MADV_ZEROS
#else
	/* Last resort no-op. */
	unzeroed = true;
#endif
	return (unzeroed);
}