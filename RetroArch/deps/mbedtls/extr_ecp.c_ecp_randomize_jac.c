#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mbedtls_mpi ;
struct TYPE_8__ {int /*<<< orphan*/  Y; int /*<<< orphan*/  X; int /*<<< orphan*/  Z; } ;
typedef  TYPE_1__ mbedtls_ecp_point ;
struct TYPE_9__ {int pbits; int /*<<< orphan*/  P; } ;
typedef  TYPE_2__ mbedtls_ecp_group ;

/* Variables and functions */
 int MBEDTLS_ERR_ECP_RANDOM_FAILED ; 
 int /*<<< orphan*/  MBEDTLS_MPI_CHK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MOD_MUL (int /*<<< orphan*/ ) ; 
 scalar_t__ mbedtls_internal_ecp_grp_capable (TYPE_2__ const*) ; 
 int mbedtls_internal_ecp_randomize_jac (TYPE_2__ const*,TYPE_1__*,int (*) (void*,unsigned char*,size_t),void*) ; 
 scalar_t__ mbedtls_mpi_cmp_int (int /*<<< orphan*/ *,int) ; 
 scalar_t__ mbedtls_mpi_cmp_mpi (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_mpi_fill_random (int /*<<< orphan*/ *,size_t,int (*) (void*,unsigned char*,size_t),void*) ; 
 int /*<<< orphan*/  mbedtls_mpi_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_mpi_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_mpi_mul_mpi (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_mpi_shift_r (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ecp_randomize_jac( const mbedtls_ecp_group *grp, mbedtls_ecp_point *pt,
                int (*f_rng)(void *, unsigned char *, size_t), void *p_rng )
{
    int ret;
    mbedtls_mpi l, ll;
    size_t p_size;
    int count = 0;

#if defined(MBEDTLS_ECP_RANDOMIZE_JAC_ALT)
    if ( mbedtls_internal_ecp_grp_capable( grp ) )
    {
        return mbedtls_internal_ecp_randomize_jac( grp, pt, f_rng, p_rng );
    }
#endif /* MBEDTLS_ECP_RANDOMIZE_JAC_ALT */

    p_size = ( grp->pbits + 7 ) / 8;
    mbedtls_mpi_init( &l ); mbedtls_mpi_init( &ll );

    /* Generate l such that 1 < l < p */
    do
    {
        MBEDTLS_MPI_CHK( mbedtls_mpi_fill_random( &l, p_size, f_rng, p_rng ) );

        while( mbedtls_mpi_cmp_mpi( &l, &grp->P ) >= 0 )
            MBEDTLS_MPI_CHK( mbedtls_mpi_shift_r( &l, 1 ) );

        if( count++ > 10 )
            return( MBEDTLS_ERR_ECP_RANDOM_FAILED );
    }
    while( mbedtls_mpi_cmp_int( &l, 1 ) <= 0 );

    /* Z = l * Z */
    MBEDTLS_MPI_CHK( mbedtls_mpi_mul_mpi( &pt->Z,   &pt->Z,     &l  ) ); MOD_MUL( pt->Z );

    /* X = l^2 * X */
    MBEDTLS_MPI_CHK( mbedtls_mpi_mul_mpi( &ll,      &l,         &l  ) ); MOD_MUL( ll );
    MBEDTLS_MPI_CHK( mbedtls_mpi_mul_mpi( &pt->X,   &pt->X,     &ll ) ); MOD_MUL( pt->X );

    /* Y = l^3 * Y */
    MBEDTLS_MPI_CHK( mbedtls_mpi_mul_mpi( &ll,      &ll,        &l  ) ); MOD_MUL( ll );
    MBEDTLS_MPI_CHK( mbedtls_mpi_mul_mpi( &pt->Y,   &pt->Y,     &ll ) ); MOD_MUL( pt->Y );

cleanup:
    mbedtls_mpi_free( &l ); mbedtls_mpi_free( &ll );

    return( ret );
}