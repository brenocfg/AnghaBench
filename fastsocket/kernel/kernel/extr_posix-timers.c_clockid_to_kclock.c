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
struct k_clock {int /*<<< orphan*/  clock_getres; } ;
typedef  size_t clockid_t ;

/* Variables and functions */
 size_t const CLOCKFD ; 
 size_t const CLOCKFD_MASK ; 
 size_t const MAX_CLOCKS ; 
 struct k_clock clock_posix_cpu ; 
 struct k_clock clock_posix_dynamic ; 
 struct k_clock* posix_clocks ; 

__attribute__((used)) static struct k_clock *clockid_to_kclock(const clockid_t id)
{
	if (id < 0)
		return (id & CLOCKFD_MASK) == CLOCKFD ?
			&clock_posix_dynamic : &clock_posix_cpu;

	if (id >= MAX_CLOCKS || !posix_clocks[id].clock_getres)
		return NULL;
	return &posix_clocks[id];
}