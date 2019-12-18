#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mbedtls_mpi ;
struct TYPE_4__ {size_t len; int /*<<< orphan*/  K; int /*<<< orphan*/  P; int /*<<< orphan*/  Vf; int /*<<< orphan*/  RP; int /*<<< orphan*/  X; int /*<<< orphan*/  GY; int /*<<< orphan*/  Vi; } ;
typedef  TYPE_1__ mbedtls_dhm_context ;

/* Variables and functions */
 int MBEDTLS_ERR_DHM_BAD_INPUT_DATA ; 
 int MBEDTLS_ERR_DHM_CALC_SECRET_FAILED ; 
 int /*<<< orphan*/  MBEDTLS_MPI_CHK (int /*<<< orphan*/ ) ; 
 int dhm_check_range (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dhm_update_blinding (TYPE_1__*,int (*) (void*,unsigned char*,size_t),void*) ; 
 int /*<<< orphan*/  mbedtls_mpi_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_mpi_exp_mod (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_mpi_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_mpi_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_mpi_mod_mpi (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_mpi_mul_mpi (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t mbedtls_mpi_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_mpi_write_binary (int /*<<< orphan*/ *,unsigned char*,size_t) ; 

int mbedtls_dhm_calc_secret( mbedtls_dhm_context *ctx,
                     unsigned char *output, size_t output_size, size_t *olen,
                     int (*f_rng)(void *, unsigned char *, size_t),
                     void *p_rng )
{
    int ret;
    mbedtls_mpi GYb;

    if( ctx == NULL || output_size < ctx->len )
        return( MBEDTLS_ERR_DHM_BAD_INPUT_DATA );

    if( ( ret = dhm_check_range( &ctx->GY, &ctx->P ) ) != 0 )
        return( ret );

    mbedtls_mpi_init( &GYb );

    /* Blind peer's value */
    if( f_rng != NULL )
    {
        MBEDTLS_MPI_CHK( dhm_update_blinding( ctx, f_rng, p_rng ) );
        MBEDTLS_MPI_CHK( mbedtls_mpi_mul_mpi( &GYb, &ctx->GY, &ctx->Vi ) );
        MBEDTLS_MPI_CHK( mbedtls_mpi_mod_mpi( &GYb, &GYb, &ctx->P ) );
    }
    else
        MBEDTLS_MPI_CHK( mbedtls_mpi_copy( &GYb, &ctx->GY ) );

    /* Do modular exponentiation */
    MBEDTLS_MPI_CHK( mbedtls_mpi_exp_mod( &ctx->K, &GYb, &ctx->X,
                          &ctx->P, &ctx->RP ) );

    /* Unblind secret value */
    if( f_rng != NULL )
    {
        MBEDTLS_MPI_CHK( mbedtls_mpi_mul_mpi( &ctx->K, &ctx->K, &ctx->Vf ) );
        MBEDTLS_MPI_CHK( mbedtls_mpi_mod_mpi( &ctx->K, &ctx->K, &ctx->P ) );
    }

    *olen = mbedtls_mpi_size( &ctx->K );

    MBEDTLS_MPI_CHK( mbedtls_mpi_write_binary( &ctx->K, output, *olen ) );

cleanup:
    mbedtls_mpi_free( &GYb );

    if( ret != 0 )
        return( MBEDTLS_ERR_DHM_CALC_SECRET_FAILED + ret );

    return( 0 );
}