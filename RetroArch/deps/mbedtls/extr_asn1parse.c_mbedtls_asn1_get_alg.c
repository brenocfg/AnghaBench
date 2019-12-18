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
struct TYPE_5__ {unsigned char tag; size_t len; unsigned char* p; } ;
typedef  TYPE_1__ mbedtls_asn1_buf ;

/* Variables and functions */
 int MBEDTLS_ASN1_CONSTRUCTED ; 
 int MBEDTLS_ASN1_OID ; 
 int MBEDTLS_ASN1_SEQUENCE ; 
 int MBEDTLS_ERR_ASN1_LENGTH_MISMATCH ; 
 int MBEDTLS_ERR_ASN1_OUT_OF_DATA ; 
 int mbedtls_asn1_get_len (unsigned char**,unsigned char const*,size_t*) ; 
 int mbedtls_asn1_get_tag (unsigned char**,unsigned char const*,size_t*,int) ; 
 int /*<<< orphan*/  mbedtls_zeroize (TYPE_1__*,int) ; 

int mbedtls_asn1_get_alg( unsigned char **p,
                  const unsigned char *end,
                  mbedtls_asn1_buf *alg, mbedtls_asn1_buf *params )
{
    int ret;
    size_t len;

    if( ( ret = mbedtls_asn1_get_tag( p, end, &len,
            MBEDTLS_ASN1_CONSTRUCTED | MBEDTLS_ASN1_SEQUENCE ) ) != 0 )
        return( ret );

    if( ( end - *p ) < 1 )
        return( MBEDTLS_ERR_ASN1_OUT_OF_DATA );

    alg->tag = **p;
    end = *p + len;

    if( ( ret = mbedtls_asn1_get_tag( p, end, &alg->len, MBEDTLS_ASN1_OID ) ) != 0 )
        return( ret );

    alg->p = *p;
    *p += alg->len;

    if( *p == end )
    {
        mbedtls_zeroize( params, sizeof(mbedtls_asn1_buf) );
        return( 0 );
    }

    params->tag = **p;
    (*p)++;

    if( ( ret = mbedtls_asn1_get_len( p, end, &params->len ) ) != 0 )
        return( ret );

    params->p = *p;
    *p += params->len;

    if( *p != end )
        return( MBEDTLS_ERR_ASN1_LENGTH_MISMATCH );

    return( 0 );
}