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
typedef  unsigned char uint32_t ;
typedef  int uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  CCOPY (unsigned char,int*,int*,size_t) ; 
 int /*<<< orphan*/  br_i15_montymul (int*,int*,int*,int const*,int) ; 
 int /*<<< orphan*/  br_i15_to_monty (int*,int const*) ; 
 int /*<<< orphan*/  br_i15_zero (int*,int const) ; 
 int /*<<< orphan*/  memcpy (int*,int*,size_t) ; 

void
br_i15_modpow(uint16_t *x,
	const unsigned char *e, size_t elen,
	const uint16_t *m, uint16_t m0i, uint16_t *t1, uint16_t *t2)
{
	size_t mlen;
	unsigned k;

	mlen = ((m[0] + 31) >> 4) * sizeof m[0];
	memcpy(t1, x, mlen);
	br_i15_to_monty(t1, m);
	br_i15_zero(x, m[0]);
	x[1] = 1;
	for (k = 0; k < ((unsigned)elen << 3); k ++) {
		uint32_t ctl;

		ctl = (e[elen - 1 - (k >> 3)] >> (k & 7)) & 1;
		br_i15_montymul(t2, x, t1, m, m0i);
		CCOPY(ctl, x, t2, mlen);
		br_i15_montymul(t2, t1, t1, m, m0i);
		memcpy(t1, t2, mlen);
	}
}