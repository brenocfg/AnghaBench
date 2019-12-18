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
 int /*<<< orphan*/  MBEDTLS_ASN1_OID ; 
 int /*<<< orphan*/  mbedtls_asn1_write_len (unsigned char**,unsigned char*,size_t) ; 
 int /*<<< orphan*/  mbedtls_asn1_write_raw_buffer (unsigned char**,unsigned char*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  mbedtls_asn1_write_tag (unsigned char**,unsigned char*,int /*<<< orphan*/ ) ; 

int mbedtls_asn1_write_oid( unsigned char **p, unsigned char *start,
                    const char *oid, size_t oid_len )
{
    int ret;
    size_t len = 0;

    MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_raw_buffer( p, start,
                                  (const unsigned char *) oid, oid_len ) );
    MBEDTLS_ASN1_CHK_ADD( len , mbedtls_asn1_write_len( p, start, len ) );
    MBEDTLS_ASN1_CHK_ADD( len , mbedtls_asn1_write_tag( p, start, MBEDTLS_ASN1_OID ) );

    return( (int) len );
}