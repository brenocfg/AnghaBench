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
 int MUL15 (int,int) ; 

__attribute__((used)) static void
f255_add(uint32_t *d, const uint32_t *a, const uint32_t *b)
{
	/*
	 * Since operand words fit on 30 bits, we can use 32-bit
	 * variables throughout.
	 */
	int i;
	uint32_t cc, w;

	cc = 0;
	for (i = 0; i < 9; i ++) {
		w = a[i] + b[i] + cc;
		d[i] = w & 0x3FFFFFFF;
		cc = w >> 30;
	}
	cc = MUL15(w >> 15, 19);
	d[8] &= 0x7FFF;
	for (i = 0; i < 9; i ++) {
		w = d[i] + cc;
		d[i] = w & 0x3FFFFFFF;
		cc = w >> 30;
	}
}