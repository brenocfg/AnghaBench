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

/* Variables and functions */
 int MBEDTLS_ERR_ASN1_UNEXPECTED_TAG ; 
 int MBEDTLS_ERR_X509_INVALID_VERSION ; 
 int mbedtls_asn1_get_int (unsigned char**,unsigned char const*,int*) ; 

__attribute__((used)) static int x509_csr_get_version( unsigned char **p,
                             const unsigned char *end,
                             int *ver )
{
    int ret;

    if( ( ret = mbedtls_asn1_get_int( p, end, ver ) ) != 0 )
    {
        if( ret == MBEDTLS_ERR_ASN1_UNEXPECTED_TAG )
        {
            *ver = 0;
            return( 0 );
        }

        return( MBEDTLS_ERR_X509_INVALID_VERSION + ret );
    }

    return( 0 );
}