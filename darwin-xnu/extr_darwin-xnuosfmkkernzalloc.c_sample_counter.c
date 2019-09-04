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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  OSCompareAndSwap (scalar_t__,scalar_t__,scalar_t__ volatile*) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static inline boolean_t
sample_counter(volatile uint32_t * count_p, uint32_t factor)
{
	uint32_t old_count, new_count;
	boolean_t rolled_over;

	do {
		new_count = old_count = *count_p;

		if (++new_count >= factor) {
			rolled_over = TRUE;
			new_count = 0;
		} else {
			rolled_over = FALSE;
		}

	} while (!OSCompareAndSwap(old_count, new_count, count_p));

	return rolled_over;
}