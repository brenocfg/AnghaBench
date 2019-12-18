#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t mbedtls_mpi_uint ;
struct TYPE_5__ {size_t* p; } ;
typedef  TYPE_1__ mbedtls_mpi ;

/* Variables and functions */
 int /*<<< orphan*/  CHARS_TO_LIMBS (size_t) ; 
 int /*<<< orphan*/  MBEDTLS_MPI_CHK (int /*<<< orphan*/ ) ; 
 size_t ciL ; 
 int /*<<< orphan*/  mbedtls_mpi_grow (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_mpi_lset (TYPE_1__*,int /*<<< orphan*/ ) ; 

int mbedtls_mpi_read_binary( mbedtls_mpi *X, const unsigned char *buf, size_t buflen )
{
    int ret;
    size_t i, j, n;

    for( n = 0; n < buflen; n++ )
        if( buf[n] != 0 )
            break;

    MBEDTLS_MPI_CHK( mbedtls_mpi_grow( X, CHARS_TO_LIMBS( buflen - n ) ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_lset( X, 0 ) );

    for( i = buflen, j = 0; i > n; i--, j++ )
        X->p[j / ciL] |= ((mbedtls_mpi_uint) buf[i - 1]) << ((j % ciL) << 3);

cleanup:

    return( ret );
}