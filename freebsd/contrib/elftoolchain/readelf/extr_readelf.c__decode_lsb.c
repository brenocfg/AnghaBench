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

__attribute__((used)) static uint64_t
_decode_lsb(uint8_t **data, int bytes_to_read)
{
	uint64_t ret;
	uint8_t *src;

	src = *data;

	ret = 0;
	switch (bytes_to_read) {
	case 8:
		ret |= ((uint64_t) src[4]) << 32 | ((uint64_t) src[5]) << 40;
		ret |= ((uint64_t) src[6]) << 48 | ((uint64_t) src[7]) << 56;
		/* FALLTHROUGH */
	case 4:
		ret |= ((uint64_t) src[2]) << 16 | ((uint64_t) src[3]) << 24;
		/* FALLTHROUGH */
	case 2:
		ret |= ((uint64_t) src[1]) << 8;
		/* FALLTHROUGH */
	case 1:
		ret |= src[0];
		break;
	default:
		return (0);
	}

	*data += bytes_to_read;

	return (ret);
}