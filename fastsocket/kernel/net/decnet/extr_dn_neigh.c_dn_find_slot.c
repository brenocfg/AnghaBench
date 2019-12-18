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

/* Variables and functions */

__attribute__((used)) static char *dn_find_slot(char *base, int max, int priority)
{
	int i;
	unsigned char *min = NULL;

	base += 6; /* skip first id */

	for(i = 0; i < max; i++) {
		if (!min || (*base < *min))
			min = base;
		base += 7; /* find next priority */
	}

	if (!min)
		return NULL;

	return (*min < priority) ? (min - 6) : NULL;
}