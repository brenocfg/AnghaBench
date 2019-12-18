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
 int MUX (int,int,int) ; 

uint32_t
br_i15_add(uint16_t *a, const uint16_t *b, uint32_t ctl)
{
	uint32_t cc;
	size_t u, m;

	cc = 0;
	m = (a[0] + 31) >> 4;
	for (u = 1; u < m; u ++) {
		uint32_t aw, bw, naw;

		aw = a[u];
		bw = b[u];
		naw = aw + bw + cc;
		cc = naw >> 15;
		a[u] = MUX(ctl, naw & 0x7FFF, aw);
	}
	return cc;
}