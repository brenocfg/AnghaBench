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
typedef  int uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int MUL15 (int,int) ; 
 int MUL31 (int const,int) ; 

__attribute__((used)) static void
f255_mul_a24(uint32_t *d, const uint32_t *a)
{
	int i;
	uint64_t w;
	uint32_t cc;

	/*
	 * a[] is over 256 bits, thus a[8] has length at most 16 bits.
	 * We single out the processing of the last word: intermediate
	 * value w is up to 121665*2^16, yielding a carry for the next
	 * loop of at most 19*(121665*2^16/2^15) = 4623289.
	 */
	cc = 0;
	for (i = 0; i < 8; i ++) {
		w = MUL31(a[i], 121665) + (uint64_t)cc;
		d[i] = (uint32_t)w & 0x3FFFFFFF;
		cc = (uint32_t)(w >> 30);
	}
	w = MUL31(a[8], 121665) + (uint64_t)cc;
	d[8] = (uint32_t)w & 0x7FFF;
	cc = MUL15((uint32_t)(w >> 15), 19);

	for (i = 0; i < 9; i ++) {
		uint32_t z;

		z = d[i] + cc;
		d[i] = z & 0x3FFFFFFF;
		cc = z >> 30;
	}
}