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
 int /*<<< orphan*/  mbedtls_asn1_write_len (unsigned char**,unsigned char*,size_t) ; 
 int /*<<< orphan*/  mbedtls_asn1_write_null (unsigned char**,unsigned char*) ; 
 int /*<<< orphan*/  mbedtls_asn1_write_oid (unsigned char**,unsigned char*,char const*,size_t) ; 
 int /*<<< orphan*/  mbedtls_asn1_write_tag (unsigned char**,unsigned char*,int) ; 

int mbedtls_asn1_write_algorithm_identifier( unsigned char **p, unsigned char *start,
                                     const char *oid, size_t oid_len,
                                     size_t par_len )
{
    int ret;
    size_t len = 0;

    if( par_len == 0 )
        MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_null( p, start ) );
    else
        len += par_len;

    MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_oid( p, start, oid, oid_len ) );

    MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_len( p, start, len ) );
    MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_tag( p, start,
                                       MBEDTLS_ASN1_CONSTRUCTED | MBEDTLS_ASN1_SEQUENCE ) );

    return( (int) len );
}