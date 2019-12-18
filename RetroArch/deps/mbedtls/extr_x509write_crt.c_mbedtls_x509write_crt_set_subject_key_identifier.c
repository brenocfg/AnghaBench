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
struct TYPE_4__ {int /*<<< orphan*/  subject_key; } ;
typedef  TYPE_1__ mbedtls_x509write_cert ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  MBEDTLS_ASN1_CHK_ADD (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MBEDTLS_ASN1_OCTET_STRING ; 
 int MBEDTLS_MPI_MAX_SIZE ; 
 int /*<<< orphan*/  MBEDTLS_OID_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MBEDTLS_OID_SUBJECT_KEY_IDENTIFIER ; 
 int /*<<< orphan*/  mbedtls_asn1_write_len (unsigned char**,unsigned char*,size_t) ; 
 int /*<<< orphan*/  mbedtls_asn1_write_tag (unsigned char**,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_pk_write_pubkey (unsigned char**,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_sha1 (unsigned char*,size_t,unsigned char*) ; 
 int mbedtls_x509write_crt_set_extension (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,size_t) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 

int mbedtls_x509write_crt_set_subject_key_identifier( mbedtls_x509write_cert *ctx )
{
    int ret;
    unsigned char buf[MBEDTLS_MPI_MAX_SIZE * 2 + 20]; /* tag, length + 2xMPI */
    unsigned char *c = buf + sizeof(buf);
    size_t len = 0;

    memset( buf, 0, sizeof(buf) );
    MBEDTLS_ASN1_CHK_ADD( len, mbedtls_pk_write_pubkey( &c, buf, ctx->subject_key ) );

    mbedtls_sha1( buf + sizeof(buf) - len, len, buf + sizeof(buf) - 20 );
    c = buf + sizeof(buf) - 20;
    len = 20;

    MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_len( &c, buf, len ) );
    MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_tag( &c, buf, MBEDTLS_ASN1_OCTET_STRING ) );

    return mbedtls_x509write_crt_set_extension( ctx, MBEDTLS_OID_SUBJECT_KEY_IDENTIFIER,
                                        MBEDTLS_OID_SIZE( MBEDTLS_OID_SUBJECT_KEY_IDENTIFIER ),
                                        0, buf + sizeof(buf) - len, len );
}