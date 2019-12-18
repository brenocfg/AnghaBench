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
struct monitor_result {scalar_t__ overflow; scalar_t__ cost; } ;

/* Variables and functions */

__attribute__((used)) static int monitor_result_reverse_cmp(const void *a, const void *b)
{
	const struct monitor_result *s1 = a;
	const struct monitor_result *s2 = b;

	/* Compare the overflow firstly */
	if (s1->overflow < s2->overflow) {
		return 1;
	} else if (s1->overflow > s2->overflow) {
		return -1;
	} else {		
		if (s1->cost < s2->cost) {
			return 1;
		} else if (s1->cost > s2->cost) {
			return -1;
		} else {
			return 0;
		}	
	}
}