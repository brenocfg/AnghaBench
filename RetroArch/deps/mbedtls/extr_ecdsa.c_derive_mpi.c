#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mbedtls_mpi ;
struct TYPE_3__ {int nbits; int /*<<< orphan*/  N; } ;
typedef  TYPE_1__ mbedtls_ecp_group ;

/* Variables and functions */
 int /*<<< orphan*/  MBEDTLS_MPI_CHK (int /*<<< orphan*/ ) ; 
 scalar_t__ mbedtls_mpi_cmp_mpi (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_mpi_read_binary (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  mbedtls_mpi_shift_r (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  mbedtls_mpi_sub_mpi (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int derive_mpi( const mbedtls_ecp_group *grp, mbedtls_mpi *x,
                       const unsigned char *buf, size_t blen )
{
    int ret;
    size_t n_size = ( grp->nbits + 7 ) / 8;
    size_t use_size = blen > n_size ? n_size : blen;

    MBEDTLS_MPI_CHK( mbedtls_mpi_read_binary( x, buf, use_size ) );
    if( use_size * 8 > grp->nbits )
        MBEDTLS_MPI_CHK( mbedtls_mpi_shift_r( x, use_size * 8 - grp->nbits ) );

    /* While at it, reduce modulo N */
    if( mbedtls_mpi_cmp_mpi( x, &grp->N ) >= 0 )
        MBEDTLS_MPI_CHK( mbedtls_mpi_sub_mpi( x, x, &grp->N ) );

cleanup:
    return( ret );
}