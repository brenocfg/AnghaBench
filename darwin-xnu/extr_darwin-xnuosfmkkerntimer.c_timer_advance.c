#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  TYPE_1__* timer_t ;
struct TYPE_3__ {int /*<<< orphan*/  all_bits; } ;

/* Variables and functions */

__attribute__((used)) static void
timer_advance(timer_t timer, uint64_t delta)
{
#if defined(__LP64__)
	timer->all_bits += delta;
#else /* defined(__LP64__) */
	extern void timer_advance_internal_32(timer_t timer, uint32_t high,
			uint32_t low);
	uint64_t low = delta + timer->low_bits;
	if (low >> 32) {
		timer_advance_internal_32(timer,
				(uint32_t)(timer->high_bits + (low >> 32)), (uint32_t)low);
	} else {
		timer->low_bits = (uint32_t)low;
	}
#endif /* defined(__LP64__) */
}