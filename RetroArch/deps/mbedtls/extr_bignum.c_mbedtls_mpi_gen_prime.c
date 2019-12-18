#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int mbedtls_mpi_uint ;
struct TYPE_17__ {int* p; } ;
typedef  TYPE_1__ mbedtls_mpi ;

/* Variables and functions */
 size_t BITS_TO_LIMBS (size_t) ; 
 int MBEDTLS_ERR_MPI_BAD_INPUT_DATA ; 
 int MBEDTLS_ERR_MPI_NOT_ACCEPTABLE ; 
 int /*<<< orphan*/  MBEDTLS_MPI_CHK (int /*<<< orphan*/ ) ; 
 size_t MBEDTLS_MPI_MAX_BITS ; 
 size_t ciL ; 
 int /*<<< orphan*/  mbedtls_mpi_add_int (TYPE_1__*,TYPE_1__*,int) ; 
 size_t mbedtls_mpi_bitlen (TYPE_1__*) ; 
 int /*<<< orphan*/  mbedtls_mpi_copy (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  mbedtls_mpi_fill_random (TYPE_1__*,size_t,int (*) (void*,unsigned char*,size_t),void*) ; 
 int /*<<< orphan*/  mbedtls_mpi_free (TYPE_1__*) ; 
 int /*<<< orphan*/  mbedtls_mpi_init (TYPE_1__*) ; 
 int mbedtls_mpi_is_prime (TYPE_1__*,int (*) (void*,unsigned char*,size_t),void*) ; 
 int /*<<< orphan*/  mbedtls_mpi_mod_int (int*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  mbedtls_mpi_set_bit (TYPE_1__*,size_t,int) ; 
 int /*<<< orphan*/  mbedtls_mpi_shift_r (TYPE_1__*,int) ; 
 int mpi_check_small_factors (TYPE_1__*) ; 
 int mpi_miller_rabin (TYPE_1__*,int (*) (void*,unsigned char*,size_t),void*) ; 

int mbedtls_mpi_gen_prime( mbedtls_mpi *X, size_t nbits, int dh_flag,
                   int (*f_rng)(void *, unsigned char *, size_t),
                   void *p_rng )
{
    int ret;
    size_t k, n;
    mbedtls_mpi_uint r;
    mbedtls_mpi Y;

    if( nbits < 3 || nbits > MBEDTLS_MPI_MAX_BITS )
        return( MBEDTLS_ERR_MPI_BAD_INPUT_DATA );

    mbedtls_mpi_init( &Y );

    n = BITS_TO_LIMBS( nbits );

    MBEDTLS_MPI_CHK( mbedtls_mpi_fill_random( X, n * ciL, f_rng, p_rng ) );

    k = mbedtls_mpi_bitlen( X );
    if( k > nbits ) MBEDTLS_MPI_CHK( mbedtls_mpi_shift_r( X, k - nbits + 1 ) );

    mbedtls_mpi_set_bit( X, nbits-1, 1 );

    X->p[0] |= 1;

    if( dh_flag == 0 )
    {
        while( ( ret = mbedtls_mpi_is_prime( X, f_rng, p_rng ) ) != 0 )
        {
            if( ret != MBEDTLS_ERR_MPI_NOT_ACCEPTABLE )
                goto cleanup;

            MBEDTLS_MPI_CHK( mbedtls_mpi_add_int( X, X, 2 ) );
        }
    }
    else
    {
        /*
         * An necessary condition for Y and X = 2Y + 1 to be prime
         * is X = 2 mod 3 (which is equivalent to Y = 2 mod 3).
         * Make sure it is satisfied, while keeping X = 3 mod 4
         */

        X->p[0] |= 2;

        MBEDTLS_MPI_CHK( mbedtls_mpi_mod_int( &r, X, 3 ) );
        if( r == 0 )
            MBEDTLS_MPI_CHK( mbedtls_mpi_add_int( X, X, 8 ) );
        else if( r == 1 )
            MBEDTLS_MPI_CHK( mbedtls_mpi_add_int( X, X, 4 ) );

        /* Set Y = (X-1) / 2, which is X / 2 because X is odd */
        MBEDTLS_MPI_CHK( mbedtls_mpi_copy( &Y, X ) );
        MBEDTLS_MPI_CHK( mbedtls_mpi_shift_r( &Y, 1 ) );

        while( 1 )
        {
            /*
             * First, check small factors for X and Y
             * before doing Miller-Rabin on any of them
             */
            if( ( ret = mpi_check_small_factors(  X         ) ) == 0 &&
                ( ret = mpi_check_small_factors( &Y         ) ) == 0 &&
                ( ret = mpi_miller_rabin(  X, f_rng, p_rng  ) ) == 0 &&
                ( ret = mpi_miller_rabin( &Y, f_rng, p_rng  ) ) == 0 )
            {
                break;
            }

            if( ret != MBEDTLS_ERR_MPI_NOT_ACCEPTABLE )
                goto cleanup;

            /*
             * Next candidates. We want to preserve Y = (X-1) / 2 and
             * Y = 1 mod 2 and Y = 2 mod 3 (eq X = 3 mod 4 and X = 2 mod 3)
             * so up Y by 6 and X by 12.
             */
            MBEDTLS_MPI_CHK( mbedtls_mpi_add_int(  X,  X, 12 ) );
            MBEDTLS_MPI_CHK( mbedtls_mpi_add_int( &Y, &Y, 6  ) );
        }
    }

cleanup:

    mbedtls_mpi_free( &Y );

    return( ret );
}