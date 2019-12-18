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
struct TYPE_4__ {int len; int /*<<< orphan*/  N; int /*<<< orphan*/  P; int /*<<< orphan*/  Q; int /*<<< orphan*/  QP; int /*<<< orphan*/  D; int /*<<< orphan*/  DQ; int /*<<< orphan*/  DP; int /*<<< orphan*/  E; } ;
typedef  TYPE_1__ mbedtls_rsa_context ;
typedef  int /*<<< orphan*/  mbedtls_mpi ;

/* Variables and functions */
 int MBEDTLS_ERR_RSA_BAD_INPUT_DATA ; 
 int MBEDTLS_ERR_RSA_KEY_GEN_FAILED ; 
 int /*<<< orphan*/  MBEDTLS_MPI_CHK (int /*<<< orphan*/ ) ; 
 int mbedtls_mpi_bitlen (int /*<<< orphan*/ *) ; 
 scalar_t__ mbedtls_mpi_cmp_int (int /*<<< orphan*/ *,int) ; 
 scalar_t__ mbedtls_mpi_cmp_mpi (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_mpi_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_mpi_gcd (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_mpi_gen_prime (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ,int (*) (void*,unsigned char*,size_t),void*) ; 
 int /*<<< orphan*/  mbedtls_mpi_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_mpi_inv_mod (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_mpi_lset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mbedtls_mpi_mod_mpi (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_mpi_mul_mpi (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_mpi_sub_int (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mbedtls_mpi_swap (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_rsa_free (TYPE_1__*) ; 

int mbedtls_rsa_gen_key( mbedtls_rsa_context *ctx,
                 int (*f_rng)(void *, unsigned char *, size_t),
                 void *p_rng,
                 unsigned int nbits, int exponent )
{
    int ret;
    mbedtls_mpi P1, Q1, H, G;

    if( f_rng == NULL || nbits < 128 || exponent < 3 )
        return( MBEDTLS_ERR_RSA_BAD_INPUT_DATA );

    if( nbits % 2 )
        return( MBEDTLS_ERR_RSA_BAD_INPUT_DATA );

    mbedtls_mpi_init( &P1 ); mbedtls_mpi_init( &Q1 );
    mbedtls_mpi_init( &H ); mbedtls_mpi_init( &G );

    /*
     * find primes P and Q with Q < P so that:
     * GCD( E, (P-1)*(Q-1) ) == 1
     */
    MBEDTLS_MPI_CHK( mbedtls_mpi_lset( &ctx->E, exponent ) );

    do
    {
        MBEDTLS_MPI_CHK( mbedtls_mpi_gen_prime( &ctx->P, nbits >> 1, 0,
                                f_rng, p_rng ) );

        MBEDTLS_MPI_CHK( mbedtls_mpi_gen_prime( &ctx->Q, nbits >> 1, 0,
                                f_rng, p_rng ) );

        if( mbedtls_mpi_cmp_mpi( &ctx->P, &ctx->Q ) == 0 )
            continue;

        MBEDTLS_MPI_CHK( mbedtls_mpi_mul_mpi( &ctx->N, &ctx->P, &ctx->Q ) );
        if( mbedtls_mpi_bitlen( &ctx->N ) != nbits )
            continue;

        if( mbedtls_mpi_cmp_mpi( &ctx->P, &ctx->Q ) < 0 )
                                mbedtls_mpi_swap( &ctx->P, &ctx->Q );

        MBEDTLS_MPI_CHK( mbedtls_mpi_sub_int( &P1, &ctx->P, 1 ) );
        MBEDTLS_MPI_CHK( mbedtls_mpi_sub_int( &Q1, &ctx->Q, 1 ) );
        MBEDTLS_MPI_CHK( mbedtls_mpi_mul_mpi( &H, &P1, &Q1 ) );
        MBEDTLS_MPI_CHK( mbedtls_mpi_gcd( &G, &ctx->E, &H  ) );
    }
    while( mbedtls_mpi_cmp_int( &G, 1 ) != 0 );

    /*
     * D  = E^-1 mod ((P-1)*(Q-1))
     * DP = D mod (P - 1)
     * DQ = D mod (Q - 1)
     * QP = Q^-1 mod P
     */
    MBEDTLS_MPI_CHK( mbedtls_mpi_inv_mod( &ctx->D , &ctx->E, &H  ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_mod_mpi( &ctx->DP, &ctx->D, &P1 ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_mod_mpi( &ctx->DQ, &ctx->D, &Q1 ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_inv_mod( &ctx->QP, &ctx->Q, &ctx->P ) );

    ctx->len = ( mbedtls_mpi_bitlen( &ctx->N ) + 7 ) >> 3;

cleanup:

    mbedtls_mpi_free( &P1 ); mbedtls_mpi_free( &Q1 ); mbedtls_mpi_free( &H ); mbedtls_mpi_free( &G );

    if( ret != 0 )
    {
        mbedtls_rsa_free( ctx );
        return( MBEDTLS_ERR_RSA_KEY_GEN_FAILED + ret );
    }

    return( 0 );
}