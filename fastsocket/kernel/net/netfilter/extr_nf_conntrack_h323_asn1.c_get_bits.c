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
struct TYPE_3__ {int* cur; int bit; } ;
typedef  TYPE_1__ bitstr_t ;

/* Variables and functions */

__attribute__((used)) static unsigned int get_bits(bitstr_t *bs, unsigned int b)
{
	unsigned int v, l;

	v = (*bs->cur) & (0xffU >> bs->bit);
	l = b + bs->bit;

	if (l < 8) {
		v >>= 8 - l;
		bs->bit = l;
	} else if (l == 8) {
		bs->cur++;
		bs->bit = 0;
	} else {		/* l > 8 */

		v <<= 8;
		v += *(++bs->cur);
		v >>= 16 - l;
		bs->bit = l - 8;
	}

	return v;
}