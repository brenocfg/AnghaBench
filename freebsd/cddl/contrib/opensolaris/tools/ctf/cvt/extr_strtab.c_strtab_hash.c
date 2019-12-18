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

__attribute__((used)) static ulong_t
strtab_hash(const char *key, size_t *len)
{
	ulong_t g, h = 0;
	const char *p;
	size_t n = 0;

	for (p = key; *p != '\0'; p++, n++) {
		h = (h << 4) + *p;

		if ((g = (h & 0xf0000000)) != 0) {
			h ^= (g >> 24);
			h ^= g;
		}
	}

	*len = n;
	return (h);
}