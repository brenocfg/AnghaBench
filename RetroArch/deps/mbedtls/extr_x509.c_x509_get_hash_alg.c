#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int tag; unsigned char* p; size_t len; } ;
typedef  TYPE_1__ mbedtls_x509_buf ;
typedef  int /*<<< orphan*/  mbedtls_md_type_t ;

/* Variables and functions */
 int MBEDTLS_ASN1_CONSTRUCTED ; 
 int /*<<< orphan*/  MBEDTLS_ASN1_NULL ; 
 int /*<<< orphan*/  MBEDTLS_ASN1_OID ; 
 int MBEDTLS_ASN1_SEQUENCE ; 
 int MBEDTLS_ERR_ASN1_LENGTH_MISMATCH ; 
 int MBEDTLS_ERR_ASN1_OUT_OF_DATA ; 
 int MBEDTLS_ERR_ASN1_UNEXPECTED_TAG ; 
 int MBEDTLS_ERR_X509_INVALID_ALG ; 
 int mbedtls_asn1_get_tag (unsigned char**,unsigned char const*,size_t*,int /*<<< orphan*/ ) ; 
 int mbedtls_oid_get_md_alg (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int x509_get_hash_alg( const mbedtls_x509_buf *alg, mbedtls_md_type_t *md_alg )
{
    int ret;
    unsigned char *p;
    const unsigned char *end;
    mbedtls_x509_buf md_oid;
    size_t len;

    /* Make sure we got a SEQUENCE and setup bounds */
    if( alg->tag != ( MBEDTLS_ASN1_CONSTRUCTED | MBEDTLS_ASN1_SEQUENCE ) )
        return( MBEDTLS_ERR_X509_INVALID_ALG +
                MBEDTLS_ERR_ASN1_UNEXPECTED_TAG );

    p = (unsigned char *) alg->p;
    end = p + alg->len;

    if( p >= end )
        return( MBEDTLS_ERR_X509_INVALID_ALG +
                MBEDTLS_ERR_ASN1_OUT_OF_DATA );

    /* Parse md_oid */
    md_oid.tag = *p;

    if( ( ret = mbedtls_asn1_get_tag( &p, end, &md_oid.len, MBEDTLS_ASN1_OID ) ) != 0 )
        return( MBEDTLS_ERR_X509_INVALID_ALG + ret );

    md_oid.p = p;
    p += md_oid.len;

    /* Get md_alg from md_oid */
    if( ( ret = mbedtls_oid_get_md_alg( &md_oid, md_alg ) ) != 0 )
        return( MBEDTLS_ERR_X509_INVALID_ALG + ret );

    /* Make sure params is absent of NULL */
    if( p == end )
        return( 0 );

    if( ( ret = mbedtls_asn1_get_tag( &p, end, &len, MBEDTLS_ASN1_NULL ) ) != 0 || len != 0 )
        return( MBEDTLS_ERR_X509_INVALID_ALG + ret );

    if( p != end )
        return( MBEDTLS_ERR_X509_INVALID_ALG +
                MBEDTLS_ERR_ASN1_LENGTH_MISMATCH );

    return( 0 );
}