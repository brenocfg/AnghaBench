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
typedef  int /*<<< orphan*/  mbedtls_des_context ;

/* Variables and functions */
 int mbedtls_des_crypt_cbc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t,unsigned char*,unsigned char const*,unsigned char*) ; 

__attribute__((used)) static int des_crypt_cbc_wrap( void *ctx, mbedtls_operation_t operation, size_t length,
        unsigned char *iv, const unsigned char *input, unsigned char *output )
{
    return mbedtls_des_crypt_cbc( (mbedtls_des_context *) ctx, operation, length, iv, input,
                          output );
}