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
typedef  int u8 ;
typedef  int u32 ;

/* Variables and functions */
 int aes_ks_subword (int) ; 
 int be32_to_cpu (int) ; 
 int cpu_to_be32 (int) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int* round_constant ; 

__attribute__((used)) static void get_aes_decrypt_key(unsigned char *dec_key, const unsigned  char *key, unsigned int keylength)
{
	u32 temp;
	u32 w_ring[8]; /* nk is max 8, use elements 0..(nk - 1) as a ringbuffer */
	u8  w_last_ix;
	int i;
	u8  nr, nk;

	switch (keylength){
	case 128:
		nk = 4;
		nr = 10;
		break;
	case 192:
		nk = 6;
		nr = 12;
		break;
	case 256:
		nk = 8;
		nr = 14;
		break;
	default:
		panic("stream co-processor: bad aes key length in get_aes_decrypt_key\n");
	};

	/* Need to do host byte order correction here since key is byte oriented and the
	 * kx algorithm is word (u32) oriented. */
	for (i = 0; i < nk; i+=1) {
		w_ring[i] = be32_to_cpu(*(u32*)&key[4*i]);
	}

	i = (int)nk;
	w_last_ix = i - 1;
	while (i < (4 * (nr + 2))) {
		temp = w_ring[w_last_ix];
		if (!(i % nk)) {
			/* RotWord(temp) */
			temp = (temp << 8) | (temp >> 24);
			temp = aes_ks_subword(temp);
			temp ^= round_constant[i/nk - 1];
		} else if ((nk > 6) && ((i % nk) == 4)) {
			temp = aes_ks_subword(temp);
		}
		w_last_ix = (w_last_ix + 1) % nk; /* This is the same as (i-Nk) mod Nk */
		temp ^= w_ring[w_last_ix];
		w_ring[w_last_ix] = temp;

		/* We need the round keys for round Nr+1 and Nr+2 (round key
		 * Nr+2 is the round key beyond the last one used when
		 * encrypting).  Rounds are numbered starting from 0, Nr=10
		 * implies 11 rounds are used in encryption/decryption.
		 */
		if (i >= (4 * nr)) {
			/* Need to do host byte order correction here, the key
			 * is byte oriented. */
			*(u32*)dec_key = cpu_to_be32(temp);
			dec_key += 4;
		}
		++i;
	}
}