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
typedef  int uint16_t ;

/* Variables and functions */

__attribute__((used)) static void
cswap(uint16_t *a, uint16_t *b, uint32_t ctl)
{
	int i;

	ctl = -ctl;
	for (i = 0; i < 18; i ++) {
		uint32_t aw, bw, tw;

		aw = a[i];
		bw = b[i];
		tw = ctl & (aw ^ bw);
		a[i] = aw ^ tw;
		b[i] = bw ^ tw;
	}
}