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
 int** fp_maskl ; 
 int** fp_maskr ; 
 int** ip_maskl ; 
 int** ip_maskr ; 
 int** psbox ; 

void __do_des(uint32_t l_in, uint32_t r_in,
    uint32_t *l_out, uint32_t *r_out,
    uint32_t count, uint32_t saltbits, const struct expanded_key *ekey)
{
	uint32_t l, r;

	/*
	 * Do initial permutation (IP).
	 */
	l = r = 0;
	if (l_in | r_in) {
		unsigned int i, ibit;
		for (i = 0, ibit = 28; i < 8; i++, ibit -= 4) {
			l |= ip_maskl[i][(l_in >> ibit) & 0xf] |
			     ip_maskl[i + 8][(r_in >> ibit) & 0xf];
			r |= ip_maskr[i][(l_in >> ibit) & 0xf] |
			     ip_maskr[i + 8][(r_in >> ibit) & 0xf];
		}
	}

	while (count--) {
		/*
		 * Do each round.
		 */
		unsigned int round = 16;
		const uint32_t *kl = ekey->l;
		const uint32_t *kr = ekey->r;
		uint32_t f;
		while (round--) {
			uint32_t r48l, r48r;
			/*
			 * Expand R to 48 bits (simulate the E-box).
			 */
			r48l	= ((r & 0x00000001) << 23)
				| ((r & 0xf8000000) >> 9)
				| ((r & 0x1f800000) >> 11)
				| ((r & 0x01f80000) >> 13)
				| ((r & 0x001f8000) >> 15);

			r48r	= ((r & 0x0001f800) << 7)
				| ((r & 0x00001f80) << 5)
				| ((r & 0x000001f8) << 3)
				| ((r & 0x0000001f) << 1)
				| ((r & 0x80000000) >> 31);
			/*
			 * Do salting for crypt() and friends, and
			 * XOR with the permuted key.
			 */
			f = (r48l ^ r48r) & saltbits;
			r48l ^= f ^ *kl++;
			r48r ^= f ^ *kr++;
			/*
			 * Do S-box lookups (which shrink it back to 32 bits)
			 * and do the P-box permutation at the same time.
			 */
			f = psbox[0][r48l >> 18]
			  | psbox[1][(r48l >> 12) & 0x3f]
			  | psbox[2][(r48l >> 6) & 0x3f]
			  | psbox[3][r48l & 0x3f]
			  | psbox[4][r48r >> 18]
			  | psbox[5][(r48r >> 12) & 0x3f]
			  | psbox[6][(r48r >> 6) & 0x3f]
			  | psbox[7][r48r & 0x3f];
			/*
			 * Now that we've permuted things, complete f().
			 */
			f ^= l;
			l = r;
			r = f;
		}
		r = l;
		l = f;
	}

	/*
	 * Do final permutation (inverse of IP).
	 */
	{
		unsigned int i, ibit;
		uint32_t lo, ro;
		lo = ro = 0;
		for (i = 0, ibit = 28; i < 4; i++, ibit -= 4) {
			ro |= fp_maskr[i][(l >> ibit) & 0xf] |
			      fp_maskr[i + 4][(r >> ibit) & 0xf];
			ibit -= 4;
			lo |= fp_maskl[i][(l >> ibit) & 0xf] |
			      fp_maskl[i + 4][(r >> ibit) & 0xf];
		}
		*l_out = lo;
		*r_out = ro;
	}
}