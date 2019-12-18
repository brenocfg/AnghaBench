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
typedef  int u8 ;
struct TYPE_2__ {int /*<<< orphan*/  sha256; int /*<<< orphan*/  sha1; int /*<<< orphan*/  md5; } ;
struct crypto_hash {int alg; int* key; size_t key_len; TYPE_1__ u; } ;
typedef  int /*<<< orphan*/  k_pad ;
typedef  enum crypto_hash_alg { ____Placeholder_crypto_hash_alg } crypto_hash_alg ;

/* Variables and functions */
#define  CRYPTO_HASH_ALG_HMAC_MD5 133 
#define  CRYPTO_HASH_ALG_HMAC_SHA1 132 
#define  CRYPTO_HASH_ALG_HMAC_SHA256 131 
#define  CRYPTO_HASH_ALG_MD5 130 
#define  CRYPTO_HASH_ALG_SHA1 129 
#define  CRYPTO_HASH_ALG_SHA256 128 
 int /*<<< orphan*/  MD5Final (int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5Update (int /*<<< orphan*/ *,int const*,int) ; 
 int /*<<< orphan*/  SHA1Final (int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA1Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA1Update (int /*<<< orphan*/ *,int const*,int) ; 
 int /*<<< orphan*/  mbedtls_sha256_finish (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  mbedtls_sha256_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_sha256_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_sha256_starts (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_sha256_update (int /*<<< orphan*/ *,int const*,int) ; 
 int /*<<< orphan*/  os_free (struct crypto_hash*) ; 
 int /*<<< orphan*/  os_memcpy (int*,int const*,size_t) ; 
 int /*<<< orphan*/  os_memset (int*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ os_zalloc (int) ; 
 int /*<<< orphan*/  sha256_done (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  sha256_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sha256_process (int /*<<< orphan*/ *,int const*,int) ; 

struct crypto_hash *  crypto_hash_init(enum crypto_hash_alg alg, const u8 *key,
				      size_t key_len)
{
	struct crypto_hash *ctx;
	u8 k_pad[64];
	u8 tk[32];
	size_t i;

	ctx = (struct crypto_hash *)os_zalloc(sizeof(*ctx));
	if (ctx == NULL)
		return NULL;

	ctx->alg = alg;

	switch (alg) {
	case CRYPTO_HASH_ALG_MD5:
		MD5Init(&ctx->u.md5);
		break;
	case CRYPTO_HASH_ALG_SHA1:
		SHA1Init(&ctx->u.sha1);
		break;
#ifdef CONFIG_SHA256
	case CRYPTO_HASH_ALG_SHA256:
#ifdef USE_MBEDTLS_CRYPTO
		mbedtls_sha256_init(&ctx->u.sha256);
		mbedtls_sha256_starts(&ctx->u.sha256, 0);
#else /* USE_MBEDTLS_CRYPTO */
		sha256_init(&ctx->u.sha256);
#endif /* USE_MBEDTLS_CRYPTO */
		break;
#endif /* CONFIG_SHA256 */
	case CRYPTO_HASH_ALG_HMAC_MD5:
		if (key_len > sizeof(k_pad)) {
			MD5Init(&ctx->u.md5);
			MD5Update(&ctx->u.md5, key, key_len);
			MD5Final(tk, &ctx->u.md5);
			key = tk;
			key_len = 16;
		}
		os_memcpy(ctx->key, key, key_len);
		ctx->key_len = key_len;

		os_memcpy(k_pad, key, key_len);
		if (key_len < sizeof(k_pad))
			os_memset(k_pad + key_len, 0, sizeof(k_pad) - key_len);
		for (i = 0; i < sizeof(k_pad); i++)
			k_pad[i] ^= 0x36;
		MD5Init(&ctx->u.md5);
		MD5Update(&ctx->u.md5, k_pad, sizeof(k_pad));
		break;
	case CRYPTO_HASH_ALG_HMAC_SHA1:
		if (key_len > sizeof(k_pad)) {
			SHA1Init(&ctx->u.sha1);
			SHA1Update(&ctx->u.sha1, key, key_len);
			SHA1Final(tk, &ctx->u.sha1);
			key = tk;
			key_len = 20;
		}
		os_memcpy(ctx->key, key, key_len);
		ctx->key_len = key_len;

		os_memcpy(k_pad, key, key_len);
		if (key_len < sizeof(k_pad))
			os_memset(k_pad + key_len, 0, sizeof(k_pad) - key_len);
		for (i = 0; i < sizeof(k_pad); i++)
			k_pad[i] ^= 0x36;
		SHA1Init(&ctx->u.sha1);
		SHA1Update(&ctx->u.sha1, k_pad, sizeof(k_pad));
		break;
#ifdef CONFIG_SHA256
	case CRYPTO_HASH_ALG_HMAC_SHA256:
		if (key_len > sizeof(k_pad)) {
#ifdef USE_MBEDTLS_CRYPTO
			mbedtls_sha256_init(&ctx->u.sha256);
			mbedtls_sha256_starts(&ctx->u.sha256, 0);
			mbedtls_sha256_update(&ctx->u.sha256, key, key_len);
			mbedtls_sha256_finish(&ctx->u.sha256, tk);
			mbedtls_sha256_free(&ctx->u.sha256);
#else /* USE_MBEDTLS_CRYPTO */
			sha256_init(&ctx->u.sha256);
			sha256_process(&ctx->u.sha256, key, key_len);
			sha256_done(&ctx->u.sha256, tk);
#endif /* USE_MBEDTLS_CRYPTO */
			key = tk;
			key_len = 32;
		}
		os_memcpy(ctx->key, key, key_len);
		ctx->key_len = key_len;

		os_memcpy(k_pad, key, key_len);
		if (key_len < sizeof(k_pad))
			os_memset(k_pad + key_len, 0, sizeof(k_pad) - key_len);
		for (i = 0; i < sizeof(k_pad); i++)
			k_pad[i] ^= 0x36;
#ifdef USE_MBEDTLS_CRYPTO
		mbedtls_sha256_init(&ctx->u.sha256);
		mbedtls_sha256_starts(&ctx->u.sha256, 0);
		mbedtls_sha256_update(&ctx->u.sha256, k_pad, sizeof(k_pad));
#else /* USE_MBEDTLS_CRYPTO */
		sha256_init(&ctx->u.sha256);
		sha256_process(&ctx->u.sha256, k_pad, sizeof(k_pad));
#endif /* USE_MBEDTLS_CRYPTO */
		break;
#endif /* CONFIG_SHA256 */
	default:
		os_free(ctx);
		return NULL;
	}

	return ctx;
}