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

__attribute__((used)) static int fuzzycmp(const unsigned char *a, const unsigned char *b)
{
	for (; *a && *b; a++, b++) {
		while (*a && (*a|32U)-'a'>26 && *a-'0'>10U) a++;
		if ((*a|32U) != *b) return 1;
	}
	return *a != *b;
}