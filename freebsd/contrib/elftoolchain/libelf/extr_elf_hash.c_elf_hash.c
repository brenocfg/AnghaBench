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

unsigned long
elf_hash(const char *name)
{
	unsigned long h, t;
	const unsigned char *s;

	s = (const unsigned char *) name;
	h = t = 0;

	for (; *s != '\0'; h = h & ~t) {
		h = (h << 4) + *s++;
		t = h & 0xF0000000UL;
		if (t)
			h ^= t >> 24;
	}

	return (h);
}