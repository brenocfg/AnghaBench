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

int memcmp(const void *cs, const void *ct, size_t count)
{
	const unsigned char *su1, *su2;

	for (su1 = cs, su2 = ct; count > 0; ++su1, ++su2, count--)
		if (*su1 != *su2)
			return *su1 < *su2 ? -1 : +1;
	return 0;
}