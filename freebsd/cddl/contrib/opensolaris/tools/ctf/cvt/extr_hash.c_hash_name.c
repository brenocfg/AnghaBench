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
typedef  int ulong_t ;

/* Variables and functions */

int
hash_name(int nbuckets, const char *name)
{
	const char *c;
	ulong_t g;
	int h = 0;

	for (c = name; *c; c++) {
		h = (h << 4) + *c;
		if ((g = (h & 0xf0000000)) != 0) {
			h ^= (g >> 24);
			h ^= g;
		}
	}

	return (h % nbuckets);
}