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
typedef  int /*<<< orphan*/  uint32_t ;
struct bitstream {int bits; int /*<<< orphan*/  doffset; } ;

/* Variables and functions */

uint32_t bitstream_read_offset(struct bitstream* bitstream)
{
	uint32_t result = bitstream->doffset;
	int bits = bitstream->bits;
	while (bits >= 8)
	{
		result--;
		bits -= 8;
	}
	return result;
}