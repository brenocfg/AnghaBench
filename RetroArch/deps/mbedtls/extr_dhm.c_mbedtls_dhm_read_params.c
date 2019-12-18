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
struct TYPE_3__ {int /*<<< orphan*/  P; int /*<<< orphan*/  len; int /*<<< orphan*/  GY; int /*<<< orphan*/  G; } ;
typedef  TYPE_1__ mbedtls_dhm_context ;

/* Variables and functions */
 int dhm_check_range (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int dhm_read_bignum (int /*<<< orphan*/ *,unsigned char**,unsigned char const*) ; 
 int /*<<< orphan*/  mbedtls_mpi_size (int /*<<< orphan*/ *) ; 

int mbedtls_dhm_read_params( mbedtls_dhm_context *ctx,
                     unsigned char **p,
                     const unsigned char *end )
{
    int ret;

    if( ( ret = dhm_read_bignum( &ctx->P,  p, end ) ) != 0 ||
        ( ret = dhm_read_bignum( &ctx->G,  p, end ) ) != 0 ||
        ( ret = dhm_read_bignum( &ctx->GY, p, end ) ) != 0 )
        return( ret );

    if( ( ret = dhm_check_range( &ctx->GY, &ctx->P ) ) != 0 )
        return( ret );

    ctx->len = mbedtls_mpi_size( &ctx->P );

    return( 0 );
}