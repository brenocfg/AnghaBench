#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  Z; int /*<<< orphan*/  Y; int /*<<< orphan*/  X; } ;
typedef  TYPE_1__ mbedtls_ecp_point ;
struct TYPE_7__ {int /*<<< orphan*/  P; } ;
typedef  TYPE_2__ mbedtls_ecp_group ;

/* Variables and functions */
 int MBEDTLS_ERR_ECP_BAD_INPUT_DATA ; 
 int MBEDTLS_ERR_ECP_FEATURE_UNAVAILABLE ; 
 int /*<<< orphan*/  MBEDTLS_MPI_CHK (int /*<<< orphan*/ ) ; 
 int mbedtls_ecp_set_zero (TYPE_1__*) ; 
 int /*<<< orphan*/  mbedtls_mpi_lset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mbedtls_mpi_read_binary (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 
 size_t mbedtls_mpi_size (int /*<<< orphan*/ *) ; 

int mbedtls_ecp_point_read_binary( const mbedtls_ecp_group *grp, mbedtls_ecp_point *pt,
                           const unsigned char *buf, size_t ilen )
{
    int ret;
    size_t plen;

    if( ilen < 1 )
        return( MBEDTLS_ERR_ECP_BAD_INPUT_DATA );

    if( buf[0] == 0x00 )
    {
        if( ilen == 1 )
            return( mbedtls_ecp_set_zero( pt ) );
        else
            return( MBEDTLS_ERR_ECP_BAD_INPUT_DATA );
    }

    plen = mbedtls_mpi_size( &grp->P );

    if( buf[0] != 0x04 )
        return( MBEDTLS_ERR_ECP_FEATURE_UNAVAILABLE );

    if( ilen != 2 * plen + 1 )
        return( MBEDTLS_ERR_ECP_BAD_INPUT_DATA );

    MBEDTLS_MPI_CHK( mbedtls_mpi_read_binary( &pt->X, buf + 1, plen ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_read_binary( &pt->Y, buf + 1 + plen, plen ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_lset( &pt->Z, 1 ) );

cleanup:
    return( ret );
}