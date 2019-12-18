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
struct intc_handle_int {unsigned int irq; } ;

/* Variables and functions */

__attribute__((used)) static struct intc_handle_int *intc_find_irq(struct intc_handle_int *hp,
					     unsigned int nr_hp,
					     unsigned int irq)
{
	int i;

	/* this doesn't scale well, but...
	 *
	 * this function should only be used for cerain uncommon
	 * operations such as intc_set_priority() and intc_set_sense()
	 * and in those rare cases performance doesn't matter that much.
	 * keeping the memory footprint low is more important.
	 *
	 * one rather simple way to speed this up and still keep the
	 * memory footprint down is to make sure the array is sorted
	 * and then perform a bisect to lookup the irq.
	 */

	for (i = 0; i < nr_hp; i++) {
		if ((hp + i)->irq != irq)
			continue;

		return hp + i;
	}

	return NULL;
}