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
eqnocase(const void *s1, const void *s2, size_t len)
{
	const unsigned char *buf1, *buf2;

	buf1 = s1;
	buf2 = s2;
	while (len -- > 0) {
		int x1, x2;

		x1 = *buf1 ++;
		x2 = *buf2 ++;
		if (x1 >= 'A' && x1 <= 'Z') {
			x1 += 'a' - 'A';
		}
		if (x2 >= 'A' && x2 <= 'Z') {
			x2 += 'a' - 'A';
		}
		if (x1 != x2) {
			return 0;
		}
	}
	return 1;
}