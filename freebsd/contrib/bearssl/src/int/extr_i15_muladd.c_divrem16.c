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
typedef  int uint32_t ;

/* Variables and functions */
 int LE (int,int) ; 

__attribute__((used)) static uint32_t
divrem16(uint32_t x, uint32_t d, uint32_t *r)
{
	int i;
	uint32_t q;

	q = 0;
	d <<= 16;
	for (i = 16; i >= 0; i --) {
		uint32_t ctl;

		ctl = LE(d, x);
		q |= ctl << i;
		x -= (-ctl) & d;
		d >>= 1;
	}
	if (r != NULL) {
		*r = x;
	}
	return q;
}