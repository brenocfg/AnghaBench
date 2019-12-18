#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned int bit; int* cur; } ;
typedef  TYPE_1__ bitstr_t ;

/* Variables and functions */

__attribute__((used)) static unsigned int get_bitmap(bitstr_t *bs, unsigned int b)
{
	unsigned int v, l, shift, bytes;

	if (!b)
		return 0;

	l = bs->bit + b;

	if (l < 8) {
		v = (unsigned int)(*bs->cur) << (bs->bit + 24);
		bs->bit = l;
	} else if (l == 8) {
		v = (unsigned int)(*bs->cur++) << (bs->bit + 24);
		bs->bit = 0;
	} else {
		for (bytes = l >> 3, shift = 24, v = 0; bytes;
		     bytes--, shift -= 8)
			v |= (unsigned int)(*bs->cur++) << shift;

		if (l < 32) {
			v |= (unsigned int)(*bs->cur) << shift;
			v <<= bs->bit;
		} else if (l > 32) {
			v <<= bs->bit;
			v |= (*bs->cur) >> (8 - bs->bit);
		}

		bs->bit = l & 0x7;
	}

	v &= 0xffffffff << (32 - b);

	return v;
}