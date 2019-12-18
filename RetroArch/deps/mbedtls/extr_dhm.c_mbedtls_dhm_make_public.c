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
struct TYPE_3__ {size_t len; int /*<<< orphan*/  GX; int /*<<< orphan*/  P; int /*<<< orphan*/  RP; int /*<<< orphan*/  X; int /*<<< orphan*/  G; } ;
typedef  TYPE_1__ mbedtls_dhm_context ;

/* Variables and functions */
 int MBEDTLS_ERR_DHM_BAD_INPUT_DATA ; 
 int MBEDTLS_ERR_DHM_MAKE_PUBLIC_FAILED ; 
 int /*<<< orphan*/  MBEDTLS_MPI_CHK (int /*<<< orphan*/ ) ; 
 int dhm_check_range (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ mbedtls_mpi_cmp_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ mbedtls_mpi_cmp_mpi (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_mpi_exp_mod (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_mpi_fill_random (int /*<<< orphan*/ *,int,int (*) (void*,unsigned char*,size_t),void*) ; 
 int /*<<< orphan*/  mbedtls_mpi_shift_r (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mbedtls_mpi_write_binary (int /*<<< orphan*/ *,unsigned char*,size_t) ; 

int mbedtls_dhm_make_public( mbedtls_dhm_context *ctx, int x_size,
                     unsigned char *output, size_t olen,
                     int (*f_rng)(void *, unsigned char *, size_t),
                     void *p_rng )
{
    int ret, count = 0;

    if( ctx == NULL || olen < 1 || olen > ctx->len )
        return( MBEDTLS_ERR_DHM_BAD_INPUT_DATA );

    if( mbedtls_mpi_cmp_int( &ctx->P, 0 ) == 0 )
        return( MBEDTLS_ERR_DHM_BAD_INPUT_DATA );

    /*
     * generate X and calculate GX = G^X mod P
     */
    do
    {
        MBEDTLS_MPI_CHK( mbedtls_mpi_fill_random( &ctx->X, x_size, f_rng, p_rng ) );

        while( mbedtls_mpi_cmp_mpi( &ctx->X, &ctx->P ) >= 0 )
            MBEDTLS_MPI_CHK( mbedtls_mpi_shift_r( &ctx->X, 1 ) );

        if( count++ > 10 )
            return( MBEDTLS_ERR_DHM_MAKE_PUBLIC_FAILED );
    }
    while( dhm_check_range( &ctx->X, &ctx->P ) != 0 );

    MBEDTLS_MPI_CHK( mbedtls_mpi_exp_mod( &ctx->GX, &ctx->G, &ctx->X,
                          &ctx->P , &ctx->RP ) );

    if( ( ret = dhm_check_range( &ctx->GX, &ctx->P ) ) != 0 )
        return( ret );

    MBEDTLS_MPI_CHK( mbedtls_mpi_write_binary( &ctx->GX, output, olen ) );

cleanup:

    if( ret != 0 )
        return( MBEDTLS_ERR_DHM_MAKE_PUBLIC_FAILED + ret );

    return( 0 );
}