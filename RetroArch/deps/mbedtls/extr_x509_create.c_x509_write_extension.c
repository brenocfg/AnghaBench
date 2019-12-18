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
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__* p; int len; } ;
struct TYPE_5__ {scalar_t__* p; int len; } ;
struct TYPE_7__ {TYPE_2__ oid; TYPE_1__ val; } ;
typedef  TYPE_3__ mbedtls_asn1_named_data ;

/* Variables and functions */
 int /*<<< orphan*/  MBEDTLS_ASN1_CHK_ADD (size_t,int /*<<< orphan*/ ) ; 
 int MBEDTLS_ASN1_CONSTRUCTED ; 
 int MBEDTLS_ASN1_OCTET_STRING ; 
 int MBEDTLS_ASN1_OID ; 
 int MBEDTLS_ASN1_SEQUENCE ; 
 int /*<<< orphan*/  mbedtls_asn1_write_bool (unsigned char**,unsigned char*,int) ; 
 int /*<<< orphan*/  mbedtls_asn1_write_len (unsigned char**,unsigned char*,size_t) ; 
 int /*<<< orphan*/  mbedtls_asn1_write_raw_buffer (unsigned char**,unsigned char*,scalar_t__*,int) ; 
 int /*<<< orphan*/  mbedtls_asn1_write_tag (unsigned char**,unsigned char*,int) ; 

__attribute__((used)) static int x509_write_extension( unsigned char **p, unsigned char *start,
                                 mbedtls_asn1_named_data *ext )
{
    int ret;
    size_t len = 0;

    MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_raw_buffer( p, start, ext->val.p + 1,
                                              ext->val.len - 1 ) );
    MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_len( p, start, ext->val.len - 1 ) );
    MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_tag( p, start, MBEDTLS_ASN1_OCTET_STRING ) );

    if( ext->val.p[0] != 0 )
    {
        MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_bool( p, start, 1 ) );
    }

    MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_raw_buffer( p, start, ext->oid.p,
                                              ext->oid.len ) );
    MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_len( p, start, ext->oid.len ) );
    MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_tag( p, start, MBEDTLS_ASN1_OID ) );

    MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_len( p, start, len ) );
    MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_tag( p, start, MBEDTLS_ASN1_CONSTRUCTED |
                                                 MBEDTLS_ASN1_SEQUENCE ) );

    return( (int) len );
}