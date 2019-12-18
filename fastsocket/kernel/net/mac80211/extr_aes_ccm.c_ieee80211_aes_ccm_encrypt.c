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
struct crypto_cipher {int dummy; } ;

/* Variables and functions */
 int AES_BLOCK_SIZE ; 
 int CCMP_MIC_LEN ; 
 int DIV_ROUND_UP (size_t,int) ; 
 int /*<<< orphan*/  aes_ccm_prepare (struct crypto_cipher*,int*,int*) ; 
 int /*<<< orphan*/  crypto_cipher_encrypt_one (struct crypto_cipher*,int*,int*) ; 

void ieee80211_aes_ccm_encrypt(struct crypto_cipher *tfm, u8 *scratch,
			       u8 *data, size_t data_len,
			       u8 *cdata, u8 *mic)
{
	int i, j, last_len, num_blocks;
	u8 *pos, *cpos, *b, *s_0, *e, *b_0;

	b = scratch;
	s_0 = scratch + AES_BLOCK_SIZE;
	e = scratch + 2 * AES_BLOCK_SIZE;
	b_0 = scratch + 3 * AES_BLOCK_SIZE;

	num_blocks = DIV_ROUND_UP(data_len, AES_BLOCK_SIZE);
	last_len = data_len % AES_BLOCK_SIZE;
	aes_ccm_prepare(tfm, scratch, b);

	/* Process payload blocks */
	pos = data;
	cpos = cdata;
	for (j = 1; j <= num_blocks; j++) {
		int blen = (j == num_blocks && last_len) ?
			last_len : AES_BLOCK_SIZE;

		/* Authentication followed by encryption */
		for (i = 0; i < blen; i++)
			b[i] ^= pos[i];
		crypto_cipher_encrypt_one(tfm, b, b);

		b_0[14] = (j >> 8) & 0xff;
		b_0[15] = j & 0xff;
		crypto_cipher_encrypt_one(tfm, e, b_0);
		for (i = 0; i < blen; i++)
			*cpos++ = *pos++ ^ e[i];
	}

	for (i = 0; i < CCMP_MIC_LEN; i++)
		mic[i] = b[i] ^ s_0[i];
}