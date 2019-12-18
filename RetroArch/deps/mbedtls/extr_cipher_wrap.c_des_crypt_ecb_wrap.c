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
typedef  scalar_t__ mbedtls_operation_t ;
typedef  int /*<<< orphan*/  mbedtls_des_context ;

/* Variables and functions */
 int mbedtls_des_crypt_ecb (int /*<<< orphan*/ *,unsigned char const*,unsigned char*) ; 

__attribute__((used)) static int des_crypt_ecb_wrap( void *ctx, mbedtls_operation_t operation,
        const unsigned char *input, unsigned char *output )
{
    ((void) operation);
    return mbedtls_des_crypt_ecb( (mbedtls_des_context *) ctx, input, output );
}