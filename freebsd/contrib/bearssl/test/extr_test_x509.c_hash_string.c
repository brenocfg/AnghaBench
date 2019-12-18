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
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static uint32_t
hash_string(const char *name)
{
	uint32_t hc;

	hc = 0;
	while (*name) {
		int x;

		hc = (hc << 5) - hc;
		x = *(const unsigned char *)name;
		if (x >= 'A' && x <= 'Z') {
			x += 'a' - 'A';
		}
		hc += (uint32_t)x;
		name ++;
	}
	return hc;
}