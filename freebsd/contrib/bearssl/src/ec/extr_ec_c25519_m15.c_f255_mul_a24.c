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
 int MUL15 (int const,int) ; 

__attribute__((used)) static void
f255_mul_a24(uint32_t *d, const uint32_t *a)
{
	int i;
	uint32_t cc, w;

	cc = 0;
	for (i = 0; i < 20; i ++) {
		w = MUL15(a[i], 121665) + cc;
		d[i] = w & 0x1FFF;
		cc = w >> 13;
	}
	cc = MUL15(w >> 8, 19);
	d[19] &= 0xFF;
	for (i = 0; i < 20; i ++) {
		w = d[i] + cc;
		d[i] = w & 0x1FFF;
		cc = w >> 13;
	}
}