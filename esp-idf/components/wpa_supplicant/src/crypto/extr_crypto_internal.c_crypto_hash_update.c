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
struct TYPE_2__ {int /*<<< orphan*/  sha256; int /*<<< orphan*/  sha1; int /*<<< orphan*/  md5; } ;
struct crypto_hash {int alg; TYPE_1__ u; } ;

/* Variables and functions */
#define  CRYPTO_HASH_ALG_HMAC_MD5 133 
#define  CRYPTO_HASH_ALG_HMAC_SHA1 132 
#define  CRYPTO_HASH_ALG_HMAC_SHA256 131 
#define  CRYPTO_HASH_ALG_MD5 130 
#define  CRYPTO_HASH_ALG_SHA1 129 
#define  CRYPTO_HASH_ALG_SHA256 128 
 int /*<<< orphan*/  MD5Update (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  SHA1Update (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  mbedtls_sha256_update (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  sha256_process (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 

void  crypto_hash_update(struct crypto_hash *ctx, const u8 *data, size_t len)
{
	if (ctx == NULL)
		return;

	switch (ctx->alg) {
	case CRYPTO_HASH_ALG_MD5:
	case CRYPTO_HASH_ALG_HMAC_MD5:
		MD5Update(&ctx->u.md5, data, len);
		break;
	case CRYPTO_HASH_ALG_SHA1:
	case CRYPTO_HASH_ALG_HMAC_SHA1:
		SHA1Update(&ctx->u.sha1, data, len);
		break;
#ifdef CONFIG_SHA256
	case CRYPTO_HASH_ALG_SHA256:
	case CRYPTO_HASH_ALG_HMAC_SHA256:
#ifdef USE_MBEDTLS_CRYPTO
		mbedtls_sha256_update(&ctx->u.sha256, data, len);
#else /* USE_MBEDTLS_CRYPTO */
		sha256_process(&ctx->u.sha256, data, len);
#endif /* USE_MBEDTLS_CRYPTO */
		break;
#endif /* CONFIG_SHA256 */
	default:
		break;
	}
}