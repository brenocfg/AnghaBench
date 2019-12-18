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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint64_t ;

/* Variables and functions */

uint8_t *
_dwarf_read_block(void *data, uint64_t *offsetp, uint64_t length)
{
	uint8_t *ret, *src;

	ret = src = (uint8_t *) data + *offsetp;

	(*offsetp) += length;

	return (ret);
}