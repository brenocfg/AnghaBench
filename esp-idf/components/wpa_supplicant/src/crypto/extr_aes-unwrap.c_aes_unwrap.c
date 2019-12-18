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
 int /*<<< orphan*/  aes_decrypt (void*,int*,int*) ; 
 int /*<<< orphan*/  aes_decrypt_deinit (void*) ; 
 void* aes_decrypt_init (int const*,int) ; 
 int /*<<< orphan*/  mbedtls_aes_free (void**) ; 
 int /*<<< orphan*/  mbedtls_aes_init (void**) ; 
 scalar_t__ mbedtls_aes_setkey_dec (void**,int const*,int) ; 
 scalar_t__ mbedtls_internal_aes_decrypt (void**,int*,int*) ; 
 int /*<<< orphan*/  os_memcpy (int*,int const*,int) ; 

int 
aes_unwrap(const u8 *kek, int n, const u8 *cipher, u8 *plain)
{
	u8 a[8], *r, b[16];
	int i, j;
#ifdef USE_MBEDTLS_CRYPTO
	int32_t ret = 0;
	mbedtls_aes_context ctx;
#else /* USE_MBEDTLS_CRYPTO */
	void *ctx;
#endif /* USE_MBEDTLS_CRYPTO */

	/* 1) Initialize variables. */
	os_memcpy(a, cipher, 8);
	r = plain;
	os_memcpy(r, cipher + 8, 8 * n);

#ifdef USE_MBEDTLS_CRYPTO
	mbedtls_aes_init(&ctx);
	ret = mbedtls_aes_setkey_dec(&ctx, kek, 128);
	if (ret < 0) {
		mbedtls_aes_free(&ctx);
		return ret;
	}
#else /* USE_MBEDTLS_CRYPTO */
	ctx = aes_decrypt_init(kek, 16);
	if (ctx == NULL)
		return -1;
#endif /* USE_MBEDTLS_CRYPTO */

	/* 2) Compute intermediate values.
	 * For j = 5 to 0
	 *     For i = n to 1
	 *         B = AES-1(K, (A ^ t) | R[i]) where t = n*j+i
	 *         A = MSB(64, B)
	 *         R[i] = LSB(64, B)
	 */
	for (j = 5; j >= 0; j--) {
		r = plain + (n - 1) * 8;
		for (i = n; i >= 1; i--) {
			os_memcpy(b, a, 8);
			b[7] ^= n * j + i;

			os_memcpy(b + 8, r, 8);
#ifdef USE_MBEDTLS_CRYPTO
			ret = mbedtls_internal_aes_decrypt(&ctx, b, b);
#else /* USE_MBEDTLS_CRYPTO */
			aes_decrypt(ctx, b, b);
#endif /* USE_MBEDTLS_CRYPTO */
			os_memcpy(a, b, 8);
			os_memcpy(r, b + 8, 8);
			r -= 8;
		}
	}
#ifdef USE_MBEDTLS_CRYPTO
	mbedtls_aes_free(&ctx);
#else /* USE_MBEDTLS_CRYPTO */
	aes_decrypt_deinit(ctx);
#endif /* USE_MBEDTLS_CRYPTO */

	/* 3) Output results.
	 *
	 * These are already in @plain due to the location of temporary
	 * variables. Just verify that the IV matches with the expected value.
	 */
	for (i = 0; i < 8; i++) {
		if (a[i] != 0xa6)
			return -1;
	}

	return 0;
}