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
 int /*<<< orphan*/  MBEDTLS_ASN1_BOOLEAN ; 
 int MBEDTLS_ERR_ASN1_INVALID_LENGTH ; 
 int mbedtls_asn1_get_tag (unsigned char**,unsigned char const*,size_t*,int /*<<< orphan*/ ) ; 

int mbedtls_asn1_get_bool( unsigned char **p,
                   const unsigned char *end,
                   int *val )
{
    int ret;
    size_t len;

    if( ( ret = mbedtls_asn1_get_tag( p, end, &len, MBEDTLS_ASN1_BOOLEAN ) ) != 0 )
        return( ret );

    if( len != 1 )
        return( MBEDTLS_ERR_ASN1_INVALID_LENGTH );

    *val = ( **p != 0 ) ? 1 : 0;
    (*p)++;

    return( 0 );
}