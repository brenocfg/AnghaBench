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
 int /*<<< orphan*/  drm_clflush_virt_range (char*,unsigned long) ; 
 unsigned long round_down (unsigned long,int) ; 
 unsigned long round_up (unsigned long,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void
shmem_clflush_swizzled_range(char *addr, unsigned long length,
			     bool swizzled)
{
	if (unlikely(swizzled)) {
		unsigned long start = (unsigned long) addr;
		unsigned long end = (unsigned long) addr + length;

		/* For swizzling simply ensure that we always flush both
		 * channels. Lame, but simple and it works. Swizzled
		 * pwrite/pread is far from a hotpath - current userspace
		 * doesn't use it at all. */
		start = round_down(start, 128);
		end = round_up(end, 128);

		drm_clflush_virt_range((void *)start, end - start);
	} else {
		drm_clflush_virt_range(addr, length);
	}

}