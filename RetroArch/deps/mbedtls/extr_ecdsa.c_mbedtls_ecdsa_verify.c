#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_36__   TYPE_3__ ;
typedef  struct TYPE_35__   TYPE_2__ ;
typedef  struct TYPE_34__   TYPE_1__ ;

/* Type definitions */
struct TYPE_34__ {int /*<<< orphan*/ * p; } ;
typedef  TYPE_1__ const mbedtls_mpi ;
struct TYPE_35__ {TYPE_1__ const X; } ;
typedef  TYPE_2__ mbedtls_ecp_point ;
struct TYPE_36__ {TYPE_1__ const N; int /*<<< orphan*/  G; } ;
typedef  TYPE_3__ mbedtls_ecp_group ;

/* Variables and functions */
 int MBEDTLS_ERR_ECP_BAD_INPUT_DATA ; 
 int MBEDTLS_ERR_ECP_VERIFY_FAILED ; 
 int /*<<< orphan*/  MBEDTLS_MPI_CHK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  derive_mpi (TYPE_3__*,TYPE_1__ const*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  mbedtls_ecp_check_pubkey (TYPE_3__*,TYPE_2__ const*) ; 
 scalar_t__ mbedtls_ecp_is_zero (TYPE_2__*) ; 
 int /*<<< orphan*/  mbedtls_ecp_muladd (TYPE_3__*,TYPE_2__*,TYPE_1__ const*,int /*<<< orphan*/ *,TYPE_1__ const*,TYPE_2__ const*) ; 
 int /*<<< orphan*/  mbedtls_ecp_point_free (TYPE_2__*) ; 
 int /*<<< orphan*/  mbedtls_ecp_point_init (TYPE_2__*) ; 
 scalar_t__ mbedtls_mpi_cmp_int (TYPE_1__ const*,int) ; 
 scalar_t__ mbedtls_mpi_cmp_mpi (TYPE_1__ const*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  mbedtls_mpi_free (TYPE_1__ const*) ; 
 int /*<<< orphan*/  mbedtls_mpi_init (TYPE_1__ const*) ; 
 int /*<<< orphan*/  mbedtls_mpi_inv_mod (TYPE_1__ const*,TYPE_1__ const*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  mbedtls_mpi_mod_mpi (TYPE_1__ const*,TYPE_1__ const*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  mbedtls_mpi_mul_mpi (TYPE_1__ const*,TYPE_1__ const*,TYPE_1__ const*) ; 

int mbedtls_ecdsa_verify( mbedtls_ecp_group *grp,
                  const unsigned char *buf, size_t blen,
                  const mbedtls_ecp_point *Q, const mbedtls_mpi *r, const mbedtls_mpi *s)
{
    int ret;
    mbedtls_mpi e, s_inv, u1, u2;
    mbedtls_ecp_point R;

    mbedtls_ecp_point_init( &R );
    mbedtls_mpi_init( &e ); mbedtls_mpi_init( &s_inv ); mbedtls_mpi_init( &u1 ); mbedtls_mpi_init( &u2 );

    /* Fail cleanly on curves such as Curve25519 that can't be used for ECDSA */
    if( grp->N.p == NULL )
        return( MBEDTLS_ERR_ECP_BAD_INPUT_DATA );

    /*
     * Step 1: make sure r and s are in range 1..n-1
     */
    if( mbedtls_mpi_cmp_int( r, 1 ) < 0 || mbedtls_mpi_cmp_mpi( r, &grp->N ) >= 0 ||
        mbedtls_mpi_cmp_int( s, 1 ) < 0 || mbedtls_mpi_cmp_mpi( s, &grp->N ) >= 0 )
    {
        ret = MBEDTLS_ERR_ECP_VERIFY_FAILED;
        goto cleanup;
    }

    /*
     * Additional precaution: make sure Q is valid
     */
    MBEDTLS_MPI_CHK( mbedtls_ecp_check_pubkey( grp, Q ) );

    /*
     * Step 3: derive MPI from hashed message
     */
    MBEDTLS_MPI_CHK( derive_mpi( grp, &e, buf, blen ) );

    /*
     * Step 4: u1 = e / s mod n, u2 = r / s mod n
     */
    MBEDTLS_MPI_CHK( mbedtls_mpi_inv_mod( &s_inv, s, &grp->N ) );

    MBEDTLS_MPI_CHK( mbedtls_mpi_mul_mpi( &u1, &e, &s_inv ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_mod_mpi( &u1, &u1, &grp->N ) );

    MBEDTLS_MPI_CHK( mbedtls_mpi_mul_mpi( &u2, r, &s_inv ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_mod_mpi( &u2, &u2, &grp->N ) );

    /*
     * Step 5: R = u1 G + u2 Q
     *
     * Since we're not using any secret data, no need to pass a RNG to
     * mbedtls_ecp_mul() for countermesures.
     */
    MBEDTLS_MPI_CHK( mbedtls_ecp_muladd( grp, &R, &u1, &grp->G, &u2, Q ) );

    if( mbedtls_ecp_is_zero( &R ) )
    {
        ret = MBEDTLS_ERR_ECP_VERIFY_FAILED;
        goto cleanup;
    }

    /*
     * Step 6: convert xR to an integer (no-op)
     * Step 7: reduce xR mod n (gives v)
     */
    MBEDTLS_MPI_CHK( mbedtls_mpi_mod_mpi( &R.X, &R.X, &grp->N ) );

    /*
     * Step 8: check if v (that is, R.X) is equal to r
     */
    if( mbedtls_mpi_cmp_mpi( &R.X, r ) != 0 )
    {
        ret = MBEDTLS_ERR_ECP_VERIFY_FAILED;
        goto cleanup;
    }

cleanup:
    mbedtls_ecp_point_free( &R );
    mbedtls_mpi_free( &e ); mbedtls_mpi_free( &s_inv ); mbedtls_mpi_free( &u1 ); mbedtls_mpi_free( &u2 );

    return( ret );
}