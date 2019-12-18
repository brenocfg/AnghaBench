#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  X; int /*<<< orphan*/  Y; int /*<<< orphan*/  Z; } ;
typedef  TYPE_1__ mbedtls_ecp_point ;
struct TYPE_6__ {int /*<<< orphan*/  P; } ;
typedef  TYPE_2__ mbedtls_ecp_group ;

/* Variables and functions */
 int MBEDTLS_ECP_PF_COMPRESSED ; 
 int MBEDTLS_ECP_PF_UNCOMPRESSED ; 
 int MBEDTLS_ERR_ECP_BAD_INPUT_DATA ; 
 int MBEDTLS_ERR_ECP_BUFFER_TOO_SMALL ; 
 int /*<<< orphan*/  MBEDTLS_MPI_CHK (int /*<<< orphan*/ ) ; 
 scalar_t__ mbedtls_mpi_cmp_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int mbedtls_mpi_get_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t mbedtls_mpi_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_mpi_write_binary (int /*<<< orphan*/ *,unsigned char*,size_t) ; 

int mbedtls_ecp_point_write_binary( const mbedtls_ecp_group *grp, const mbedtls_ecp_point *P,
                            int format, size_t *olen,
                            unsigned char *buf, size_t buflen )
{
    int ret = 0;
    size_t plen;

    if( format != MBEDTLS_ECP_PF_UNCOMPRESSED &&
        format != MBEDTLS_ECP_PF_COMPRESSED )
        return( MBEDTLS_ERR_ECP_BAD_INPUT_DATA );

    /*
     * Common case: P == 0
     */
    if( mbedtls_mpi_cmp_int( &P->Z, 0 ) == 0 )
    {
        if( buflen < 1 )
            return( MBEDTLS_ERR_ECP_BUFFER_TOO_SMALL );

        buf[0] = 0x00;
        *olen = 1;

        return( 0 );
    }

    plen = mbedtls_mpi_size( &grp->P );

    if( format == MBEDTLS_ECP_PF_UNCOMPRESSED )
    {
        *olen = 2 * plen + 1;

        if( buflen < *olen )
            return( MBEDTLS_ERR_ECP_BUFFER_TOO_SMALL );

        buf[0] = 0x04;
        MBEDTLS_MPI_CHK( mbedtls_mpi_write_binary( &P->X, buf + 1, plen ) );
        MBEDTLS_MPI_CHK( mbedtls_mpi_write_binary( &P->Y, buf + 1 + plen, plen ) );
    }
    else if( format == MBEDTLS_ECP_PF_COMPRESSED )
    {
        *olen = plen + 1;

        if( buflen < *olen )
            return( MBEDTLS_ERR_ECP_BUFFER_TOO_SMALL );

        buf[0] = 0x02 + mbedtls_mpi_get_bit( &P->Y, 0 );
        MBEDTLS_MPI_CHK( mbedtls_mpi_write_binary( &P->X, buf + 1, plen ) );
    }

cleanup:
    return( ret );
}