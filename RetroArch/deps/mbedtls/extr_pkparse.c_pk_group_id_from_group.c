#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ mbedtls_ecp_group_id ;
struct TYPE_7__ {int /*<<< orphan*/  Y; int /*<<< orphan*/  Z; int /*<<< orphan*/  X; } ;
struct TYPE_8__ {scalar_t__ pbits; scalar_t__ nbits; TYPE_1__ G; int /*<<< orphan*/  N; int /*<<< orphan*/  B; int /*<<< orphan*/  A; int /*<<< orphan*/  P; } ;
typedef  TYPE_2__ mbedtls_ecp_group ;

/* Variables and functions */
 scalar_t__ const MBEDTLS_ECP_DP_NONE ; 
 int MBEDTLS_ERR_ECP_FEATURE_UNAVAILABLE ; 
 int /*<<< orphan*/  MBEDTLS_MPI_CHK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_ecp_group_free (TYPE_2__*) ; 
 int /*<<< orphan*/  mbedtls_ecp_group_init (TYPE_2__*) ; 
 int /*<<< orphan*/  mbedtls_ecp_group_load (TYPE_2__*,scalar_t__ const) ; 
 scalar_t__* mbedtls_ecp_grp_id_list () ; 
 scalar_t__ mbedtls_mpi_cmp_mpi (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ mbedtls_mpi_get_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pk_group_id_from_group( const mbedtls_ecp_group *grp, mbedtls_ecp_group_id *grp_id )
{
    int ret = 0;
    mbedtls_ecp_group ref;
    const mbedtls_ecp_group_id *id;

    mbedtls_ecp_group_init( &ref );

    for( id = mbedtls_ecp_grp_id_list(); *id != MBEDTLS_ECP_DP_NONE; id++ )
    {
        /* Load the group associated to that id */
        mbedtls_ecp_group_free( &ref );
        MBEDTLS_MPI_CHK( mbedtls_ecp_group_load( &ref, *id ) );

        /* Compare to the group we were given, starting with easy tests */
        if( grp->pbits == ref.pbits && grp->nbits == ref.nbits &&
            mbedtls_mpi_cmp_mpi( &grp->P, &ref.P ) == 0 &&
            mbedtls_mpi_cmp_mpi( &grp->A, &ref.A ) == 0 &&
            mbedtls_mpi_cmp_mpi( &grp->B, &ref.B ) == 0 &&
            mbedtls_mpi_cmp_mpi( &grp->N, &ref.N ) == 0 &&
            mbedtls_mpi_cmp_mpi( &grp->G.X, &ref.G.X ) == 0 &&
            mbedtls_mpi_cmp_mpi( &grp->G.Z, &ref.G.Z ) == 0 &&
            /* For Y we may only know the parity bit, so compare only that */
            mbedtls_mpi_get_bit( &grp->G.Y, 0 ) == mbedtls_mpi_get_bit( &ref.G.Y, 0 ) )
        {
            break;
        }

    }

cleanup:
    mbedtls_ecp_group_free( &ref );

    *grp_id = *id;

    if( ret == 0 && *id == MBEDTLS_ECP_DP_NONE )
        ret = MBEDTLS_ERR_ECP_FEATURE_UNAVAILABLE;

    return( ret );
}