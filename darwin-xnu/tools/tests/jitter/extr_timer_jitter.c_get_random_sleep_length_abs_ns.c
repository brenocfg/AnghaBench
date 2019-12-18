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
typedef  int uint32_t ;

/* Variables and functions */
 scalar_t__ random () ; 

uint64_t 
get_random_sleep_length_abs_ns(uint64_t min_sleep_ns, uint64_t max_sleep_ns)
{
	uint64_t tmp;

	tmp = (uint32_t)random();
	tmp <<= 32;
	tmp |= (uint32_t)random();

	/* Now use the random number to sleep amount within the window */
	tmp %= (max_sleep_ns - min_sleep_ns);

	return min_sleep_ns + tmp;
}