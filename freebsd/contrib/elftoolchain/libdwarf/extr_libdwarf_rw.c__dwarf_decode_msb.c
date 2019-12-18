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
_dwarf_decode_msb(uint8_t **data, int bytes_to_read)
{
	uint64_t ret;
	uint8_t *src;

	src = *data;

	ret = 0;
	switch (bytes_to_read) {
	case 1:
		ret = src[0];
		break;
	case 2:
		ret = src[1] | ((uint64_t) src[0]) << 8;
		break;
	case 4:
		ret = src[3] | ((uint64_t) src[2]) << 8;
		ret |= ((uint64_t) src[1]) << 16 | ((uint64_t) src[0]) << 24;
		break;
	case 8:
		ret = src[7] | ((uint64_t) src[6]) << 8;
		ret |= ((uint64_t) src[5]) << 16 | ((uint64_t) src[4]) << 24;
		ret |= ((uint64_t) src[3]) << 32 | ((uint64_t) src[2]) << 40;
		ret |= ((uint64_t) src[1]) << 48 | ((uint64_t) src[0]) << 56;
		break;
	default:
		return (0);
		break;
	}

	*data += bytes_to_read;

	return (ret);
}