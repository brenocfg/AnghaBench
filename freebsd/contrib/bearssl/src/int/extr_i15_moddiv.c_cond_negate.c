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
cond_negate(uint16_t *a, size_t len, uint32_t ctl)
{
	size_t k;
	uint32_t cc, xm;

	cc = ctl;
	xm = 0x7FFF & -ctl;
	for (k = 0; k < len; k ++) {
		uint32_t aw;

		aw = a[k];
		aw = (aw ^ xm) + cc;
		a[k] = aw & 0x7FFF;
		cc = (aw >> 15) & 1;
	}
}