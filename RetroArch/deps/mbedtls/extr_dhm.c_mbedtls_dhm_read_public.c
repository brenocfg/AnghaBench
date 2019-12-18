#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t len; int /*<<< orphan*/  GY; } ;
typedef  TYPE_1__ mbedtls_dhm_context ;

/* Variables and functions */
 int MBEDTLS_ERR_DHM_BAD_INPUT_DATA ; 
 int MBEDTLS_ERR_DHM_READ_PUBLIC_FAILED ; 
 int mbedtls_mpi_read_binary (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 

int mbedtls_dhm_read_public( mbedtls_dhm_context *ctx,
                     const unsigned char *input, size_t ilen )
{
    int ret;

    if( ctx == NULL || ilen < 1 || ilen > ctx->len )
        return( MBEDTLS_ERR_DHM_BAD_INPUT_DATA );

    if( ( ret = mbedtls_mpi_read_binary( &ctx->GY, input, ilen ) ) != 0 )
        return( MBEDTLS_ERR_DHM_READ_PUBLIC_FAILED + ret );

    return( 0 );
}