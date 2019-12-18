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
typedef  int /*<<< orphan*/  mbedtls_operation_t ;
typedef  int /*<<< orphan*/  mbedtls_camellia_context ;

/* Variables and functions */
 int mbedtls_camellia_crypt_cfb128 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t,size_t*,unsigned char*,unsigned char const*,unsigned char*) ; 

__attribute__((used)) static int camellia_crypt_cfb128_wrap( void *ctx, mbedtls_operation_t operation,
        size_t length, size_t *iv_off, unsigned char *iv,
        const unsigned char *input, unsigned char *output )
{
    return mbedtls_camellia_crypt_cfb128( (mbedtls_camellia_context *) ctx, operation, length,
                                  iv_off, iv, input, output );
}