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
struct TYPE_8__ {int /*<<< orphan*/  Z; int /*<<< orphan*/  X; } ;
typedef  TYPE_1__ mbedtls_ecp_point ;
struct TYPE_9__ {int /*<<< orphan*/  P; } ;
typedef  TYPE_2__ mbedtls_ecp_group ;

/* Variables and functions */
 int /*<<< orphan*/  MBEDTLS_MPI_CHK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MOD_MUL (int /*<<< orphan*/ ) ; 
 scalar_t__ mbedtls_internal_ecp_grp_capable (TYPE_2__ const*) ; 
 int mbedtls_internal_ecp_normalize_mxz (TYPE_2__ const*,TYPE_1__*) ; 
 int /*<<< orphan*/  mbedtls_mpi_inv_mod (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_mpi_lset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mbedtls_mpi_mul_mpi (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ecp_normalize_mxz( const mbedtls_ecp_group *grp, mbedtls_ecp_point *P )
{
    int ret;

#if defined(MBEDTLS_ECP_NORMALIZE_MXZ_ALT)
    if ( mbedtls_internal_ecp_grp_capable( grp ) )
    {
        return mbedtls_internal_ecp_normalize_mxz( grp, P );
    }
#endif /* MBEDTLS_ECP_NORMALIZE_MXZ_ALT */

    MBEDTLS_MPI_CHK( mbedtls_mpi_inv_mod( &P->Z, &P->Z, &grp->P ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_mul_mpi( &P->X, &P->X, &P->Z ) ); MOD_MUL( P->X );
    MBEDTLS_MPI_CHK( mbedtls_mpi_lset( &P->Z, 1 ) );

cleanup:
    return( ret );
}