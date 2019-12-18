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
 int* Rcon ; 
 int /*<<< orphan*/  br_aes_ct_ortho (int*) ; 
 int br_dec32le (unsigned char const*) ; 
 int sub_word (int) ; 

unsigned
br_aes_ct_keysched(uint32_t *comp_skey, const void *key, size_t key_len)
{
	unsigned num_rounds;
	int i, j, k, nk, nkf;
	uint32_t tmp;
	uint32_t skey[120];

	switch (key_len) {
	case 16:
		num_rounds = 10;
		break;
	case 24:
		num_rounds = 12;
		break;
	case 32:
		num_rounds = 14;
		break;
	default:
		/* abort(); */
		return 0;
	}
	nk = (int)(key_len >> 2);
	nkf = (int)((num_rounds + 1) << 2);
	tmp = 0;
	for (i = 0; i < nk; i ++) {
		tmp = br_dec32le((const unsigned char *)key + (i << 2));
		skey[(i << 1) + 0] = tmp;
		skey[(i << 1) + 1] = tmp;
	}
	for (i = nk, j = 0, k = 0; i < nkf; i ++) {
		if (j == 0) {
			tmp = (tmp << 24) | (tmp >> 8);
			tmp = sub_word(tmp) ^ Rcon[k];
		} else if (nk > 6 && j == 4) {
			tmp = sub_word(tmp);
		}
		tmp ^= skey[(i - nk) << 1];
		skey[(i << 1) + 0] = tmp;
		skey[(i << 1) + 1] = tmp;
		if (++ j == nk) {
			j = 0;
			k ++;
		}
	}
	for (i = 0; i < nkf; i += 4) {
		br_aes_ct_ortho(skey + (i << 1));
	}
	for (i = 0, j = 0; i < nkf; i ++, j += 2) {
		comp_skey[i] = (skey[j + 0] & 0x55555555)
			| (skey[j + 1] & 0xAAAAAAAA);
	}
	return num_rounds;
}