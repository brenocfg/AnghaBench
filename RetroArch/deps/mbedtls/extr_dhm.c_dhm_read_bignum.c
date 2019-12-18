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
typedef  int /*<<< orphan*/  mbedtls_mpi ;

/* Variables and functions */
 int MBEDTLS_ERR_DHM_BAD_INPUT_DATA ; 
 int MBEDTLS_ERR_DHM_READ_PARAMS_FAILED ; 
 int mbedtls_mpi_read_binary (int /*<<< orphan*/ *,unsigned char*,int) ; 

__attribute__((used)) static int dhm_read_bignum( mbedtls_mpi *X,
                            unsigned char **p,
                            const unsigned char *end )
{
    int ret, n;

    if( end - *p < 2 )
        return( MBEDTLS_ERR_DHM_BAD_INPUT_DATA );

    n = ( (*p)[0] << 8 ) | (*p)[1];
    (*p) += 2;

    if( (int)( end - *p ) < n )
        return( MBEDTLS_ERR_DHM_BAD_INPUT_DATA );

    if( ( ret = mbedtls_mpi_read_binary( X, *p, n ) ) != 0 )
        return( MBEDTLS_ERR_DHM_READ_PARAMS_FAILED + ret );

    (*p) += n;

    return( 0 );
}