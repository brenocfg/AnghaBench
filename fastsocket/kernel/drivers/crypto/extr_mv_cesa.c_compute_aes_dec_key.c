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
struct mv_ctx {int key_len; scalar_t__ need_calc_aes_dkey; int /*<<< orphan*/ * aes_dec_key; int /*<<< orphan*/  aes_enc_key; } ;
struct crypto_aes_ctx {int /*<<< orphan*/ * key_enc; } ;

/* Variables and functions */
#define  AES_KEYSIZE_192 129 
#define  AES_KEYSIZE_256 128 
 int /*<<< orphan*/  crypto_aes_expand_key (struct crypto_aes_ctx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void compute_aes_dec_key(struct mv_ctx *ctx)
{
	struct crypto_aes_ctx gen_aes_key;
	int key_pos;

	if (!ctx->need_calc_aes_dkey)
		return;

	crypto_aes_expand_key(&gen_aes_key, ctx->aes_enc_key, ctx->key_len);

	key_pos = ctx->key_len + 24;
	memcpy(ctx->aes_dec_key, &gen_aes_key.key_enc[key_pos], 4 * 4);
	switch (ctx->key_len) {
	case AES_KEYSIZE_256:
		key_pos -= 2;
		/* fall */
	case AES_KEYSIZE_192:
		key_pos -= 2;
		memcpy(&ctx->aes_dec_key[4], &gen_aes_key.key_enc[key_pos],
				4 * 4);
		break;
	}
	ctx->need_calc_aes_dkey = 0;
}