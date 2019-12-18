#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_9__ {int /*<<< orphan*/  cbc; int /*<<< orphan*/  dk; int /*<<< orphan*/  ek; } ;
struct TYPE_8__ {int /*<<< orphan*/  cbc; int /*<<< orphan*/  key; } ;
struct TYPE_7__ {int /*<<< orphan*/  cbc; int /*<<< orphan*/ * ctx_enc; int /*<<< orphan*/ * ctx_dec; } ;
struct TYPE_6__ {size_t keylen; int /*<<< orphan*/  key; } ;
struct TYPE_10__ {TYPE_4__ des; TYPE_3__ des3; TYPE_2__ aes; TYPE_1__ rc4; } ;
struct crypto_cipher {int alg; TYPE_5__ u; } ;
typedef  enum crypto_cipher_alg { ____Placeholder_crypto_cipher_alg } crypto_cipher_alg ;

/* Variables and functions */
 int AES_BLOCK_SIZE ; 
#define  CRYPTO_CIPHER_ALG_3DES 131 
#define  CRYPTO_CIPHER_ALG_AES 130 
#define  CRYPTO_CIPHER_ALG_DES 129 
#define  CRYPTO_CIPHER_ALG_RC4 128 
 int /*<<< orphan*/ * aes_decrypt_init (int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  aes_encrypt_deinit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * aes_encrypt_init (int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  des3_key_setup (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  des_key_setup (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_aes_init (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  mbedtls_aes_setkey_dec (int /*<<< orphan*/ **,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  mbedtls_aes_setkey_enc (int /*<<< orphan*/ **,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  os_free (struct crypto_cipher*) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 scalar_t__ os_zalloc (int) ; 

struct crypto_cipher *  crypto_cipher_init(enum crypto_cipher_alg alg,
					  const u8 *iv, const u8 *key,
					  size_t key_len)
{
	struct crypto_cipher *ctx;

	ctx = (struct crypto_cipher *)os_zalloc(sizeof(*ctx));
	if (ctx == NULL)
		return NULL;

	ctx->alg = alg;

	switch (alg) {
	case CRYPTO_CIPHER_ALG_RC4:
		if (key_len > sizeof(ctx->u.rc4.key)) {
			os_free(ctx);
			return NULL;
		}
		ctx->u.rc4.keylen = key_len;
		os_memcpy(ctx->u.rc4.key, key, key_len);
		break;
	case CRYPTO_CIPHER_ALG_AES:
#ifdef USE_MBEDTLS_CRYPTO
		mbedtls_aes_init(&(ctx->u.aes.ctx_enc));
		mbedtls_aes_setkey_enc(&(ctx->u.aes.ctx_enc), key, key_len * 8);
		mbedtls_aes_init(&(ctx->u.aes.ctx_dec));
		mbedtls_aes_setkey_dec(&(ctx->u.aes.ctx_dec), key, key_len * 8);
#else /* USE_MBEDTLS_CRYPTO */
		ctx->u.aes.ctx_enc = aes_encrypt_init(key, key_len);
		if (ctx->u.aes.ctx_enc == NULL) {
			os_free(ctx);
			return NULL;
		}
		ctx->u.aes.ctx_dec = aes_decrypt_init(key, key_len);
		if (ctx->u.aes.ctx_dec == NULL) {
			aes_encrypt_deinit(ctx->u.aes.ctx_enc);
			os_free(ctx);
			return NULL;
		}
#endif /* USE_MBEDTLS_CRYPTO */
		os_memcpy(ctx->u.aes.cbc, iv, AES_BLOCK_SIZE);
		break;
#ifdef CONFIG_DES3
	case CRYPTO_CIPHER_ALG_3DES:
		if (key_len != 24) {
			os_free(ctx);
			return NULL;
		}
		des3_key_setup(key, &ctx->u.des3.key);
		os_memcpy(ctx->u.des3.cbc, iv, 8);
		break;
#endif
#ifdef CONFIG_DES
	case CRYPTO_CIPHER_ALG_DES:
		if (key_len != 8) {
			os_free(ctx);
			return NULL;
		}
		des_key_setup(key, ctx->u.des.ek, ctx->u.des.dk);
		os_memcpy(ctx->u.des.cbc, iv, 8);
		break;
#endif
	default:
		os_free(ctx);
		return NULL;
	}

	return ctx;
}