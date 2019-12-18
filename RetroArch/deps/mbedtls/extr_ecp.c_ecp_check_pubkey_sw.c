#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mbedtls_mpi ;
struct TYPE_6__ {int /*<<< orphan*/  X; int /*<<< orphan*/  Y; } ;
typedef  TYPE_1__ mbedtls_ecp_point ;
struct TYPE_8__ {int /*<<< orphan*/ * p; } ;
struct TYPE_7__ {TYPE_3__ B; TYPE_3__ A; int /*<<< orphan*/  P; } ;
typedef  TYPE_2__ mbedtls_ecp_group ;

/* Variables and functions */
 int MBEDTLS_ERR_ECP_INVALID_KEY ; 
 int /*<<< orphan*/  MBEDTLS_MPI_CHK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MOD_ADD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MOD_MUL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MOD_SUB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_mpi_add_mpi (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*) ; 
 scalar_t__ mbedtls_mpi_cmp_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ mbedtls_mpi_cmp_mpi (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_mpi_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_mpi_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_mpi_mul_mpi (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_mpi_sub_int (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ecp_check_pubkey_sw( const mbedtls_ecp_group *grp, const mbedtls_ecp_point *pt )
{
    int ret;
    mbedtls_mpi YY, RHS;

    /* pt coordinates must be normalized for our checks */
    if( mbedtls_mpi_cmp_int( &pt->X, 0 ) < 0 ||
        mbedtls_mpi_cmp_int( &pt->Y, 0 ) < 0 ||
        mbedtls_mpi_cmp_mpi( &pt->X, &grp->P ) >= 0 ||
        mbedtls_mpi_cmp_mpi( &pt->Y, &grp->P ) >= 0 )
        return( MBEDTLS_ERR_ECP_INVALID_KEY );

    mbedtls_mpi_init( &YY ); mbedtls_mpi_init( &RHS );

    /*
     * YY = Y^2
     * RHS = X (X^2 + A) + B = X^3 + A X + B
     */
    MBEDTLS_MPI_CHK( mbedtls_mpi_mul_mpi( &YY,  &pt->Y,   &pt->Y  ) );  MOD_MUL( YY  );
    MBEDTLS_MPI_CHK( mbedtls_mpi_mul_mpi( &RHS, &pt->X,   &pt->X  ) );  MOD_MUL( RHS );

    /* Special case for A = -3 */
    if( grp->A.p == NULL )
    {
        MBEDTLS_MPI_CHK( mbedtls_mpi_sub_int( &RHS, &RHS, 3       ) );  MOD_SUB( RHS );
    }
    else
    {
        MBEDTLS_MPI_CHK( mbedtls_mpi_add_mpi( &RHS, &RHS, &grp->A ) );  MOD_ADD( RHS );
    }

    MBEDTLS_MPI_CHK( mbedtls_mpi_mul_mpi( &RHS, &RHS,     &pt->X  ) );  MOD_MUL( RHS );
    MBEDTLS_MPI_CHK( mbedtls_mpi_add_mpi( &RHS, &RHS,     &grp->B ) );  MOD_ADD( RHS );

    if( mbedtls_mpi_cmp_mpi( &YY, &RHS ) != 0 )
        ret = MBEDTLS_ERR_ECP_INVALID_KEY;

cleanup:

    mbedtls_mpi_free( &YY ); mbedtls_mpi_free( &RHS );

    return( ret );
}