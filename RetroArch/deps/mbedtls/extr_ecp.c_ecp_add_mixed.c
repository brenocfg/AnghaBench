#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_2__ ;
typedef  struct TYPE_30__   TYPE_1__ ;

/* Type definitions */
struct TYPE_30__ {int /*<<< orphan*/ * p; } ;
typedef  TYPE_1__ mbedtls_mpi ;
struct TYPE_31__ {TYPE_1__ Z; TYPE_1__ Y; TYPE_1__ X; } ;
typedef  TYPE_2__ mbedtls_ecp_point ;
typedef  int /*<<< orphan*/  mbedtls_ecp_group ;

/* Variables and functions */
 int MBEDTLS_ERR_ECP_BAD_INPUT_DATA ; 
 int /*<<< orphan*/  MBEDTLS_MPI_CHK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MOD_ADD (TYPE_1__) ; 
 int /*<<< orphan*/  MOD_MUL (TYPE_1__) ; 
 int /*<<< orphan*/  MOD_SUB (TYPE_1__) ; 
 int /*<<< orphan*/  add_count ; 
 int ecp_double_jac (int /*<<< orphan*/  const*,TYPE_2__*,TYPE_2__ const*) ; 
 int mbedtls_ecp_copy (TYPE_2__*,TYPE_2__ const*) ; 
 int mbedtls_ecp_set_zero (TYPE_2__*) ; 
 int mbedtls_internal_ecp_add_mixed (int /*<<< orphan*/  const*,TYPE_2__*,TYPE_2__ const*,TYPE_2__ const*) ; 
 scalar_t__ mbedtls_internal_ecp_grp_capable (int /*<<< orphan*/  const*) ; 
 scalar_t__ mbedtls_mpi_cmp_int (TYPE_1__*,int) ; 
 int /*<<< orphan*/  mbedtls_mpi_copy (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  mbedtls_mpi_free (TYPE_1__*) ; 
 int /*<<< orphan*/  mbedtls_mpi_init (TYPE_1__*) ; 
 int /*<<< orphan*/  mbedtls_mpi_mul_int (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  mbedtls_mpi_mul_mpi (TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  mbedtls_mpi_sub_mpi (TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static int ecp_add_mixed( const mbedtls_ecp_group *grp, mbedtls_ecp_point *R,
                          const mbedtls_ecp_point *P, const mbedtls_ecp_point *Q )
{
    int ret;
    mbedtls_mpi T1, T2, T3, T4, X, Y, Z;

#if defined(MBEDTLS_SELF_TEST)
    add_count++;
#endif

#if defined(MBEDTLS_ECP_ADD_MIXED_ALT)
    if ( mbedtls_internal_ecp_grp_capable( grp ) )
    {
        return mbedtls_internal_ecp_add_mixed( grp, R, P, Q );
    }
#endif /* MBEDTLS_ECP_ADD_MIXED_ALT */

    /*
     * Trivial cases: P == 0 or Q == 0 (case 1)
     */
    if( mbedtls_mpi_cmp_int( &P->Z, 0 ) == 0 )
        return( mbedtls_ecp_copy( R, Q ) );

    if( Q->Z.p != NULL && mbedtls_mpi_cmp_int( &Q->Z, 0 ) == 0 )
        return( mbedtls_ecp_copy( R, P ) );

    /*
     * Make sure Q coordinates are normalized
     */
    if( Q->Z.p != NULL && mbedtls_mpi_cmp_int( &Q->Z, 1 ) != 0 )
        return( MBEDTLS_ERR_ECP_BAD_INPUT_DATA );

    mbedtls_mpi_init( &T1 ); mbedtls_mpi_init( &T2 ); mbedtls_mpi_init( &T3 ); mbedtls_mpi_init( &T4 );
    mbedtls_mpi_init( &X ); mbedtls_mpi_init( &Y ); mbedtls_mpi_init( &Z );

    MBEDTLS_MPI_CHK( mbedtls_mpi_mul_mpi( &T1,  &P->Z,  &P->Z ) );  MOD_MUL( T1 );
    MBEDTLS_MPI_CHK( mbedtls_mpi_mul_mpi( &T2,  &T1,    &P->Z ) );  MOD_MUL( T2 );
    MBEDTLS_MPI_CHK( mbedtls_mpi_mul_mpi( &T1,  &T1,    &Q->X ) );  MOD_MUL( T1 );
    MBEDTLS_MPI_CHK( mbedtls_mpi_mul_mpi( &T2,  &T2,    &Q->Y ) );  MOD_MUL( T2 );
    MBEDTLS_MPI_CHK( mbedtls_mpi_sub_mpi( &T1,  &T1,    &P->X ) );  MOD_SUB( T1 );
    MBEDTLS_MPI_CHK( mbedtls_mpi_sub_mpi( &T2,  &T2,    &P->Y ) );  MOD_SUB( T2 );

    /* Special cases (2) and (3) */
    if( mbedtls_mpi_cmp_int( &T1, 0 ) == 0 )
    {
        if( mbedtls_mpi_cmp_int( &T2, 0 ) == 0 )
        {
            ret = ecp_double_jac( grp, R, P );
            goto cleanup;
        }
        else
        {
            ret = mbedtls_ecp_set_zero( R );
            goto cleanup;
        }
    }

    MBEDTLS_MPI_CHK( mbedtls_mpi_mul_mpi( &Z,   &P->Z,  &T1   ) );  MOD_MUL( Z  );
    MBEDTLS_MPI_CHK( mbedtls_mpi_mul_mpi( &T3,  &T1,    &T1   ) );  MOD_MUL( T3 );
    MBEDTLS_MPI_CHK( mbedtls_mpi_mul_mpi( &T4,  &T3,    &T1   ) );  MOD_MUL( T4 );
    MBEDTLS_MPI_CHK( mbedtls_mpi_mul_mpi( &T3,  &T3,    &P->X ) );  MOD_MUL( T3 );
    MBEDTLS_MPI_CHK( mbedtls_mpi_mul_int( &T1,  &T3,    2     ) );  MOD_ADD( T1 );
    MBEDTLS_MPI_CHK( mbedtls_mpi_mul_mpi( &X,   &T2,    &T2   ) );  MOD_MUL( X  );
    MBEDTLS_MPI_CHK( mbedtls_mpi_sub_mpi( &X,   &X,     &T1   ) );  MOD_SUB( X  );
    MBEDTLS_MPI_CHK( mbedtls_mpi_sub_mpi( &X,   &X,     &T4   ) );  MOD_SUB( X  );
    MBEDTLS_MPI_CHK( mbedtls_mpi_sub_mpi( &T3,  &T3,    &X    ) );  MOD_SUB( T3 );
    MBEDTLS_MPI_CHK( mbedtls_mpi_mul_mpi( &T3,  &T3,    &T2   ) );  MOD_MUL( T3 );
    MBEDTLS_MPI_CHK( mbedtls_mpi_mul_mpi( &T4,  &T4,    &P->Y ) );  MOD_MUL( T4 );
    MBEDTLS_MPI_CHK( mbedtls_mpi_sub_mpi( &Y,   &T3,    &T4   ) );  MOD_SUB( Y  );

    MBEDTLS_MPI_CHK( mbedtls_mpi_copy( &R->X, &X ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_copy( &R->Y, &Y ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_copy( &R->Z, &Z ) );

cleanup:

    mbedtls_mpi_free( &T1 ); mbedtls_mpi_free( &T2 ); mbedtls_mpi_free( &T3 ); mbedtls_mpi_free( &T4 );
    mbedtls_mpi_free( &X ); mbedtls_mpi_free( &Y ); mbedtls_mpi_free( &Z );

    return( ret );
}