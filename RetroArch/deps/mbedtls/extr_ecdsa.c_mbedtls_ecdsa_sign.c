#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  const mbedtls_mpi ;
struct TYPE_12__ {int /*<<< orphan*/  const X; } ;
typedef  TYPE_1__ mbedtls_ecp_point ;
struct TYPE_14__ {int /*<<< orphan*/ * p; } ;
struct TYPE_13__ {int nbits; TYPE_3__ N; } ;
typedef  TYPE_2__ mbedtls_ecp_group ;

/* Variables and functions */
 int MBEDTLS_ERR_ECP_BAD_INPUT_DATA ; 
 int MBEDTLS_ERR_ECP_RANDOM_FAILED ; 
 int /*<<< orphan*/  MBEDTLS_MPI_CHK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  derive_mpi (TYPE_2__*,int /*<<< orphan*/  const*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  mbedtls_ecp_gen_keypair (TYPE_2__*,int /*<<< orphan*/  const*,TYPE_1__*,int (*) (void*,unsigned char*,size_t),void*) ; 
 int /*<<< orphan*/  mbedtls_ecp_point_free (TYPE_1__*) ; 
 int /*<<< orphan*/  mbedtls_ecp_point_init (TYPE_1__*) ; 
 int /*<<< orphan*/  mbedtls_mpi_add_mpi (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 scalar_t__ mbedtls_mpi_cmp_int (int /*<<< orphan*/  const*,int) ; 
 scalar_t__ mbedtls_mpi_cmp_mpi (int /*<<< orphan*/  const*,TYPE_3__*) ; 
 int /*<<< orphan*/  mbedtls_mpi_fill_random (int /*<<< orphan*/  const*,size_t,int (*) (void*,unsigned char*,size_t),void*) ; 
 int /*<<< orphan*/  mbedtls_mpi_free (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  mbedtls_mpi_init (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  mbedtls_mpi_inv_mod (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,TYPE_3__*) ; 
 int /*<<< orphan*/  mbedtls_mpi_mod_mpi (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,TYPE_3__*) ; 
 int /*<<< orphan*/  mbedtls_mpi_mul_mpi (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  mbedtls_mpi_shift_r (int /*<<< orphan*/  const*,int) ; 

int mbedtls_ecdsa_sign( mbedtls_ecp_group *grp, mbedtls_mpi *r, mbedtls_mpi *s,
                const mbedtls_mpi *d, const unsigned char *buf, size_t blen,
                int (*f_rng)(void *, unsigned char *, size_t), void *p_rng )
{
    int ret, key_tries, sign_tries, blind_tries;
    mbedtls_ecp_point R;
    mbedtls_mpi k, e, t;

    /* Fail cleanly on curves such as Curve25519 that can't be used for ECDSA */
    if( grp->N.p == NULL )
        return( MBEDTLS_ERR_ECP_BAD_INPUT_DATA );

    mbedtls_ecp_point_init( &R );
    mbedtls_mpi_init( &k ); mbedtls_mpi_init( &e ); mbedtls_mpi_init( &t );

    sign_tries = 0;
    do
    {
        /*
         * Steps 1-3: generate a suitable ephemeral keypair
         * and set r = xR mod n
         */
        key_tries = 0;
        do
        {
            MBEDTLS_MPI_CHK( mbedtls_ecp_gen_keypair( grp, &k, &R, f_rng, p_rng ) );
            MBEDTLS_MPI_CHK( mbedtls_mpi_mod_mpi( r, &R.X, &grp->N ) );

            if( key_tries++ > 10 )
            {
                ret = MBEDTLS_ERR_ECP_RANDOM_FAILED;
                goto cleanup;
            }
        }
        while( mbedtls_mpi_cmp_int( r, 0 ) == 0 );

        /*
         * Step 5: derive MPI from hashed message
         */
        MBEDTLS_MPI_CHK( derive_mpi( grp, &e, buf, blen ) );

        /*
         * Generate a random value to blind inv_mod in next step,
         * avoiding a potential timing leak.
         */
        blind_tries = 0;
        do
        {
            size_t n_size = ( grp->nbits + 7 ) / 8;
            MBEDTLS_MPI_CHK( mbedtls_mpi_fill_random( &t, n_size, f_rng, p_rng ) );
            MBEDTLS_MPI_CHK( mbedtls_mpi_shift_r( &t, 8 * n_size - grp->nbits ) );

            /* See mbedtls_ecp_gen_keypair() */
            if( ++blind_tries > 30 )
                return( MBEDTLS_ERR_ECP_RANDOM_FAILED );
        }
        while( mbedtls_mpi_cmp_int( &t, 1 ) < 0 ||
               mbedtls_mpi_cmp_mpi( &t, &grp->N ) >= 0 );

        /*
         * Step 6: compute s = (e + r * d) / k = t (e + rd) / (kt) mod n
         */
        MBEDTLS_MPI_CHK( mbedtls_mpi_mul_mpi( s, r, d ) );
        MBEDTLS_MPI_CHK( mbedtls_mpi_add_mpi( &e, &e, s ) );
        MBEDTLS_MPI_CHK( mbedtls_mpi_mul_mpi( &e, &e, &t ) );
        MBEDTLS_MPI_CHK( mbedtls_mpi_mul_mpi( &k, &k, &t ) );
        MBEDTLS_MPI_CHK( mbedtls_mpi_inv_mod( s, &k, &grp->N ) );
        MBEDTLS_MPI_CHK( mbedtls_mpi_mul_mpi( s, s, &e ) );
        MBEDTLS_MPI_CHK( mbedtls_mpi_mod_mpi( s, s, &grp->N ) );

        if( sign_tries++ > 10 )
        {
            ret = MBEDTLS_ERR_ECP_RANDOM_FAILED;
            goto cleanup;
        }
    }
    while( mbedtls_mpi_cmp_int( s, 0 ) == 0 );

cleanup:
    mbedtls_ecp_point_free( &R );
    mbedtls_mpi_free( &k ); mbedtls_mpi_free( &e ); mbedtls_mpi_free( &t );

    return( ret );
}