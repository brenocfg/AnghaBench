#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  mbedtls_mpi ;
typedef  int /*<<< orphan*/  mbedtls_ecp_point ;
typedef  int /*<<< orphan*/  mbedtls_ecp_group ;

/* Variables and functions */
 scalar_t__ ECP_TYPE_SHORT_WEIERSTRASS ; 
 int MBEDTLS_ERR_ECP_FEATURE_UNAVAILABLE ; 
 int /*<<< orphan*/  MBEDTLS_MPI_CHK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecp_add_mixed (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ecp_get_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecp_normalize_jac (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_ecp_mul_shortcuts (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  mbedtls_ecp_point_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_ecp_point_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_internal_ecp_free (int /*<<< orphan*/ *) ; 
 char mbedtls_internal_ecp_grp_capable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_internal_ecp_init (int /*<<< orphan*/ *) ; 

int mbedtls_ecp_muladd( mbedtls_ecp_group *grp, mbedtls_ecp_point *R,
             const mbedtls_mpi *m, const mbedtls_ecp_point *P,
             const mbedtls_mpi *n, const mbedtls_ecp_point *Q )
{
    int ret;
    mbedtls_ecp_point mP;
#if defined(MBEDTLS_ECP_INTERNAL_ALT)
    char is_grp_capable = 0;
#endif

    if( ecp_get_type( grp ) != ECP_TYPE_SHORT_WEIERSTRASS )
        return( MBEDTLS_ERR_ECP_FEATURE_UNAVAILABLE );

    mbedtls_ecp_point_init( &mP );

    MBEDTLS_MPI_CHK( mbedtls_ecp_mul_shortcuts( grp, &mP, m, P ) );
    MBEDTLS_MPI_CHK( mbedtls_ecp_mul_shortcuts( grp, R,   n, Q ) );

#if defined(MBEDTLS_ECP_INTERNAL_ALT)
    if (  is_grp_capable = mbedtls_internal_ecp_grp_capable( grp )  )
    {
        MBEDTLS_MPI_CHK( mbedtls_internal_ecp_init( grp ) );
    }

#endif /* MBEDTLS_ECP_INTERNAL_ALT */
    MBEDTLS_MPI_CHK( ecp_add_mixed( grp, R, &mP, R ) );
    MBEDTLS_MPI_CHK( ecp_normalize_jac( grp, R ) );

cleanup:

#if defined(MBEDTLS_ECP_INTERNAL_ALT)
    if ( is_grp_capable )
    {
        mbedtls_internal_ecp_free( grp );
    }

#endif /* MBEDTLS_ECP_INTERNAL_ALT */
    mbedtls_ecp_point_free( &mP );

    return( ret );
}