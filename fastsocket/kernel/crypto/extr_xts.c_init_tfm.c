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
typedef  int /*<<< orphan*/  u32 ;
struct priv {struct crypto_cipher* tweak; struct crypto_cipher* child; } ;
struct crypto_tfm {int /*<<< orphan*/  crt_flags; scalar_t__ __crt_alg; } ;
struct crypto_spawn {int dummy; } ;
struct crypto_instance {int dummy; } ;
struct crypto_cipher {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_TFM_RES_BAD_BLOCK_LEN ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct crypto_cipher*) ; 
 int PTR_ERR (struct crypto_cipher*) ; 
 scalar_t__ XTS_BLOCK_SIZE ; 
 scalar_t__ crypto_cipher_blocksize (struct crypto_cipher*) ; 
 int /*<<< orphan*/  crypto_free_cipher (struct crypto_cipher*) ; 
 struct crypto_spawn* crypto_instance_ctx (struct crypto_instance*) ; 
 struct crypto_cipher* crypto_spawn_cipher (struct crypto_spawn*) ; 
 struct priv* crypto_tfm_ctx (struct crypto_tfm*) ; 

__attribute__((used)) static int init_tfm(struct crypto_tfm *tfm)
{
	struct crypto_cipher *cipher;
	struct crypto_instance *inst = (void *)tfm->__crt_alg;
	struct crypto_spawn *spawn = crypto_instance_ctx(inst);
	struct priv *ctx = crypto_tfm_ctx(tfm);
	u32 *flags = &tfm->crt_flags;

	cipher = crypto_spawn_cipher(spawn);
	if (IS_ERR(cipher))
		return PTR_ERR(cipher);

	if (crypto_cipher_blocksize(cipher) != XTS_BLOCK_SIZE) {
		*flags |= CRYPTO_TFM_RES_BAD_BLOCK_LEN;
		crypto_free_cipher(cipher);
		return -EINVAL;
	}

	ctx->child = cipher;

	cipher = crypto_spawn_cipher(spawn);
	if (IS_ERR(cipher)) {
		crypto_free_cipher(ctx->child);
		return PTR_ERR(cipher);
	}

	/* this check isn't really needed, leave it here just in case */
	if (crypto_cipher_blocksize(cipher) != XTS_BLOCK_SIZE) {
		crypto_free_cipher(cipher);
		crypto_free_cipher(ctx->child);
		*flags |= CRYPTO_TFM_RES_BAD_BLOCK_LEN;
		return -EINVAL;
	}

	ctx->tweak = cipher;

	return 0;
}