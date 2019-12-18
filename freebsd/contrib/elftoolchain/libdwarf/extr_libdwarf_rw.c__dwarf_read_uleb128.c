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
typedef  int uint64_t ;

/* Variables and functions */

uint64_t
_dwarf_read_uleb128(uint8_t *data, uint64_t *offsetp)
{
	uint64_t ret = 0;
	uint8_t b;
	int shift = 0;
	uint8_t *src;

	src = data + *offsetp;

	do {
		b = *src++;
		ret |= ((b & 0x7f) << shift);
		(*offsetp)++;
		shift += 7;
	} while ((b & 0x80) != 0);

	return (ret);
}