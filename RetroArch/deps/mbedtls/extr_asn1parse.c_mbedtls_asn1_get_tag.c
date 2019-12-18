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
 int MBEDTLS_ERR_ASN1_OUT_OF_DATA ; 
 int MBEDTLS_ERR_ASN1_UNEXPECTED_TAG ; 
 int mbedtls_asn1_get_len (unsigned char**,unsigned char const*,size_t*) ; 

int mbedtls_asn1_get_tag( unsigned char **p,
                  const unsigned char *end,
                  size_t *len, int tag )
{
    if( ( end - *p ) < 1 )
        return( MBEDTLS_ERR_ASN1_OUT_OF_DATA );

    if( **p != tag )
        return( MBEDTLS_ERR_ASN1_UNEXPECTED_TAG );

    (*p)++;

    return( mbedtls_asn1_get_len( p, end, len ) );
}