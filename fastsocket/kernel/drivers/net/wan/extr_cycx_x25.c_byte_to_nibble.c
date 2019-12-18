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
typedef  char u8 ;

/* Variables and functions */

__attribute__((used)) static int byte_to_nibble(u8 *s, u8 *d, char *nibble)
{
	int i = 0;

	if (*nibble && *s) {
		d[i] |= *s++ - '0';
		*nibble = 0;
		++i;
	}

	while (*s) {
		d[i] = (*s - '0') << 4;
		if (*(s + 1))
			d[i] |= *(s + 1) - '0';
		else {
			*nibble = 1;
			break;
		}
		++i;
		s += 2;
	}

	return i;
}