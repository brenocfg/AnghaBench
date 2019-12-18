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
typedef  unsigned long long uint64_t ;
typedef  unsigned long long uint32_t ;
struct timeval {unsigned long long tv_sec; unsigned long long tv_usec; } ;

/* Variables and functions */
 unsigned long long start_tick ; 

__attribute__((used)) static uint32_t
ticks_get_timeval(struct timeval *tv)
{
	uint64_t v;

	if (tv->tv_sec != 0 || tv->tv_usec != 0) {
		v = 100ULL * tv->tv_sec + tv->tv_usec / 10000ULL;
		if (v > start_tick)
			return (v - start_tick);
	}
	return (0);
}