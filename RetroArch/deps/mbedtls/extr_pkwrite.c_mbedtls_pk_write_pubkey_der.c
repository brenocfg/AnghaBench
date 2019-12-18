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
typedef  int /*<<< orphan*/  mbedtls_pk_context ;

/* Variables and functions */
 int MBEDTLS_ASN1_BIT_STRING ; 
 int /*<<< orphan*/  MBEDTLS_ASN1_CHK_ADD (size_t,int /*<<< orphan*/ ) ; 
 int MBEDTLS_ASN1_CONSTRUCTED ; 
 int MBEDTLS_ASN1_SEQUENCE ; 
 int MBEDTLS_ERR_ASN1_BUF_TOO_SMALL ; 
 scalar_t__ MBEDTLS_PK_ECKEY ; 
 int /*<<< orphan*/  mbedtls_asn1_write_algorithm_identifier (unsigned char**,unsigned char*,char const*,size_t,size_t) ; 
 int /*<<< orphan*/  mbedtls_asn1_write_len (unsigned char**,unsigned char*,size_t) ; 
 int /*<<< orphan*/  mbedtls_asn1_write_tag (unsigned char**,unsigned char*,int) ; 
 int mbedtls_oid_get_oid_by_pk_alg (scalar_t__,char const**,size_t*) ; 
 int /*<<< orphan*/  mbedtls_pk_ec (int /*<<< orphan*/ ) ; 
 scalar_t__ mbedtls_pk_get_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_pk_write_pubkey (unsigned char**,unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pk_write_ec_param (unsigned char**,unsigned char*,int /*<<< orphan*/ ) ; 

int mbedtls_pk_write_pubkey_der( mbedtls_pk_context *key, unsigned char *buf, size_t size )
{
    int ret;
    unsigned char *c;
    size_t len = 0, par_len = 0, oid_len;
    const char *oid;

    c = buf + size;

    MBEDTLS_ASN1_CHK_ADD( len, mbedtls_pk_write_pubkey( &c, buf, key ) );

    if( c - buf < 1 )
        return( MBEDTLS_ERR_ASN1_BUF_TOO_SMALL );

    /*
     *  SubjectPublicKeyInfo  ::=  SEQUENCE  {
     *       algorithm            AlgorithmIdentifier,
     *       subjectPublicKey     BIT STRING }
     */
    *--c = 0;
    len += 1;

    MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_len( &c, buf, len ) );
    MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_tag( &c, buf, MBEDTLS_ASN1_BIT_STRING ) );

    if( ( ret = mbedtls_oid_get_oid_by_pk_alg( mbedtls_pk_get_type( key ),
                                       &oid, &oid_len ) ) != 0 )
    {
        return( ret );
    }

#if defined(MBEDTLS_ECP_C)
    if( mbedtls_pk_get_type( key ) == MBEDTLS_PK_ECKEY )
    {
        MBEDTLS_ASN1_CHK_ADD( par_len, pk_write_ec_param( &c, buf, mbedtls_pk_ec( *key ) ) );
    }
#endif

    MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_algorithm_identifier( &c, buf, oid, oid_len,
                                                        par_len ) );

    MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_len( &c, buf, len ) );
    MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_tag( &c, buf, MBEDTLS_ASN1_CONSTRUCTED |
                                                MBEDTLS_ASN1_SEQUENCE ) );

    return( (int) len );
}