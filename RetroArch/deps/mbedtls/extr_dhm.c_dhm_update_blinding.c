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
struct TYPE_3__ {int /*<<< orphan*/  RP; int /*<<< orphan*/  P; int /*<<< orphan*/  X; int /*<<< orphan*/  Vf; int /*<<< orphan*/  Vi; int /*<<< orphan*/  pX; } ;
typedef  TYPE_1__ mbedtls_dhm_context ;

/* Variables and functions */
 int MBEDTLS_ERR_MPI_NOT_ACCEPTABLE ; 
 int /*<<< orphan*/  MBEDTLS_MPI_CHK (int /*<<< orphan*/ ) ; 
 scalar_t__ mbedtls_mpi_cmp_int (int /*<<< orphan*/ *,int) ; 
 scalar_t__ mbedtls_mpi_cmp_mpi (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_mpi_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_mpi_exp_mod (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_mpi_fill_random (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int (*) (void*,unsigned char*,size_t),void*) ; 
 int /*<<< orphan*/  mbedtls_mpi_inv_mod (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_mpi_lset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mbedtls_mpi_mod_mpi (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_mpi_mul_mpi (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_mpi_shift_r (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mbedtls_mpi_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dhm_update_blinding( mbedtls_dhm_context *ctx,
                    int (*f_rng)(void *, unsigned char *, size_t), void *p_rng )
{
    int ret, count;

    /*
     * Don't use any blinding the first time a particular X is used,
     * but remember it to use blinding next time.
     */
    if( mbedtls_mpi_cmp_mpi( &ctx->X, &ctx->pX ) != 0 )
    {
        MBEDTLS_MPI_CHK( mbedtls_mpi_copy( &ctx->pX, &ctx->X ) );
        MBEDTLS_MPI_CHK( mbedtls_mpi_lset( &ctx->Vi, 1 ) );
        MBEDTLS_MPI_CHK( mbedtls_mpi_lset( &ctx->Vf, 1 ) );

        return( 0 );
    }

    /*
     * Ok, we need blinding. Can we re-use existing values?
     * If yes, just update them by squaring them.
     */
    if( mbedtls_mpi_cmp_int( &ctx->Vi, 1 ) != 0 )
    {
        MBEDTLS_MPI_CHK( mbedtls_mpi_mul_mpi( &ctx->Vi, &ctx->Vi, &ctx->Vi ) );
        MBEDTLS_MPI_CHK( mbedtls_mpi_mod_mpi( &ctx->Vi, &ctx->Vi, &ctx->P ) );

        MBEDTLS_MPI_CHK( mbedtls_mpi_mul_mpi( &ctx->Vf, &ctx->Vf, &ctx->Vf ) );
        MBEDTLS_MPI_CHK( mbedtls_mpi_mod_mpi( &ctx->Vf, &ctx->Vf, &ctx->P ) );

        return( 0 );
    }

    /*
     * We need to generate blinding values from scratch
     */

    /* Vi = random( 2, P-1 ) */
    count = 0;
    do
    {
        MBEDTLS_MPI_CHK( mbedtls_mpi_fill_random( &ctx->Vi, mbedtls_mpi_size( &ctx->P ), f_rng, p_rng ) );

        while( mbedtls_mpi_cmp_mpi( &ctx->Vi, &ctx->P ) >= 0 )
            MBEDTLS_MPI_CHK( mbedtls_mpi_shift_r( &ctx->Vi, 1 ) );

        if( count++ > 10 )
            return( MBEDTLS_ERR_MPI_NOT_ACCEPTABLE );
    }
    while( mbedtls_mpi_cmp_int( &ctx->Vi, 1 ) <= 0 );

    /* Vf = Vi^-X mod P */
    MBEDTLS_MPI_CHK( mbedtls_mpi_inv_mod( &ctx->Vf, &ctx->Vi, &ctx->P ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_exp_mod( &ctx->Vf, &ctx->Vf, &ctx->X, &ctx->P, &ctx->RP ) );

cleanup:
    return( ret );
}