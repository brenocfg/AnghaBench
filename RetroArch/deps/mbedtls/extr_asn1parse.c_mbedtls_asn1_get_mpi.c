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
 int /*<<< orphan*/  MBEDTLS_ASN1_INTEGER ; 
 int mbedtls_asn1_get_tag (unsigned char**,unsigned char const*,size_t*,int /*<<< orphan*/ ) ; 
 int mbedtls_mpi_read_binary (int /*<<< orphan*/ *,unsigned char*,size_t) ; 

int mbedtls_asn1_get_mpi( unsigned char **p,
                  const unsigned char *end,
                  mbedtls_mpi *X )
{
    int ret;
    size_t len;

    if( ( ret = mbedtls_asn1_get_tag( p, end, &len, MBEDTLS_ASN1_INTEGER ) ) != 0 )
        return( ret );

    ret = mbedtls_mpi_read_binary( X, *p, len );

    *p += len;

    return( ret );
}