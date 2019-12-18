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
 int mbedtls_sha512_finish_ret (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  sha512_libsodium_to_mbedtls (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
crypto_hash_sha512_final(crypto_hash_sha512_state *state, unsigned char *out)
{
    mbedtls_sha512_context ctx;
    sha512_libsodium_to_mbedtls(&ctx, state);
    return mbedtls_sha512_finish_ret(&ctx, out);
}