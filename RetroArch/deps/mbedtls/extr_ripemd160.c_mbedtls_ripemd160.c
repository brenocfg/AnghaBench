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
typedef  int /*<<< orphan*/  mbedtls_ripemd160_context ;

/* Variables and functions */
 int /*<<< orphan*/  mbedtls_ripemd160_finish (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  mbedtls_ripemd160_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_ripemd160_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_ripemd160_starts (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_ripemd160_update (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 

void mbedtls_ripemd160( const unsigned char *input, size_t ilen,
                unsigned char output[20] )
{
    mbedtls_ripemd160_context ctx;

    mbedtls_ripemd160_init( &ctx );
    mbedtls_ripemd160_starts( &ctx );
    mbedtls_ripemd160_update( &ctx, input, ilen );
    mbedtls_ripemd160_finish( &ctx, output );
    mbedtls_ripemd160_free( &ctx );
}