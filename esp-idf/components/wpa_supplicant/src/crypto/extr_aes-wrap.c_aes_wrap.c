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
typedef  int /*<<< orphan*/  mbedtls_aes_context ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  aes_encrypt (void*,int*,int*) ; 
 int /*<<< orphan*/  aes_encrypt_deinit (void*) ; 
 void* aes_encrypt_init (int const*,int) ; 
 int /*<<< orphan*/  mbedtls_aes_free (void**) ; 
 int /*<<< orphan*/  mbedtls_aes_init (void**) ; 
 scalar_t__ mbedtls_aes_setkey_enc (void**,int const*,int) ; 
 scalar_t__ mbedtls_internal_aes_encrypt (void**,int*,int*) ; 
 int /*<<< orphan*/  os_memcpy (int*,int const*,int) ; 
 int /*<<< orphan*/  os_memset (int*,int,int) ; 

int  aes_wrap(const u8 *kek, int n, const u8 *plain, u8 *cipher)
{
	u8 *a, *r, b[16];
	int i, j;
#ifdef USE_MBEDTLS_CRYPTO
	int32_t ret = 0;
	mbedtls_aes_context ctx;
#else /* USE_MBEDTLS_CRYPTO */
	void *ctx;
#endif /* USE_MBEDTLS_CRYPTO */

	a = cipher;
	r = cipher + 8;

	/* 1) Initialize variables. */
	os_memset(a, 0xa6, 8);
	os_memcpy(r, plain, 8 * n);

#ifdef USE_MBEDTLS_CRYPTO
	mbedtls_aes_init(&ctx);
	ret = mbedtls_aes_setkey_enc(&ctx, kek, 128);
	if (ret < 0) {
		mbedtls_aes_free(&ctx);
		return ret;
	}
#else /* USE_MBEDTLS_CRYPTO */
	ctx = aes_encrypt_init(kek, 16);
	if (ctx == NULL)
		return -1;
#endif /* USE_MBEDTLS_CRYPTO */

	/* 2) Calculate intermediate values.
	 * For j = 0 to 5
	 *     For i=1 to n
	 *         B = AES(K, A | R[i])
	 *         A = MSB(64, B) ^ t where t = (n*j)+i
	 *         R[i] = LSB(64, B)
	 */
	for (j = 0; j <= 5; j++) {
		r = cipher + 8;
		for (i = 1; i <= n; i++) {
			os_memcpy(b, a, 8);
			os_memcpy(b + 8, r, 8);
#ifdef USE_MBEDTLS_CRYPTO
			ret = mbedtls_internal_aes_encrypt(&ctx, b, b);
			if (ret != 0)
				break;
#else /* USE_MBEDTLS_CRYPTO */
			aes_encrypt(ctx, b, b);
#endif /* USE_MBEDTLS_CRYPTO */
			os_memcpy(a, b, 8);
			a[7] ^= n * j + i;
			os_memcpy(r, b + 8, 8);
			r += 8;
		}
	}
#ifdef USE_MBEDTLS_CRYPTO
	mbedtls_aes_free(&ctx);
#else /* USE_MBEDTLS_CRYPTO */
	aes_encrypt_deinit(ctx);
#endif /* USE_MBEDTLS_CRYPTO */

	/* 3) Output the results.
	 *
	 * These are already in @cipher due to the location of temporary
	 * variables.
	 */

	return 0;
}