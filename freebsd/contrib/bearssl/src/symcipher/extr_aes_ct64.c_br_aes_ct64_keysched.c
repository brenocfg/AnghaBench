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
 int* Rcon ; 
 int /*<<< orphan*/  br_aes_ct64_interleave_in (int*,int*,int*) ; 
 int /*<<< orphan*/  br_aes_ct64_ortho (int*) ; 
 int /*<<< orphan*/  br_range_dec32le (int*,size_t,void const*) ; 
 int sub_word (int) ; 

unsigned
br_aes_ct64_keysched(uint64_t *comp_skey, const void *key, size_t key_len)
{
	unsigned num_rounds;
	int i, j, k, nk, nkf;
	uint32_t tmp;
	uint32_t skey[60];

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
	br_range_dec32le(skey, (key_len >> 2), key);
	tmp = skey[(key_len >> 2) - 1];
	for (i = nk, j = 0, k = 0; i < nkf; i ++) {
		if (j == 0) {
			tmp = (tmp << 24) | (tmp >> 8);
			tmp = sub_word(tmp) ^ Rcon[k];
		} else if (nk > 6 && j == 4) {
			tmp = sub_word(tmp);
		}
		tmp ^= skey[i - nk];
		skey[i] = tmp;
		if (++ j == nk) {
			j = 0;
			k ++;
		}
	}

	for (i = 0, j = 0; i < nkf; i += 4, j += 2) {
		uint64_t q[8];

		br_aes_ct64_interleave_in(&q[0], &q[4], skey + i);
		q[1] = q[0];
		q[2] = q[0];
		q[3] = q[0];
		q[5] = q[4];
		q[6] = q[4];
		q[7] = q[4];
		br_aes_ct64_ortho(q);
		comp_skey[j + 0] =
			  (q[0] & (uint64_t)0x1111111111111111)
			| (q[1] & (uint64_t)0x2222222222222222)
			| (q[2] & (uint64_t)0x4444444444444444)
			| (q[3] & (uint64_t)0x8888888888888888);
		comp_skey[j + 1] =
			  (q[4] & (uint64_t)0x1111111111111111)
			| (q[5] & (uint64_t)0x2222222222222222)
			| (q[6] & (uint64_t)0x4444444444444444)
			| (q[7] & (uint64_t)0x8888888888888888);
	}
	return num_rounds;
}