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
 unsigned long CACHED_BOOTROM ; 
 unsigned long PAGE_MASK ; 

__attribute__((used)) static inline void
flush_etrax_cacherange(void *startadr, int length)
{
	/* CACHED_BOOTROM is mapped to the boot-rom area (cached) which
	 * we can use to get fast dummy-reads of cachelines
	 */

	volatile short *flushadr = (volatile short *)(((unsigned long)startadr & ~PAGE_MASK) |
						      CACHED_BOOTROM);

	length = length > 8192 ? 8192 : length;  /* No need to flush more than cache size */

	while(length > 0) {
		*flushadr; /* dummy read to flush */
		flushadr += (32/sizeof(short));  /* a cacheline is 32 bytes */
		length -= 32;
	}
}