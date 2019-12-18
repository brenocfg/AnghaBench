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
typedef  int u_char ;

/* Variables and functions */

__attribute__((used)) static int
prbits(char *dest, u_char b, int start, int len)
{
	char *dp = dest;

	b = b << (8 - start);
	while (len--) {
		if (b & 0x80)
			*dp++ = '1';
		else
			*dp++ = '0';
		b = b << 1;
	}
	return (dp - dest);
}