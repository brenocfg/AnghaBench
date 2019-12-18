#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mbedtls_mpi ;
struct TYPE_9__ {int /*<<< orphan*/  Z; } ;
typedef  TYPE_1__ mbedtls_ecp_point ;
typedef  int /*<<< orphan*/  mbedtls_ecp_group ;

/* Variables and functions */
 scalar_t__ ECP_TYPE_MONTGOMERY ; 
 scalar_t__ ECP_TYPE_SHORT_WEIERSTRASS ; 
 int MBEDTLS_ERR_ECP_BAD_INPUT_DATA ; 
 int /*<<< orphan*/  MBEDTLS_MPI_CHK (int /*<<< orphan*/ ) ; 
 scalar_t__ ecp_get_type (int /*<<< orphan*/ *) ; 
 int ecp_mul_comb (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/  const*,TYPE_1__ const*,int (*) (void*,unsigned char*,size_t),void*) ; 
 int ecp_mul_mxz (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/  const*,TYPE_1__ const*,int (*) (void*,unsigned char*,size_t),void*) ; 
 int mbedtls_ecp_check_privkey (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int mbedtls_ecp_check_pubkey (int /*<<< orphan*/ *,TYPE_1__ const*) ; 
 int /*<<< orphan*/  mbedtls_internal_ecp_free (int /*<<< orphan*/ *) ; 
 char mbedtls_internal_ecp_grp_capable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_internal_ecp_init (int /*<<< orphan*/ *) ; 
 scalar_t__ mbedtls_mpi_cmp_int (int /*<<< orphan*/ *,int) ; 

int mbedtls_ecp_mul( mbedtls_ecp_group *grp, mbedtls_ecp_point *R,
             const mbedtls_mpi *m, const mbedtls_ecp_point *P,
             int (*f_rng)(void *, unsigned char *, size_t), void *p_rng )
{
    int ret = MBEDTLS_ERR_ECP_BAD_INPUT_DATA;
#if defined(MBEDTLS_ECP_INTERNAL_ALT)
    char is_grp_capable = 0;
#endif

    /* Common sanity checks */
    if( mbedtls_mpi_cmp_int( &P->Z, 1 ) != 0 )
        return( MBEDTLS_ERR_ECP_BAD_INPUT_DATA );

    if( ( ret = mbedtls_ecp_check_privkey( grp, m ) ) != 0 ||
        ( ret = mbedtls_ecp_check_pubkey( grp, P ) ) != 0 )
        return( ret );

#if defined(MBEDTLS_ECP_INTERNAL_ALT)
    if ( is_grp_capable = mbedtls_internal_ecp_grp_capable( grp )  )
    {
        MBEDTLS_MPI_CHK( mbedtls_internal_ecp_init( grp ) );
    }

#endif /* MBEDTLS_ECP_INTERNAL_ALT */
#if defined(ECP_MONTGOMERY)
    if( ecp_get_type( grp ) == ECP_TYPE_MONTGOMERY )
        ret = ecp_mul_mxz( grp, R, m, P, f_rng, p_rng );

#endif
#if defined(ECP_SHORTWEIERSTRASS)
    if( ecp_get_type( grp ) == ECP_TYPE_SHORT_WEIERSTRASS )
        ret = ecp_mul_comb( grp, R, m, P, f_rng, p_rng );

#endif
#if defined(MBEDTLS_ECP_INTERNAL_ALT)
cleanup:

    if ( is_grp_capable )
    {
        mbedtls_internal_ecp_free( grp );
    }

#endif /* MBEDTLS_ECP_INTERNAL_ALT */
    return( ret );
}