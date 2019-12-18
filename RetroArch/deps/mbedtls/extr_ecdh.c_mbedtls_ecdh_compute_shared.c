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
struct TYPE_9__ {int /*<<< orphan*/  X; } ;
typedef  TYPE_1__ mbedtls_ecp_point ;
typedef  int /*<<< orphan*/  mbedtls_ecp_group ;

/* Variables and functions */
 int MBEDTLS_ERR_ECP_BAD_INPUT_DATA ; 
 int /*<<< orphan*/  MBEDTLS_MPI_CHK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_ecp_check_pubkey (int /*<<< orphan*/ *,TYPE_1__ const*) ; 
 scalar_t__ mbedtls_ecp_is_zero (TYPE_1__*) ; 
 int /*<<< orphan*/  mbedtls_ecp_mul (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/  const*,TYPE_1__ const*,int (*) (void*,unsigned char*,size_t),void*) ; 
 int /*<<< orphan*/  mbedtls_ecp_point_free (TYPE_1__*) ; 
 int /*<<< orphan*/  mbedtls_ecp_point_init (TYPE_1__*) ; 
 int /*<<< orphan*/  mbedtls_mpi_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int mbedtls_ecdh_compute_shared( mbedtls_ecp_group *grp, mbedtls_mpi *z,
                         const mbedtls_ecp_point *Q, const mbedtls_mpi *d,
                         int (*f_rng)(void *, unsigned char *, size_t),
                         void *p_rng )
{
    int ret;
    mbedtls_ecp_point P;

    mbedtls_ecp_point_init( &P );

    /*
     * Make sure Q is a valid pubkey before using it
     */
    MBEDTLS_MPI_CHK( mbedtls_ecp_check_pubkey( grp, Q ) );

    MBEDTLS_MPI_CHK( mbedtls_ecp_mul( grp, &P, d, Q, f_rng, p_rng ) );

    if( mbedtls_ecp_is_zero( &P ) )
    {
        ret = MBEDTLS_ERR_ECP_BAD_INPUT_DATA;
        goto cleanup;
    }

    MBEDTLS_MPI_CHK( mbedtls_mpi_copy( z, &P.X ) );

cleanup:
    mbedtls_ecp_point_free( &P );

    return( ret );
}