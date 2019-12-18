#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_2__ ;
typedef  struct TYPE_30__   TYPE_1__ ;

/* Type definitions */
struct TYPE_31__ {int /*<<< orphan*/ * p; } ;
struct TYPE_30__ {size_t len; int /*<<< orphan*/  mutex; TYPE_2__ N; TYPE_2__ Vf; TYPE_2__ Q; TYPE_2__ P; TYPE_2__ QP; int /*<<< orphan*/  RQ; int /*<<< orphan*/  RP; int /*<<< orphan*/  RN; TYPE_2__ DQ; TYPE_2__ DP; TYPE_2__ D; TYPE_2__ Vi; } ;
typedef  TYPE_1__ mbedtls_rsa_context ;
typedef  TYPE_2__ mbedtls_mpi ;

/* Variables and functions */
 int MBEDTLS_ERR_MPI_BAD_INPUT_DATA ; 
 int MBEDTLS_ERR_RSA_BAD_INPUT_DATA ; 
 int MBEDTLS_ERR_RSA_PRIVATE_FAILED ; 
 int MBEDTLS_ERR_THREADING_MUTEX_ERROR ; 
 int /*<<< orphan*/  MBEDTLS_MPI_CHK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RSA_EXPONENT_BLINDING ; 
 int /*<<< orphan*/  mbedtls_mpi_add_mpi (TYPE_2__*,TYPE_2__*,TYPE_2__*) ; 
 scalar_t__ mbedtls_mpi_cmp_mpi (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  mbedtls_mpi_exp_mod (TYPE_2__*,TYPE_2__*,TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_mpi_fill_random (TYPE_2__*,int /*<<< orphan*/ ,int (*) (void*,unsigned char*,size_t),void*) ; 
 int /*<<< orphan*/  mbedtls_mpi_free (TYPE_2__*) ; 
 int /*<<< orphan*/  mbedtls_mpi_init (TYPE_2__*) ; 
 int /*<<< orphan*/  mbedtls_mpi_mod_mpi (TYPE_2__*,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  mbedtls_mpi_mul_mpi (TYPE_2__*,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  mbedtls_mpi_read_binary (TYPE_2__*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  mbedtls_mpi_sub_int (TYPE_2__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  mbedtls_mpi_sub_mpi (TYPE_2__*,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  mbedtls_mpi_write_binary (TYPE_2__*,unsigned char*,size_t) ; 
 int mbedtls_mutex_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ mbedtls_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rsa_prepare_blinding (TYPE_1__*,int (*) (void*,unsigned char*,size_t),void*) ; 

int mbedtls_rsa_private( mbedtls_rsa_context *ctx,
                 int (*f_rng)(void *, unsigned char *, size_t),
                 void *p_rng,
                 const unsigned char *input,
                 unsigned char *output )
{
    int ret;
    size_t olen;
    mbedtls_mpi T, T1, T2;
    mbedtls_mpi P1, Q1, R;
#if defined(MBEDTLS_RSA_NO_CRT)
    mbedtls_mpi D_blind;
    mbedtls_mpi *D = &ctx->D;
#else
    mbedtls_mpi DP_blind, DQ_blind;
    mbedtls_mpi *DP = &ctx->DP;
    mbedtls_mpi *DQ = &ctx->DQ;
#endif

    /* Make sure we have private key info, prevent possible misuse */
    if( ctx->P.p == NULL || ctx->Q.p == NULL || ctx->D.p == NULL )
        return( MBEDTLS_ERR_RSA_BAD_INPUT_DATA );

    mbedtls_mpi_init( &T ); mbedtls_mpi_init( &T1 ); mbedtls_mpi_init( &T2 );
    mbedtls_mpi_init( &P1 ); mbedtls_mpi_init( &Q1 ); mbedtls_mpi_init( &R );


    if( f_rng != NULL )
    {
#if defined(MBEDTLS_RSA_NO_CRT)
        mbedtls_mpi_init( &D_blind );
#else
        mbedtls_mpi_init( &DP_blind );
        mbedtls_mpi_init( &DQ_blind );
#endif
    }


#if defined(MBEDTLS_THREADING_C)
    if( ( ret = mbedtls_mutex_lock( &ctx->mutex ) ) != 0 )
        return( ret );
#endif

    MBEDTLS_MPI_CHK( mbedtls_mpi_read_binary( &T, input, ctx->len ) );
    if( mbedtls_mpi_cmp_mpi( &T, &ctx->N ) >= 0 )
    {
        ret = MBEDTLS_ERR_MPI_BAD_INPUT_DATA;
        goto cleanup;
    }

    if( f_rng != NULL )
    {
        /*
         * Blinding
         * T = T * Vi mod N
         */
        MBEDTLS_MPI_CHK( rsa_prepare_blinding( ctx, f_rng, p_rng ) );
        MBEDTLS_MPI_CHK( mbedtls_mpi_mul_mpi( &T, &T, &ctx->Vi ) );
        MBEDTLS_MPI_CHK( mbedtls_mpi_mod_mpi( &T, &T, &ctx->N ) );

        /*
         * Exponent blinding
         */
        MBEDTLS_MPI_CHK( mbedtls_mpi_sub_int( &P1, &ctx->P, 1 ) );
        MBEDTLS_MPI_CHK( mbedtls_mpi_sub_int( &Q1, &ctx->Q, 1 ) );

#if defined(MBEDTLS_RSA_NO_CRT)
        /*
         * D_blind = ( P - 1 ) * ( Q - 1 ) * R + D
         */
        MBEDTLS_MPI_CHK( mbedtls_mpi_fill_random( &R, RSA_EXPONENT_BLINDING,
                         f_rng, p_rng ) );
        MBEDTLS_MPI_CHK( mbedtls_mpi_mul_mpi( &D_blind, &P1, &Q1 ) );
        MBEDTLS_MPI_CHK( mbedtls_mpi_mul_mpi( &D_blind, &D_blind, &R ) );
        MBEDTLS_MPI_CHK( mbedtls_mpi_add_mpi( &D_blind, &D_blind, &ctx->D ) );

        D = &D_blind;
#else
        /*
         * DP_blind = ( P - 1 ) * R + DP
         */
        MBEDTLS_MPI_CHK( mbedtls_mpi_fill_random( &R, RSA_EXPONENT_BLINDING,
                         f_rng, p_rng ) );
        MBEDTLS_MPI_CHK( mbedtls_mpi_mul_mpi( &DP_blind, &P1, &R ) );
        MBEDTLS_MPI_CHK( mbedtls_mpi_add_mpi( &DP_blind, &DP_blind,
                    &ctx->DP ) );

        DP = &DP_blind;

        /*
         * DQ_blind = ( Q - 1 ) * R + DQ
         */
        MBEDTLS_MPI_CHK( mbedtls_mpi_fill_random( &R, RSA_EXPONENT_BLINDING,
                         f_rng, p_rng ) );
        MBEDTLS_MPI_CHK( mbedtls_mpi_mul_mpi( &DQ_blind, &Q1, &R ) );
        MBEDTLS_MPI_CHK( mbedtls_mpi_add_mpi( &DQ_blind, &DQ_blind,
                    &ctx->DQ ) );

        DQ = &DQ_blind;
#endif /* MBEDTLS_RSA_NO_CRT */
    }

#if defined(MBEDTLS_RSA_NO_CRT)
    MBEDTLS_MPI_CHK( mbedtls_mpi_exp_mod( &T, &T, D, &ctx->N, &ctx->RN ) );
#else
    /*
     * Faster decryption using the CRT
     *
     * T1 = input ^ dP mod P
     * T2 = input ^ dQ mod Q
     */
    MBEDTLS_MPI_CHK( mbedtls_mpi_exp_mod( &T1, &T, DP, &ctx->P, &ctx->RP ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_exp_mod( &T2, &T, DQ, &ctx->Q, &ctx->RQ ) );

    /*
     * T = (T1 - T2) * (Q^-1 mod P) mod P
     */
    MBEDTLS_MPI_CHK( mbedtls_mpi_sub_mpi( &T, &T1, &T2 ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_mul_mpi( &T1, &T, &ctx->QP ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_mod_mpi( &T, &T1, &ctx->P ) );

    /*
     * T = T2 + T * Q
     */
    MBEDTLS_MPI_CHK( mbedtls_mpi_mul_mpi( &T1, &T, &ctx->Q ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_add_mpi( &T, &T2, &T1 ) );
#endif /* MBEDTLS_RSA_NO_CRT */

    if( f_rng != NULL )
    {
        /*
         * Unblind
         * T = T * Vf mod N
         */
        MBEDTLS_MPI_CHK( mbedtls_mpi_mul_mpi( &T, &T, &ctx->Vf ) );
        MBEDTLS_MPI_CHK( mbedtls_mpi_mod_mpi( &T, &T, &ctx->N ) );
    }

    olen = ctx->len;
    MBEDTLS_MPI_CHK( mbedtls_mpi_write_binary( &T, output, olen ) );

cleanup:
#if defined(MBEDTLS_THREADING_C)
    if( mbedtls_mutex_unlock( &ctx->mutex ) != 0 )
        return( MBEDTLS_ERR_THREADING_MUTEX_ERROR );
#endif

    mbedtls_mpi_free( &T ); mbedtls_mpi_free( &T1 ); mbedtls_mpi_free( &T2 );
    mbedtls_mpi_free( &P1 ); mbedtls_mpi_free( &Q1 ); mbedtls_mpi_free( &R );

    if( f_rng != NULL )
    {
#if defined(MBEDTLS_RSA_NO_CRT)
        mbedtls_mpi_free( &D_blind );
#else
        mbedtls_mpi_free( &DP_blind );
        mbedtls_mpi_free( &DQ_blind );
#endif
    }

    if( ret != 0 )
        return( MBEDTLS_ERR_RSA_PRIVATE_FAILED + ret );

    return( 0 );
}