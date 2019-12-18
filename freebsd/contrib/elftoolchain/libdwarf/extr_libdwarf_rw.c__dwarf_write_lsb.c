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

void
_dwarf_write_lsb(uint8_t *data, uint64_t *offsetp, uint64_t value,
    int bytes_to_write)
{
	uint8_t *dst;

	dst = data + *offsetp;

	switch (bytes_to_write) {
	case 8:
		dst[7] = (value >> 56) & 0xff;
		dst[6] = (value >> 48) & 0xff;
		dst[5] = (value >> 40) & 0xff;
		dst[4] = (value >> 32) & 0xff;
		/* FALLTHROUGH */
	case 4:
		dst[3] = (value >> 24) & 0xff;
		dst[2] = (value >> 16) & 0xff;
		/* FALLTHROUGH */
	case 2:
		dst[1] = (value >> 8) & 0xff;
		/* FALLTHROUGH */
	case 1:
		dst[0] = value & 0xff;
		break;
	default:
		return;
	}

	*offsetp += bytes_to_write;
}