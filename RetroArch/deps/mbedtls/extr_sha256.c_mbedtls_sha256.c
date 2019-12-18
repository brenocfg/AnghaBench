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
typedef  int /*<<< orphan*/  mbedtls_sha256_context ;

/* Variables and functions */
 int /*<<< orphan*/  mbedtls_sha256_finish (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  mbedtls_sha256_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_sha256_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_sha256_starts (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mbedtls_sha256_update (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 

void mbedtls_sha256( const unsigned char *input, size_t ilen,
             unsigned char output[32], int is224 )
{
    mbedtls_sha256_context ctx;

    mbedtls_sha256_init( &ctx );
    mbedtls_sha256_starts( &ctx, is224 );
    mbedtls_sha256_update( &ctx, input, ilen );
    mbedtls_sha256_finish( &ctx, output );
    mbedtls_sha256_free( &ctx );
}