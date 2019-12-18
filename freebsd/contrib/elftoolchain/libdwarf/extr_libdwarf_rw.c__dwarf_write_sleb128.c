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
typedef  int uint8_t ;
typedef  int int64_t ;

/* Variables and functions */

int
_dwarf_write_sleb128(uint8_t *data, uint8_t *end, int64_t val)
{
	uint8_t *p;

	p = data;

	for (;;) {
		if (p >= end)
			return (-1);
		*p = val & 0x7f;
		val >>= 7;
		if ((val == 0 && (*p & 0x40) == 0) ||
		    (val == -1 && (*p & 0x40) != 0)) {
			p++;
			break;
		}
		*p++ |= 0x80;
	}

	return (p - data);
}