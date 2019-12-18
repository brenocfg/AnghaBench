#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mbedtls_md_type_t ;
struct TYPE_6__ {unsigned char* p; int len; int tag; } ;
typedef  TYPE_1__ mbedtls_asn1_buf ;

/* Variables and functions */
 int MBEDTLS_ASN1_CONSTRUCTED ; 
 int /*<<< orphan*/  MBEDTLS_ASN1_OCTET_STRING ; 
 int MBEDTLS_ASN1_SEQUENCE ; 
 int MBEDTLS_ERR_ASN1_LENGTH_MISMATCH ; 
 int MBEDTLS_ERR_ASN1_UNEXPECTED_TAG ; 
 int MBEDTLS_ERR_PKCS5_FEATURE_UNAVAILABLE ; 
 int MBEDTLS_ERR_PKCS5_INVALID_FORMAT ; 
 int /*<<< orphan*/  MBEDTLS_MD_SHA1 ; 
 scalar_t__ MBEDTLS_OID_CMP (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  MBEDTLS_OID_HMAC_SHA1 ; 
 int mbedtls_asn1_get_alg_null (unsigned char**,unsigned char const*,TYPE_1__*) ; 
 int mbedtls_asn1_get_int (unsigned char**,unsigned char const*,int*) ; 
 int mbedtls_asn1_get_tag (unsigned char**,unsigned char const*,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pkcs5_parse_pbkdf2_params( const mbedtls_asn1_buf *params,
                                      mbedtls_asn1_buf *salt, int *iterations,
                                      int *keylen, mbedtls_md_type_t *md_type )
{
    int ret;
    mbedtls_asn1_buf prf_alg_oid;
    unsigned char *p = params->p;
    const unsigned char *end = params->p + params->len;

    if( params->tag != ( MBEDTLS_ASN1_CONSTRUCTED | MBEDTLS_ASN1_SEQUENCE ) )
        return( MBEDTLS_ERR_PKCS5_INVALID_FORMAT +
                MBEDTLS_ERR_ASN1_UNEXPECTED_TAG );
    /*
     *  PBKDF2-params ::= SEQUENCE {
     *    salt              OCTET STRING,
     *    iterationCount    INTEGER,
     *    keyLength         INTEGER OPTIONAL
     *    prf               AlgorithmIdentifier DEFAULT algid-hmacWithSHA1
     *  }
     *
     */
    if( ( ret = mbedtls_asn1_get_tag( &p, end, &salt->len, MBEDTLS_ASN1_OCTET_STRING ) ) != 0 )
        return( MBEDTLS_ERR_PKCS5_INVALID_FORMAT + ret );

    salt->p = p;
    p += salt->len;

    if( ( ret = mbedtls_asn1_get_int( &p, end, iterations ) ) != 0 )
        return( MBEDTLS_ERR_PKCS5_INVALID_FORMAT + ret );

    if( p == end )
        return( 0 );

    if( ( ret = mbedtls_asn1_get_int( &p, end, keylen ) ) != 0 )
    {
        if( ret != MBEDTLS_ERR_ASN1_UNEXPECTED_TAG )
            return( MBEDTLS_ERR_PKCS5_INVALID_FORMAT + ret );
    }

    if( p == end )
        return( 0 );

    if( ( ret = mbedtls_asn1_get_alg_null( &p, end, &prf_alg_oid ) ) != 0 )
        return( MBEDTLS_ERR_PKCS5_INVALID_FORMAT + ret );

    if( MBEDTLS_OID_CMP( MBEDTLS_OID_HMAC_SHA1, &prf_alg_oid ) != 0 )
        return( MBEDTLS_ERR_PKCS5_FEATURE_UNAVAILABLE );

    *md_type = MBEDTLS_MD_SHA1;

    if( p != end )
        return( MBEDTLS_ERR_PKCS5_INVALID_FORMAT +
                MBEDTLS_ERR_ASN1_LENGTH_MISMATCH );

    return( 0 );
}