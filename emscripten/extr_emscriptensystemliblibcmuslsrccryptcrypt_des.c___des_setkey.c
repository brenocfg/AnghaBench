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
struct expanded_key {int* l; int* r; } ;

/* Variables and functions */
 int** comp_maskl0 ; 
 int** comp_maskl1 ; 
 int** comp_maskr0 ; 
 int** comp_maskr1 ; 
 int** key_perm_maskl ; 
 int** key_perm_maskr ; 
 scalar_t__* key_shifts ; 

void __des_setkey(const unsigned char *key, struct expanded_key *ekey)
{
	uint32_t k0, k1, rawkey0, rawkey1;
	unsigned int shifts, round, i, ibit;

	rawkey0 =
	    (uint32_t)key[3] |
	    ((uint32_t)key[2] << 8) |
	    ((uint32_t)key[1] << 16) |
	    ((uint32_t)key[0] << 24);
	rawkey1 =
	    (uint32_t)key[7] |
	    ((uint32_t)key[6] << 8) |
	    ((uint32_t)key[5] << 16) |
	    ((uint32_t)key[4] << 24);

	/*
	 * Do key permutation and split into two 28-bit subkeys.
	 */
	k0 = k1 = 0;
	for (i = 0, ibit = 28; i < 4; i++, ibit -= 4) {
		unsigned int j = i << 1;
		k0 |= key_perm_maskl[i][(rawkey0 >> ibit) & 0xf] |
		      key_perm_maskl[i + 4][(rawkey1 >> ibit) & 0xf];
		k1 |= key_perm_maskr[j][(rawkey0 >> ibit) & 0xf];
		ibit -= 4;
		k1 |= key_perm_maskr[j + 1][(rawkey0 >> ibit) & 0xf] |
		      key_perm_maskr[i + 8][(rawkey1 >> ibit) & 0xf];
	}

	/*
	 * Rotate subkeys and do compression permutation.
	 */
	shifts = 0;
	for (round = 0; round < 16; round++) {
		uint32_t t0, t1;
		uint32_t kl, kr;

		shifts += key_shifts[round];

		t0 = (k0 << shifts) | (k0 >> (28 - shifts));
		t1 = (k1 << shifts) | (k1 >> (28 - shifts));

		kl = kr = 0;
		ibit = 25;
		for (i = 0; i < 4; i++) {
			kl |= comp_maskl0[i][(t0 >> ibit) & 7];
			kr |= comp_maskr0[i][(t1 >> ibit) & 7];
			ibit -= 4;
			kl |= comp_maskl1[i][(t0 >> ibit) & 0xf];
			kr |= comp_maskr1[i][(t1 >> ibit) & 0xf];
			ibit -= 3;
		}
		ekey->l[round] = kl;
		ekey->r[round] = kr;
	}
}