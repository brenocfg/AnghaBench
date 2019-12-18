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

__attribute__((used)) static unsigned char*
bin2mem(unsigned char *mem, unsigned char *buf, int count)
{
	int i;
	unsigned char *next;
	for (i = 0; i < count; i++) {
		/* Check for any escaped characters. Be paranoid and
		   only unescape chars that should be escaped. */
		if (*buf == 0x7d) {
			next = buf + 1;
			if (*next == 0x3 || *next == 0x4 || *next == 0x5D) {
				 /* #, $, ESC */
				buf++;
				*buf += 0x20;
			}
		}
		*mem++ = *buf++;
	}
	return mem;
}