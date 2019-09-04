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

__attribute__((used)) static int getoffs(short *offs, const unsigned char *base, const unsigned char *s)
{
	int i=0;
	for (;;) {
		while (*s & 0xc0) {
			if ((*s & 0xc0) != 0xc0) return 0;
			s = base + ((s[0]&0x3f)<<8 | s[1]);
		}
		if (!*s) return i;
		if (s-base >= 0x4000) return 0;
		offs[i++] = s-base;
		s += *s + 1;
	}
}