#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  const mbedtls_mpi ;
struct TYPE_14__ {int /*<<< orphan*/  const Z; int /*<<< orphan*/  const X; } ;
typedef  TYPE_1__ mbedtls_ecp_point ;
struct TYPE_15__ {int /*<<< orphan*/  const A; } ;
typedef  TYPE_2__ mbedtls_ecp_group ;

/* Variables and functions */
 int /*<<< orphan*/  MBEDTLS_MPI_CHK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MOD_ADD (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  MOD_MUL (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  MOD_SUB (int /*<<< orphan*/  const) ; 
 int mbedtls_internal_ecp_double_add_mxz (TYPE_2__ const*,TYPE_1__*,TYPE_1__*,TYPE_1__ const*,TYPE_1__ const*,int /*<<< orphan*/  const*) ; 
 scalar_t__ mbedtls_internal_ecp_grp_capable (TYPE_2__ const*) ; 
 int /*<<< orphan*/  mbedtls_mpi_add_mpi (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  mbedtls_mpi_free (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  mbedtls_mpi_init (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  mbedtls_mpi_mul_mpi (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  mbedtls_mpi_sub_mpi (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int ecp_double_add_mxz( const mbedtls_ecp_group *grp,
                               mbedtls_ecp_point *R, mbedtls_ecp_point *S,
                               const mbedtls_ecp_point *P, const mbedtls_ecp_point *Q,
                               const mbedtls_mpi *d )
{
    int ret;
    mbedtls_mpi A, AA, B, BB, E, C, D, DA, CB;

#if defined(MBEDTLS_ECP_DOUBLE_ADD_MXZ_ALT)
    if ( mbedtls_internal_ecp_grp_capable( grp ) )
    {
        return mbedtls_internal_ecp_double_add_mxz( grp, R, S, P, Q, d );
    }
#endif /* MBEDTLS_ECP_DOUBLE_ADD_MXZ_ALT */

    mbedtls_mpi_init( &A ); mbedtls_mpi_init( &AA ); mbedtls_mpi_init( &B );
    mbedtls_mpi_init( &BB ); mbedtls_mpi_init( &E ); mbedtls_mpi_init( &C );
    mbedtls_mpi_init( &D ); mbedtls_mpi_init( &DA ); mbedtls_mpi_init( &CB );

    MBEDTLS_MPI_CHK( mbedtls_mpi_add_mpi( &A,    &P->X,   &P->Z ) ); MOD_ADD( A    );
    MBEDTLS_MPI_CHK( mbedtls_mpi_mul_mpi( &AA,   &A,      &A    ) ); MOD_MUL( AA   );
    MBEDTLS_MPI_CHK( mbedtls_mpi_sub_mpi( &B,    &P->X,   &P->Z ) ); MOD_SUB( B    );
    MBEDTLS_MPI_CHK( mbedtls_mpi_mul_mpi( &BB,   &B,      &B    ) ); MOD_MUL( BB   );
    MBEDTLS_MPI_CHK( mbedtls_mpi_sub_mpi( &E,    &AA,     &BB   ) ); MOD_SUB( E    );
    MBEDTLS_MPI_CHK( mbedtls_mpi_add_mpi( &C,    &Q->X,   &Q->Z ) ); MOD_ADD( C    );
    MBEDTLS_MPI_CHK( mbedtls_mpi_sub_mpi( &D,    &Q->X,   &Q->Z ) ); MOD_SUB( D    );
    MBEDTLS_MPI_CHK( mbedtls_mpi_mul_mpi( &DA,   &D,      &A    ) ); MOD_MUL( DA   );
    MBEDTLS_MPI_CHK( mbedtls_mpi_mul_mpi( &CB,   &C,      &B    ) ); MOD_MUL( CB   );
    MBEDTLS_MPI_CHK( mbedtls_mpi_add_mpi( &S->X, &DA,     &CB   ) ); MOD_MUL( S->X );
    MBEDTLS_MPI_CHK( mbedtls_mpi_mul_mpi( &S->X, &S->X,   &S->X ) ); MOD_MUL( S->X );
    MBEDTLS_MPI_CHK( mbedtls_mpi_sub_mpi( &S->Z, &DA,     &CB   ) ); MOD_SUB( S->Z );
    MBEDTLS_MPI_CHK( mbedtls_mpi_mul_mpi( &S->Z, &S->Z,   &S->Z ) ); MOD_MUL( S->Z );
    MBEDTLS_MPI_CHK( mbedtls_mpi_mul_mpi( &S->Z, d,       &S->Z ) ); MOD_MUL( S->Z );
    MBEDTLS_MPI_CHK( mbedtls_mpi_mul_mpi( &R->X, &AA,     &BB   ) ); MOD_MUL( R->X );
    MBEDTLS_MPI_CHK( mbedtls_mpi_mul_mpi( &R->Z, &grp->A, &E    ) ); MOD_MUL( R->Z );
    MBEDTLS_MPI_CHK( mbedtls_mpi_add_mpi( &R->Z, &BB,     &R->Z ) ); MOD_ADD( R->Z );
    MBEDTLS_MPI_CHK( mbedtls_mpi_mul_mpi( &R->Z, &E,      &R->Z ) ); MOD_MUL( R->Z );

cleanup:
    mbedtls_mpi_free( &A ); mbedtls_mpi_free( &AA ); mbedtls_mpi_free( &B );
    mbedtls_mpi_free( &BB ); mbedtls_mpi_free( &E ); mbedtls_mpi_free( &C );
    mbedtls_mpi_free( &D ); mbedtls_mpi_free( &DA ); mbedtls_mpi_free( &CB );

    return( ret );
}