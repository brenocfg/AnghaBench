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
 int /*<<< orphan*/  MBEDTLS_ASN1_CHK_ADD (size_t,int /*<<< orphan*/ ) ; 
 int MBEDTLS_ASN1_CONSTRUCTED ; 
 int MBEDTLS_ASN1_SEQUENCE ; 
 int MBEDTLS_ASN1_SET ; 
 int /*<<< orphan*/  MBEDTLS_OID_PKCS9_EMAIL ; 
 size_t MBEDTLS_OID_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_asn1_write_ia5_string (unsigned char**,unsigned char*,char const*,size_t) ; 
 int /*<<< orphan*/  mbedtls_asn1_write_len (unsigned char**,unsigned char*,size_t) ; 
 int /*<<< orphan*/  mbedtls_asn1_write_oid (unsigned char**,unsigned char*,char const*,size_t) ; 
 int /*<<< orphan*/  mbedtls_asn1_write_printable_string (unsigned char**,unsigned char*,char const*,size_t) ; 
 int /*<<< orphan*/  mbedtls_asn1_write_tag (unsigned char**,unsigned char*,int) ; 
 scalar_t__ memcmp (char const*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int x509_write_name( unsigned char **p, unsigned char *start,
                            const char *oid, size_t oid_len,
                            const unsigned char *name, size_t name_len )
{
    int ret;
    size_t len = 0;

    /* Write PrintableString for all except MBEDTLS_OID_PKCS9_EMAIL */
    if( MBEDTLS_OID_SIZE( MBEDTLS_OID_PKCS9_EMAIL ) == oid_len &&
        memcmp( oid, MBEDTLS_OID_PKCS9_EMAIL, oid_len ) == 0 )
    {
        MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_ia5_string( p, start,
                                                  (const char *) name,
                                                  name_len ) );
    }
    else
    {
        MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_printable_string( p, start,
                                                        (const char *) name,
                                                        name_len ) );
    }

    /* Write OID */
    MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_oid( p, start, oid, oid_len ) );

    MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_len( p, start, len ) );
    MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_tag( p, start, MBEDTLS_ASN1_CONSTRUCTED |
                                                 MBEDTLS_ASN1_SEQUENCE ) );

    MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_len( p, start, len ) );
    MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_tag( p, start, MBEDTLS_ASN1_CONSTRUCTED |
                                                 MBEDTLS_ASN1_SET ) );

    return( (int) len );
}