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
typedef  int /*<<< orphan*/  mbedtls_sha512_context ;
typedef  int /*<<< orphan*/  crypto_hash_sha512_state ;

/* Variables and functions */
 int mbedtls_sha512_update_ret (int /*<<< orphan*/ *,unsigned char const*,unsigned long long) ; 
 int /*<<< orphan*/  sha512_libsodium_to_mbedtls (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sha512_mbedtls_to_libsodium (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
crypto_hash_sha512_update(crypto_hash_sha512_state *state,
                          const unsigned char *in, unsigned long long inlen)
{
    mbedtls_sha512_context ctx;
    sha512_libsodium_to_mbedtls(&ctx, state);
    int ret = mbedtls_sha512_update_ret(&ctx, in, inlen);
    if (ret != 0) {
        return ret;
    }
    sha512_mbedtls_to_libsodium(state, &ctx);
    return 0;
}