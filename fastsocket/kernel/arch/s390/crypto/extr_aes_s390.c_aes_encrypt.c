#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  cip; } ;
struct s390_aes_ctx {int key_len; int /*<<< orphan*/  key; TYPE_1__ fallback; } ;
struct crypto_tfm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AES_BLOCK_SIZE ; 
 int /*<<< orphan*/  KM_AES_128_ENCRYPT ; 
 int /*<<< orphan*/  KM_AES_192_ENCRYPT ; 
 int /*<<< orphan*/  KM_AES_256_ENCRYPT ; 
 int /*<<< orphan*/  crypt_s390_km (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_cipher_encrypt_one (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 struct s390_aes_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  need_fallback (int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void aes_encrypt(struct crypto_tfm *tfm, u8 *out, const u8 *in)
{
	const struct s390_aes_ctx *sctx = crypto_tfm_ctx(tfm);

	if (unlikely(need_fallback(sctx->key_len))) {
		crypto_cipher_encrypt_one(sctx->fallback.cip, out, in);
		return;
	}

	switch (sctx->key_len) {
	case 16:
		crypt_s390_km(KM_AES_128_ENCRYPT, &sctx->key, out, in,
			      AES_BLOCK_SIZE);
		break;
	case 24:
		crypt_s390_km(KM_AES_192_ENCRYPT, &sctx->key, out, in,
			      AES_BLOCK_SIZE);
		break;
	case 32:
		crypt_s390_km(KM_AES_256_ENCRYPT, &sctx->key, out, in,
			      AES_BLOCK_SIZE);
		break;
	}
}