#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned char tag; size_t len; unsigned char* p; } ;
struct TYPE_4__ {int /*<<< orphan*/ * next; TYPE_2__ val; TYPE_2__ oid; } ;
typedef  TYPE_1__ mbedtls_x509_name ;
typedef  TYPE_2__ mbedtls_x509_buf ;

/* Variables and functions */
 unsigned char MBEDTLS_ASN1_BIT_STRING ; 
 unsigned char MBEDTLS_ASN1_BMP_STRING ; 
 int MBEDTLS_ASN1_CONSTRUCTED ; 
 unsigned char MBEDTLS_ASN1_IA5_STRING ; 
 int MBEDTLS_ASN1_OID ; 
 unsigned char MBEDTLS_ASN1_PRINTABLE_STRING ; 
 int MBEDTLS_ASN1_SEQUENCE ; 
 unsigned char MBEDTLS_ASN1_T61_STRING ; 
 unsigned char MBEDTLS_ASN1_UNIVERSAL_STRING ; 
 unsigned char MBEDTLS_ASN1_UTF8_STRING ; 
 int MBEDTLS_ERR_ASN1_OUT_OF_DATA ; 
 int MBEDTLS_ERR_ASN1_UNEXPECTED_TAG ; 
 int MBEDTLS_ERR_X509_INVALID_NAME ; 
 int mbedtls_asn1_get_len (unsigned char**,unsigned char const*,size_t*) ; 
 int mbedtls_asn1_get_tag (unsigned char**,unsigned char const*,size_t*,int) ; 

__attribute__((used)) static int x509_get_attr_type_value( unsigned char **p,
                                     const unsigned char *end,
                                     mbedtls_x509_name *cur )
{
    int ret;
    size_t len;
    mbedtls_x509_buf *oid;
    mbedtls_x509_buf *val;

    if( ( ret = mbedtls_asn1_get_tag( p, end, &len,
            MBEDTLS_ASN1_CONSTRUCTED | MBEDTLS_ASN1_SEQUENCE ) ) != 0 )
        return( MBEDTLS_ERR_X509_INVALID_NAME + ret );

    if( ( end - *p ) < 1 )
        return( MBEDTLS_ERR_X509_INVALID_NAME +
                MBEDTLS_ERR_ASN1_OUT_OF_DATA );

    oid = &cur->oid;
    oid->tag = **p;

    if( ( ret = mbedtls_asn1_get_tag( p, end, &oid->len, MBEDTLS_ASN1_OID ) ) != 0 )
        return( MBEDTLS_ERR_X509_INVALID_NAME + ret );

    oid->p = *p;
    *p += oid->len;

    if( ( end - *p ) < 1 )
        return( MBEDTLS_ERR_X509_INVALID_NAME +
                MBEDTLS_ERR_ASN1_OUT_OF_DATA );

    if( **p != MBEDTLS_ASN1_BMP_STRING && **p != MBEDTLS_ASN1_UTF8_STRING      &&
        **p != MBEDTLS_ASN1_T61_STRING && **p != MBEDTLS_ASN1_PRINTABLE_STRING &&
        **p != MBEDTLS_ASN1_IA5_STRING && **p != MBEDTLS_ASN1_UNIVERSAL_STRING &&
        **p != MBEDTLS_ASN1_BIT_STRING )
        return( MBEDTLS_ERR_X509_INVALID_NAME +
                MBEDTLS_ERR_ASN1_UNEXPECTED_TAG );

    val = &cur->val;
    val->tag = *(*p)++;

    if( ( ret = mbedtls_asn1_get_len( p, end, &val->len ) ) != 0 )
        return( MBEDTLS_ERR_X509_INVALID_NAME + ret );

    val->p = *p;
    *p += val->len;

    cur->next = NULL;

    return( 0 );
}