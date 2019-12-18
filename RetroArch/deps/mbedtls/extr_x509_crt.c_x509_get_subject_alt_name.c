#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {unsigned char* p; unsigned char tag; size_t len; } ;
struct TYPE_6__ {struct TYPE_6__* next; TYPE_3__ buf; } ;
typedef  TYPE_1__ mbedtls_x509_sequence ;
typedef  TYPE_1__ mbedtls_asn1_sequence ;
typedef  TYPE_3__ mbedtls_asn1_buf ;

/* Variables and functions */
 int MBEDTLS_ASN1_CONSTRUCTED ; 
 unsigned char MBEDTLS_ASN1_CONTEXT_SPECIFIC ; 
 int MBEDTLS_ASN1_SEQUENCE ; 
 int MBEDTLS_ERR_ASN1_ALLOC_FAILED ; 
 int MBEDTLS_ERR_ASN1_LENGTH_MISMATCH ; 
 int MBEDTLS_ERR_ASN1_OUT_OF_DATA ; 
 int MBEDTLS_ERR_ASN1_UNEXPECTED_TAG ; 
 int MBEDTLS_ERR_X509_INVALID_EXTENSIONS ; 
 int mbedtls_asn1_get_len (unsigned char**,unsigned char const*,size_t*) ; 
 int mbedtls_asn1_get_tag (unsigned char**,unsigned char const*,size_t*,int) ; 
 TYPE_1__* mbedtls_calloc (int,int) ; 

__attribute__((used)) static int x509_get_subject_alt_name( unsigned char **p,
                                      const unsigned char *end,
                                      mbedtls_x509_sequence *subject_alt_name )
{
    int ret;
    size_t len, tag_len;
    mbedtls_asn1_buf *buf;
    unsigned char tag;
    mbedtls_asn1_sequence *cur = subject_alt_name;

    /* Get main sequence tag */
    if( ( ret = mbedtls_asn1_get_tag( p, end, &len,
            MBEDTLS_ASN1_CONSTRUCTED | MBEDTLS_ASN1_SEQUENCE ) ) != 0 )
        return( MBEDTLS_ERR_X509_INVALID_EXTENSIONS + ret );

    if( *p + len != end )
        return( MBEDTLS_ERR_X509_INVALID_EXTENSIONS +
                MBEDTLS_ERR_ASN1_LENGTH_MISMATCH );

    while( *p < end )
    {
        if( ( end - *p ) < 1 )
            return( MBEDTLS_ERR_X509_INVALID_EXTENSIONS +
                    MBEDTLS_ERR_ASN1_OUT_OF_DATA );

        tag = **p;
        (*p)++;
        if( ( ret = mbedtls_asn1_get_len( p, end, &tag_len ) ) != 0 )
            return( MBEDTLS_ERR_X509_INVALID_EXTENSIONS + ret );

        if( ( tag & MBEDTLS_ASN1_CONTEXT_SPECIFIC ) != MBEDTLS_ASN1_CONTEXT_SPECIFIC )
            return( MBEDTLS_ERR_X509_INVALID_EXTENSIONS +
                    MBEDTLS_ERR_ASN1_UNEXPECTED_TAG );

        /* Skip everything but DNS name */
        if( tag != ( MBEDTLS_ASN1_CONTEXT_SPECIFIC | 2 ) )
        {
            *p += tag_len;
            continue;
        }

        /* Allocate and assign next pointer */
        if( cur->buf.p != NULL )
        {
            if( cur->next != NULL )
                return( MBEDTLS_ERR_X509_INVALID_EXTENSIONS );

            cur->next = mbedtls_calloc( 1, sizeof( mbedtls_asn1_sequence ) );

            if( cur->next == NULL )
                return( MBEDTLS_ERR_X509_INVALID_EXTENSIONS +
                        MBEDTLS_ERR_ASN1_ALLOC_FAILED );

            cur = cur->next;
        }

        buf = &(cur->buf);
        buf->tag = tag;
        buf->p = *p;
        buf->len = tag_len;
        *p += buf->len;
    }

    /* Set final sequence entry's next pointer to NULL */
    cur->next = NULL;

    if( *p != end )
        return( MBEDTLS_ERR_X509_INVALID_EXTENSIONS +
                MBEDTLS_ERR_ASN1_LENGTH_MISMATCH );

    return( 0 );
}