#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  Z; int /*<<< orphan*/  Y; int /*<<< orphan*/  X; } ;
typedef  TYPE_2__ mbedtls_ecp_point ;
struct TYPE_10__ {int /*<<< orphan*/  Z; int /*<<< orphan*/  Y; int /*<<< orphan*/  X; } ;
struct TYPE_13__ {scalar_t__ id; int /*<<< orphan*/  G; } ;
struct TYPE_12__ {TYPE_1__ Q; TYPE_7__ grp; int /*<<< orphan*/  d; } ;
typedef  TYPE_3__ mbedtls_ecp_keypair ;
typedef  int /*<<< orphan*/  mbedtls_ecp_group ;

/* Variables and functions */
 scalar_t__ MBEDTLS_ECP_DP_NONE ; 
 int MBEDTLS_ERR_ECP_BAD_INPUT_DATA ; 
 int /*<<< orphan*/  MBEDTLS_MPI_CHK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_ecp_group_copy (int /*<<< orphan*/ *,TYPE_7__*) ; 
 int /*<<< orphan*/  mbedtls_ecp_group_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_ecp_group_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_ecp_mul (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_ecp_point_free (TYPE_2__*) ; 
 int /*<<< orphan*/  mbedtls_ecp_point_init (TYPE_2__*) ; 
 scalar_t__ mbedtls_mpi_cmp_mpi (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int mbedtls_ecp_check_pub_priv( const mbedtls_ecp_keypair *pub, const mbedtls_ecp_keypair *prv )
{
    int ret;
    mbedtls_ecp_point Q;
    mbedtls_ecp_group grp;

    if( pub->grp.id == MBEDTLS_ECP_DP_NONE ||
        pub->grp.id != prv->grp.id ||
        mbedtls_mpi_cmp_mpi( &pub->Q.X, &prv->Q.X ) ||
        mbedtls_mpi_cmp_mpi( &pub->Q.Y, &prv->Q.Y ) ||
        mbedtls_mpi_cmp_mpi( &pub->Q.Z, &prv->Q.Z ) )
    {
        return( MBEDTLS_ERR_ECP_BAD_INPUT_DATA );
    }

    mbedtls_ecp_point_init( &Q );
    mbedtls_ecp_group_init( &grp );

    /* mbedtls_ecp_mul() needs a non-const group... */
    mbedtls_ecp_group_copy( &grp, &prv->grp );

    /* Also checks d is valid */
    MBEDTLS_MPI_CHK( mbedtls_ecp_mul( &grp, &Q, &prv->d, &prv->grp.G, NULL, NULL ) );

    if( mbedtls_mpi_cmp_mpi( &Q.X, &prv->Q.X ) ||
        mbedtls_mpi_cmp_mpi( &Q.Y, &prv->Q.Y ) ||
        mbedtls_mpi_cmp_mpi( &Q.Z, &prv->Q.Z ) )
    {
        ret = MBEDTLS_ERR_ECP_BAD_INPUT_DATA;
        goto cleanup;
    }

cleanup:
    mbedtls_ecp_point_free( &Q );
    mbedtls_ecp_group_free( &grp );

    return( ret );
}