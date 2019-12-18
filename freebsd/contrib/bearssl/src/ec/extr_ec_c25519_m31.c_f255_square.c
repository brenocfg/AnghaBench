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
 int MUL31 (int,int) ; 
 int /*<<< orphan*/  square9 (int*,int const*) ; 

__attribute__((used)) static void
f255_square(uint32_t *d, const uint32_t *a)
{
	uint32_t t[18], cc;
	int i;

	/*
	 * Compute raw squaring. All result words fit in 30 bits
	 * each; upper word (t[17]) must fit on 2 bits, since the square
	 * of a 256-bit integers must fit on 512 bits.
	 */
	square9(t, a);

	/*
	 * Modular reduction: each high word is added where necessary.
	 * See f255_mul() for details on the reduction and carry limits.
	 */
	cc = MUL15(t[8] >> 15, 19);
	t[8] &= 0x7FFF;
	for (i = 0; i < 9; i ++) {
		uint64_t w;

		w = (uint64_t)t[i] + (uint64_t)cc + MUL31(t[i + 9], 622592);
		t[i] = (uint32_t)w & 0x3FFFFFFF;
		cc = (uint32_t)(w >> 30);
	}
	cc = MUL15(t[8] >> 15, 19);
	t[8] &= 0x7FFF;
	for (i = 0; i < 9; i ++) {
		uint32_t z;

		z = t[i] + cc;
		d[i] = z & 0x3FFFFFFF;
		cc = z >> 30;
	}
}