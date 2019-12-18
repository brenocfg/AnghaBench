#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  Z; } ;
typedef  TYPE_1__ mbedtls_ecp_point ;
typedef  int /*<<< orphan*/  mbedtls_ecp_group ;

/* Variables and functions */
 int /*<<< orphan*/  MBEDTLS_MPI_CHK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecp_add_mixed (int /*<<< orphan*/  const*,TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  ecp_double_jac (int /*<<< orphan*/  const*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  ecp_randomize_jac (int /*<<< orphan*/  const*,TYPE_1__*,int (*) (void*,unsigned char*,size_t),void*) ; 
 int /*<<< orphan*/  ecp_select_comb (int /*<<< orphan*/  const*,TYPE_1__*,TYPE_1__ const*,unsigned char,unsigned char const) ; 
 int /*<<< orphan*/  mbedtls_ecp_point_free (TYPE_1__*) ; 
 int /*<<< orphan*/  mbedtls_ecp_point_init (TYPE_1__*) ; 
 int /*<<< orphan*/  mbedtls_mpi_lset (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ecp_mul_comb_core( const mbedtls_ecp_group *grp, mbedtls_ecp_point *R,
                              const mbedtls_ecp_point T[], unsigned char t_len,
                              const unsigned char x[], size_t d,
                              int (*f_rng)(void *, unsigned char *, size_t),
                              void *p_rng )
{
    int ret;
    mbedtls_ecp_point Txi;
    size_t i;

    mbedtls_ecp_point_init( &Txi );

    /* Start with a non-zero point and randomize its coordinates */
    i = d;
    MBEDTLS_MPI_CHK( ecp_select_comb( grp, R, T, t_len, x[i] ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_lset( &R->Z, 1 ) );
    if( f_rng != 0 )
        MBEDTLS_MPI_CHK( ecp_randomize_jac( grp, R, f_rng, p_rng ) );

    while( i-- != 0 )
    {
        MBEDTLS_MPI_CHK( ecp_double_jac( grp, R, R ) );
        MBEDTLS_MPI_CHK( ecp_select_comb( grp, &Txi, T, t_len, x[i] ) );
        MBEDTLS_MPI_CHK( ecp_add_mixed( grp, R, R, &Txi ) );
    }

cleanup:

    mbedtls_ecp_point_free( &Txi );

    return( ret );
}