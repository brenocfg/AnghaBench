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
eq_name(const char *s1, const char *s2)
{
	for (;;) {
		int c1, c2;

		for (;;) {
			c1 = *s1 ++;
			if (c1 >= 'A' && c1 <= 'Z') {
				c1 += 'a' - 'A';
			} else {
				switch (c1) {
				case '-': case '_': case '.': case ' ':
					continue;
				}
			}
			break;
		}
		for (;;) {
			c2 = *s2 ++;
			if (c2 >= 'A' && c2 <= 'Z') {
				c2 += 'a' - 'A';
			} else {
				switch (c2) {
				case '-': case '_': case '.': case ' ':
					continue;
				}
			}
			break;
		}
		if (c1 != c2) {
			return 0;
		}
		if (c1 == 0) {
			return 1;
		}
	}
}