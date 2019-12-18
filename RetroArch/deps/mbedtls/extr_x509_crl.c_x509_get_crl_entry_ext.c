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
struct TYPE_3__ {unsigned char tag; unsigned char* p; size_t len; } ;
typedef  TYPE_1__ mbedtls_x509_buf ;

/* Variables and functions */
 int MBEDTLS_ASN1_CONSTRUCTED ; 
 int MBEDTLS_ASN1_SEQUENCE ; 
 int MBEDTLS_ERR_ASN1_LENGTH_MISMATCH ; 
 int MBEDTLS_ERR_ASN1_UNEXPECTED_TAG ; 
 int MBEDTLS_ERR_X509_INVALID_EXTENSIONS ; 
 int mbedtls_asn1_get_tag (unsigned char**,unsigned char const*,size_t*,int) ; 

__attribute__((used)) static int x509_get_crl_entry_ext( unsigned char **p,
                             const unsigned char *end,
                             mbedtls_x509_buf *ext )
{
    int ret;
    size_t len = 0;

    /* OPTIONAL */
    if( end <= *p )
        return( 0 );

    ext->tag = **p;
    ext->p = *p;

    /*
     * Get CRL-entry extension sequence header
     * crlEntryExtensions      Extensions OPTIONAL  -- if present, MUST be v2
     */
    if( ( ret = mbedtls_asn1_get_tag( p, end, &ext->len,
            MBEDTLS_ASN1_CONSTRUCTED | MBEDTLS_ASN1_SEQUENCE ) ) != 0 )
    {
        if( ret == MBEDTLS_ERR_ASN1_UNEXPECTED_TAG )
        {
            ext->p = NULL;
            return( 0 );
        }
        return( MBEDTLS_ERR_X509_INVALID_EXTENSIONS + ret );
    }

    end = *p + ext->len;

    if( end != *p + ext->len )
        return( MBEDTLS_ERR_X509_INVALID_EXTENSIONS +
                MBEDTLS_ERR_ASN1_LENGTH_MISMATCH );

    while( *p < end )
    {
        if( ( ret = mbedtls_asn1_get_tag( p, end, &len,
                MBEDTLS_ASN1_CONSTRUCTED | MBEDTLS_ASN1_SEQUENCE ) ) != 0 )
            return( MBEDTLS_ERR_X509_INVALID_EXTENSIONS + ret );

        *p += len;
    }

    if( *p != end )
        return( MBEDTLS_ERR_X509_INVALID_EXTENSIONS +
                MBEDTLS_ERR_ASN1_LENGTH_MISMATCH );

    return( 0 );
}