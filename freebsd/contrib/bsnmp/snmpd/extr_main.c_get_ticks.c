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
struct timeval {unsigned long long tv_sec; unsigned long long tv_usec; } ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 scalar_t__ gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 

uint64_t
get_ticks(void)
{
	struct timeval tv;
	uint64_t ret;

	if (gettimeofday(&tv, NULL))
		abort();
	ret = tv.tv_sec * 100ULL + tv.tv_usec / 10000ULL;
	return (ret);
}