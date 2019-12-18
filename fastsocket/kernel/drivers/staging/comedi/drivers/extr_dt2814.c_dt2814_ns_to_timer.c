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

__attribute__((used)) static int dt2814_ns_to_timer(unsigned int *ns, unsigned int flags)
{
	int i;
	unsigned int f;

	/* XXX ignores flags */

	f = 10000;		/* ns */
	for (i = 0; i < 8; i++) {
		if ((2 * (*ns)) < (f * 11))
			break;
		f *= 10;
	}

	*ns = f;

	return i;
}