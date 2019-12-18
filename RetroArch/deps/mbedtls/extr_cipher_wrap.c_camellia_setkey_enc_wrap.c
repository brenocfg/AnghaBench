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
typedef  int /*<<< orphan*/  mbedtls_camellia_context ;

/* Variables and functions */
 int mbedtls_camellia_setkey_enc (int /*<<< orphan*/ *,unsigned char const*,unsigned int) ; 

__attribute__((used)) static int camellia_setkey_enc_wrap( void *ctx, const unsigned char *key,
                                     unsigned int key_bitlen )
{
    return mbedtls_camellia_setkey_enc( (mbedtls_camellia_context *) ctx, key, key_bitlen );
}