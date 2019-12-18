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
struct aggregator {scalar_t__ is_active; } ;

/* Variables and functions */
 struct aggregator* __get_next_agg (struct aggregator*) ; 

__attribute__((used)) static struct aggregator *__get_active_agg(struct aggregator *aggregator)
{
	struct aggregator *retval = NULL;

	for (; aggregator; aggregator = __get_next_agg(aggregator)) {
		if (aggregator->is_active) {
			retval = aggregator;
			break;
		}
	}

	return retval;
}