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
typedef  int uint64_t ;

/* Variables and functions */
 int CVMX_CACHE_LINE_MASK ; 
 scalar_t__ CVMX_CACHE_LINE_SIZE ; 
 scalar_t__ cvmx_l2c_lock_line (int) ; 

int cvmx_l2c_lock_mem_region(uint64_t start, uint64_t len)
{
	int retval = 0;

	/* Round start/end to cache line boundaries */
	len += start & CVMX_CACHE_LINE_MASK;
	start &= ~CVMX_CACHE_LINE_MASK;
	len = (len + CVMX_CACHE_LINE_MASK) & ~CVMX_CACHE_LINE_MASK;

	while (len) {
		retval += cvmx_l2c_lock_line(start);
		start += CVMX_CACHE_LINE_SIZE;
		len -= CVMX_CACHE_LINE_SIZE;
	}

	return retval;
}