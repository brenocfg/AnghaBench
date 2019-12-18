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
 int /*<<< orphan*/  MBEDTLS_ASN1_BIT_STRING ; 
 int MBEDTLS_ERR_ASN1_INVALID_DATA ; 
 int mbedtls_asn1_get_tag (unsigned char**,unsigned char const*,size_t*,int /*<<< orphan*/ ) ; 

int mbedtls_asn1_get_bitstring_null( unsigned char **p, const unsigned char *end,
                             size_t *len )
{
    int ret;

    if( ( ret = mbedtls_asn1_get_tag( p, end, len, MBEDTLS_ASN1_BIT_STRING ) ) != 0 )
        return( ret );

    if( (*len)-- < 2 || *(*p)++ != 0 )
        return( MBEDTLS_ERR_ASN1_INVALID_DATA );

    return( 0 );
}