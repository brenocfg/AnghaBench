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

/* Variables and functions */
 int /*<<< orphan*/  mbedtls_sha512_finish (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  mbedtls_sha512_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_sha512_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_sha512_starts (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mbedtls_sha512_update (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 

void mbedtls_sha512( const unsigned char *input, size_t ilen,
             unsigned char output[64], int is384 )
{
    mbedtls_sha512_context ctx;

    mbedtls_sha512_init( &ctx );
    mbedtls_sha512_starts( &ctx, is384 );
    mbedtls_sha512_update( &ctx, input, ilen );
    mbedtls_sha512_finish( &ctx, output );
    mbedtls_sha512_free( &ctx );
}