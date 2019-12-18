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

__attribute__((used)) static void
revbytes(unsigned char *buf, size_t len)
{
	size_t u;

	for (u = 0; u < (len >> 1); u ++) {
		unsigned t;

		t = buf[u];
		buf[u] = buf[len - 1 - u];
		buf[len - 1 - u] = t;
	}
}