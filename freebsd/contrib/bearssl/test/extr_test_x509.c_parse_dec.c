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

__attribute__((used)) static int
parse_dec(const char *s, unsigned len, int *val)
{
	int acc;

	acc = 0;
	while (len -- > 0) {
		int c;

		c = *s ++;
		if (c >= '0' && c <= '9') {
			acc = (acc * 10) + (c - '0');
		} else {
			return -1;
		}
	}
	*val = acc;
	return 0;
}