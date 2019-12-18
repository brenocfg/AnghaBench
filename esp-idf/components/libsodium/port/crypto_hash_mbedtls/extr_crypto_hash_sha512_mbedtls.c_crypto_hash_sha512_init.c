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
 int /*<<< orphan*/  mbedtls_sha512_init (int /*<<< orphan*/ *) ; 
 int mbedtls_sha512_starts_ret (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sha512_mbedtls_to_libsodium (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
crypto_hash_sha512_init(crypto_hash_sha512_state *state)
{
    mbedtls_sha512_context ctx;
    mbedtls_sha512_init(&ctx);
    int ret = mbedtls_sha512_starts_ret(&ctx, 0);
    if (ret != 0) {
        return ret;
    }
    sha512_mbedtls_to_libsodium(state, &ctx);
    return 0;
}