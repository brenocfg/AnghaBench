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
 int br_dec32be (unsigned char const*) ; 
 int /*<<< orphan*/  br_des_do_IP (int*,int*) ; 

void
br_des_keysched_unit(uint32_t *skey, const void *key)
{
	uint32_t xl, xr, kl, kr;
	int i;

	xl = br_dec32be(key);
	xr = br_dec32be((const unsigned char *)key + 4);

	/*
	 * Permutation PC-1 is quite similar to the IP permutation.
	 * Definition of IP (in FIPS 46-3 notations) is:
	 *   58 50 42 34 26 18 10 2
	 *   60 52 44 36 28 20 12 4
	 *   62 54 46 38 30 22 14 6
	 *   64 56 48 40 32 24 16 8
	 *   57 49 41 33 25 17  9 1
	 *   59 51 43 35 27 19 11 3
	 *   61 53 45 37 29 21 13 5
	 *   63 55 47 39 31 23 15 7
	 *
	 * Definition of PC-1 is:
	 *   57 49 41 33 25 17  9 1
	 *   58 50 42 34 26 18 10 2
	 *   59 51 43 35 27 19 11 3
	 *   60 52 44 36
	 *   63 55 47 39 31 23 15 7
	 *   62 54 46 38 30 22 14 6
	 *   61 53 45 37 29 21 13 5
	 *   28 20 12  4
	 */
	br_des_do_IP(&xl, &xr);
	kl = ((xr & (uint32_t)0xFF000000) >> 4)
		| ((xl & (uint32_t)0xFF000000) >> 12)
		| ((xr & (uint32_t)0x00FF0000) >> 12)
		| ((xl & (uint32_t)0x00FF0000) >> 20);
	kr = ((xr & (uint32_t)0x000000FF) << 20)
		| ((xl & (uint32_t)0x0000FF00) << 4)
		| ((xr & (uint32_t)0x0000FF00) >> 4)
		| ((xl & (uint32_t)0x000F0000) >> 16);

	/*
	 * For each round, rotate the two 28-bit words kl and kr.
	 * The extraction of the 48-bit subkey (PC-2) is not done yet.
	 */
	for (i = 0; i < 16; i ++) {
		if ((1 << i) & 0x8103) {
			kl = (kl << 1) | (kl >> 27);
			kr = (kr << 1) | (kr >> 27);
		} else {
			kl = (kl << 2) | (kl >> 26);
			kr = (kr << 2) | (kr >> 26);
		}
		kl &= (uint32_t)0x0FFFFFFF;
		kr &= (uint32_t)0x0FFFFFFF;
		skey[(i << 1) + 0] = kl;
		skey[(i << 1) + 1] = kr;
	}
}