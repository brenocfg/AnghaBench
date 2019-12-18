#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_1__ ;

/* Type definitions */
struct TYPE_26__ {int* p; } ;
typedef  TYPE_1__ const mbedtls_mpi ;

/* Variables and functions */
 int MBEDTLS_ERR_MPI_BAD_INPUT_DATA ; 
 int MBEDTLS_ERR_MPI_NOT_ACCEPTABLE ; 
 int /*<<< orphan*/  MBEDTLS_MPI_CHK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_mpi_add_mpi (TYPE_1__ const*,TYPE_1__ const*,TYPE_1__ const*) ; 
 scalar_t__ mbedtls_mpi_cmp_int (TYPE_1__ const*,int) ; 
 scalar_t__ mbedtls_mpi_cmp_mpi (TYPE_1__ const*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  mbedtls_mpi_copy (TYPE_1__ const*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  mbedtls_mpi_free (TYPE_1__ const*) ; 
 int /*<<< orphan*/  mbedtls_mpi_gcd (TYPE_1__ const*,TYPE_1__ const*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  mbedtls_mpi_init (TYPE_1__ const*) ; 
 int /*<<< orphan*/  mbedtls_mpi_lset (TYPE_1__ const*,int) ; 
 int /*<<< orphan*/  mbedtls_mpi_mod_mpi (TYPE_1__ const*,TYPE_1__ const*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  mbedtls_mpi_shift_r (TYPE_1__ const*,int) ; 
 int /*<<< orphan*/  mbedtls_mpi_sub_mpi (TYPE_1__ const*,TYPE_1__ const*,TYPE_1__ const*) ; 

int mbedtls_mpi_inv_mod( mbedtls_mpi *X, const mbedtls_mpi *A, const mbedtls_mpi *N )
{
    int ret;
    mbedtls_mpi G, TA, TU, U1, U2, TB, TV, V1, V2;

    if( mbedtls_mpi_cmp_int( N, 1 ) <= 0 )
        return( MBEDTLS_ERR_MPI_BAD_INPUT_DATA );

    mbedtls_mpi_init( &TA ); mbedtls_mpi_init( &TU ); mbedtls_mpi_init( &U1 ); mbedtls_mpi_init( &U2 );
    mbedtls_mpi_init( &G ); mbedtls_mpi_init( &TB ); mbedtls_mpi_init( &TV );
    mbedtls_mpi_init( &V1 ); mbedtls_mpi_init( &V2 );

    MBEDTLS_MPI_CHK( mbedtls_mpi_gcd( &G, A, N ) );

    if( mbedtls_mpi_cmp_int( &G, 1 ) != 0 )
    {
        ret = MBEDTLS_ERR_MPI_NOT_ACCEPTABLE;
        goto cleanup;
    }

    MBEDTLS_MPI_CHK( mbedtls_mpi_mod_mpi( &TA, A, N ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_copy( &TU, &TA ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_copy( &TB, N ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_copy( &TV, N ) );

    MBEDTLS_MPI_CHK( mbedtls_mpi_lset( &U1, 1 ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_lset( &U2, 0 ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_lset( &V1, 0 ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_lset( &V2, 1 ) );

    do
    {
        while( ( TU.p[0] & 1 ) == 0 )
        {
            MBEDTLS_MPI_CHK( mbedtls_mpi_shift_r( &TU, 1 ) );

            if( ( U1.p[0] & 1 ) != 0 || ( U2.p[0] & 1 ) != 0 )
            {
                MBEDTLS_MPI_CHK( mbedtls_mpi_add_mpi( &U1, &U1, &TB ) );
                MBEDTLS_MPI_CHK( mbedtls_mpi_sub_mpi( &U2, &U2, &TA ) );
            }

            MBEDTLS_MPI_CHK( mbedtls_mpi_shift_r( &U1, 1 ) );
            MBEDTLS_MPI_CHK( mbedtls_mpi_shift_r( &U2, 1 ) );
        }

        while( ( TV.p[0] & 1 ) == 0 )
        {
            MBEDTLS_MPI_CHK( mbedtls_mpi_shift_r( &TV, 1 ) );

            if( ( V1.p[0] & 1 ) != 0 || ( V2.p[0] & 1 ) != 0 )
            {
                MBEDTLS_MPI_CHK( mbedtls_mpi_add_mpi( &V1, &V1, &TB ) );
                MBEDTLS_MPI_CHK( mbedtls_mpi_sub_mpi( &V2, &V2, &TA ) );
            }

            MBEDTLS_MPI_CHK( mbedtls_mpi_shift_r( &V1, 1 ) );
            MBEDTLS_MPI_CHK( mbedtls_mpi_shift_r( &V2, 1 ) );
        }

        if( mbedtls_mpi_cmp_mpi( &TU, &TV ) >= 0 )
        {
            MBEDTLS_MPI_CHK( mbedtls_mpi_sub_mpi( &TU, &TU, &TV ) );
            MBEDTLS_MPI_CHK( mbedtls_mpi_sub_mpi( &U1, &U1, &V1 ) );
            MBEDTLS_MPI_CHK( mbedtls_mpi_sub_mpi( &U2, &U2, &V2 ) );
        }
        else
        {
            MBEDTLS_MPI_CHK( mbedtls_mpi_sub_mpi( &TV, &TV, &TU ) );
            MBEDTLS_MPI_CHK( mbedtls_mpi_sub_mpi( &V1, &V1, &U1 ) );
            MBEDTLS_MPI_CHK( mbedtls_mpi_sub_mpi( &V2, &V2, &U2 ) );
        }
    }
    while( mbedtls_mpi_cmp_int( &TU, 0 ) != 0 );

    while( mbedtls_mpi_cmp_int( &V1, 0 ) < 0 )
        MBEDTLS_MPI_CHK( mbedtls_mpi_add_mpi( &V1, &V1, N ) );

    while( mbedtls_mpi_cmp_mpi( &V1, N ) >= 0 )
        MBEDTLS_MPI_CHK( mbedtls_mpi_sub_mpi( &V1, &V1, N ) );

    MBEDTLS_MPI_CHK( mbedtls_mpi_copy( X, &V1 ) );

cleanup:

    mbedtls_mpi_free( &TA ); mbedtls_mpi_free( &TU ); mbedtls_mpi_free( &U1 ); mbedtls_mpi_free( &U2 );
    mbedtls_mpi_free( &G ); mbedtls_mpi_free( &TB ); mbedtls_mpi_free( &TV );
    mbedtls_mpi_free( &V1 ); mbedtls_mpi_free( &V2 );

    return( ret );
}