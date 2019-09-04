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
typedef  int /*<<< orphan*/  volatile uint64_t ;

/* Variables and functions */
 scalar_t__ _COMM_PAGE_CONT_TIMEBASE ; 

__attribute__((visibility("hidden")))
uint64_t
_mach_continuous_time_base(void)
{
#if !defined(__x86_64__) && !defined(__arm64__)
	// Deal with the lack of 64-bit loads on arm32 (see mach_approximate_time.s)
	while(1) {
		volatile uint64_t *base_ptr = (volatile uint64_t*)_COMM_PAGE_CONT_TIMEBASE;
		uint64_t read1, read2;
		read1 = *base_ptr;
#if defined(__arm__)
		__asm__ volatile("dsb sy" ::: "memory");
#elif defined(__i386__)
		__asm__ volatile("lfence" ::: "memory");
#else
#error "unsupported arch"
#endif
		read2 = *base_ptr;

		if(__builtin_expect((read1 == read2), 1))
			return read1;
	}
#else // 64-bit
	return *(volatile uint64_t*)_COMM_PAGE_CONT_TIMEBASE;
#endif // 64-bit
}