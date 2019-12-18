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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct crypto_tfm {int dummy; } ;
struct bf_ctx {int* p; int* s; } ;

/* Variables and functions */
 int* bf_pbox ; 
 int* bf_sbox ; 
 struct bf_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  encrypt_block (struct bf_ctx*,int*,int*) ; 

__attribute__((used)) static int bf_setkey(struct crypto_tfm *tfm, const u8 *key, unsigned int keylen)
{
	struct bf_ctx *ctx = crypto_tfm_ctx(tfm);
	u32 *P = ctx->p;
	u32 *S = ctx->s;
	short i, j, count;
	u32 data[2], temp;

	/* Copy the initialization s-boxes */
	for (i = 0, count = 0; i < 256; i++)
		for (j = 0; j < 4; j++, count++)
			S[count] = bf_sbox[count];

	/* Set the p-boxes */
	for (i = 0; i < 16 + 2; i++)
		P[i] = bf_pbox[i];

	/* Actual subkey generation */
	for (j = 0, i = 0; i < 16 + 2; i++) {
		temp = (((u32 )key[j] << 24) |
			((u32 )key[(j + 1) % keylen] << 16) |
			((u32 )key[(j + 2) % keylen] << 8) |
			((u32 )key[(j + 3) % keylen]));

		P[i] = P[i] ^ temp;
		j = (j + 4) % keylen;
	}

	data[0] = 0x00000000;
	data[1] = 0x00000000;

	for (i = 0; i < 16 + 2; i += 2) {
		encrypt_block((struct bf_ctx *)ctx, data, data);

		P[i] = data[0];
		P[i + 1] = data[1];
	}

	for (i = 0; i < 4; i++) {
		for (j = 0, count = i * 256; j < 256; j += 2, count += 2) {
			encrypt_block((struct bf_ctx *)ctx, data, data);

			S[count] = data[0];
			S[count + 1] = data[1];
		}
	}
	
	/* Bruce says not to bother with the weak key check. */
	return 0;
}