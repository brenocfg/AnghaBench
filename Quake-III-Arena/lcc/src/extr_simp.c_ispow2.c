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

int ispow2(unsigned long u) {
	int n;

	if (u > 1 && (u&(u-1)) == 0)
		for (n = 0; u; u >>= 1, n++)
			if (u&1)
				return n;
	return 0;
}