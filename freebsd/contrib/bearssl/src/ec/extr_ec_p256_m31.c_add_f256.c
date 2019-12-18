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
 int ARSH (int,int) ; 

__attribute__((used)) static void
add_f256(uint32_t *d, const uint32_t *a, const uint32_t *b)
{
	uint32_t w, cc;
	int i;

	cc = 0;
	for (i = 0; i < 9; i ++) {
		w = a[i] + b[i] + cc;
		d[i] = w & 0x3FFFFFFF;
		cc = w >> 30;
	}
	w >>= 16;
	d[8] &= 0xFFFF;
	d[3] -= w << 6;
	d[6] -= w << 12;
	d[7] += w << 14;
	cc = w;
	for (i = 0; i < 9; i ++) {
		w = d[i] + cc;
		d[i] = w & 0x3FFFFFFF;
		cc = ARSH(w, 30);
	}
}