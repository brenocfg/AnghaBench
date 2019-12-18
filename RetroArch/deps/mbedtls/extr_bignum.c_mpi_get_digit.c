#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  char mbedtls_mpi_uint ;

/* Variables and functions */
 int MBEDTLS_ERR_MPI_INVALID_CHARACTER ; 

__attribute__((used)) static int mpi_get_digit( mbedtls_mpi_uint *d, int radix, char c )
{
    *d = 255;

    if( c >= 0x30 && c <= 0x39 ) *d = c - 0x30;
    if( c >= 0x41 && c <= 0x46 ) *d = c - 0x37;
    if( c >= 0x61 && c <= 0x66 ) *d = c - 0x57;

    if( *d >= (mbedtls_mpi_uint) radix )
        return( MBEDTLS_ERR_MPI_INVALID_CHARACTER );

    return( 0 );
}