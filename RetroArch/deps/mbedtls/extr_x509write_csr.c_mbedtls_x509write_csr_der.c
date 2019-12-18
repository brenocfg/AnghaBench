#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp_buf ;
struct TYPE_3__ {int /*<<< orphan*/  md_alg; int /*<<< orphan*/  key; int /*<<< orphan*/  subject; int /*<<< orphan*/  extensions; } ;
typedef  TYPE_1__ mbedtls_x509write_csr ;
typedef  scalar_t__ mbedtls_pk_type_t ;

/* Variables and functions */
 int /*<<< orphan*/  MBEDTLS_ASN1_CHK_ADD (size_t,int /*<<< orphan*/ ) ; 
 int MBEDTLS_ASN1_CONSTRUCTED ; 
 int MBEDTLS_ASN1_CONTEXT_SPECIFIC ; 
 int MBEDTLS_ASN1_SEQUENCE ; 
 int MBEDTLS_ASN1_SET ; 
 int MBEDTLS_ERR_ASN1_BUF_TOO_SMALL ; 
 int MBEDTLS_MPI_MAX_SIZE ; 
 int /*<<< orphan*/  MBEDTLS_OID_PKCS9_CSR_EXT_REQ ; 
 int /*<<< orphan*/  MBEDTLS_OID_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ MBEDTLS_PK_ECDSA ; 
 scalar_t__ MBEDTLS_PK_ECKEY ; 
 int /*<<< orphan*/  mbedtls_asn1_write_int (unsigned char**,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_asn1_write_len (unsigned char**,unsigned char*,size_t) ; 
 int /*<<< orphan*/  mbedtls_asn1_write_oid (unsigned char**,unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_asn1_write_tag (unsigned char**,unsigned char*,int) ; 
 int /*<<< orphan*/  mbedtls_md (int /*<<< orphan*/ ,unsigned char*,size_t,unsigned char*) ; 
 int /*<<< orphan*/  mbedtls_md_info_from_type (int /*<<< orphan*/ ) ; 
 int mbedtls_oid_get_oid_by_sig_alg (scalar_t__,int /*<<< orphan*/ ,char const**,size_t*) ; 
 scalar_t__ mbedtls_pk_get_type (int /*<<< orphan*/ ) ; 
 int mbedtls_pk_sign (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ,unsigned char*,size_t*,int (*) (void*,unsigned char*,size_t),void*) ; 
 int /*<<< orphan*/  mbedtls_pk_write_pubkey_der (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  mbedtls_x509_write_extensions (unsigned char**,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_x509_write_names (unsigned char**,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_x509_write_sig (unsigned char**,unsigned char*,char const*,size_t,unsigned char*,size_t) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,size_t) ; 

int mbedtls_x509write_csr_der( mbedtls_x509write_csr *ctx, unsigned char *buf, size_t size,
                       int (*f_rng)(void *, unsigned char *, size_t),
                       void *p_rng )
{
    int ret;
    const char *sig_oid;
    size_t sig_oid_len = 0;
    unsigned char *c, *c2;
    unsigned char hash[64];
    unsigned char sig[MBEDTLS_MPI_MAX_SIZE];
    unsigned char tmp_buf[2048];
    size_t pub_len = 0, sig_and_oid_len = 0, sig_len;
    size_t len = 0;
    mbedtls_pk_type_t pk_alg;

    /*
     * Prepare data to be signed in tmp_buf
     */
    c = tmp_buf + sizeof( tmp_buf );

    MBEDTLS_ASN1_CHK_ADD( len, mbedtls_x509_write_extensions( &c, tmp_buf, ctx->extensions ) );

    if( len )
    {
        MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_len( &c, tmp_buf, len ) );
        MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_tag( &c, tmp_buf, MBEDTLS_ASN1_CONSTRUCTED |
                                                        MBEDTLS_ASN1_SEQUENCE ) );

        MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_len( &c, tmp_buf, len ) );
        MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_tag( &c, tmp_buf, MBEDTLS_ASN1_CONSTRUCTED |
                                                        MBEDTLS_ASN1_SET ) );

        MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_oid( &c, tmp_buf, MBEDTLS_OID_PKCS9_CSR_EXT_REQ,
                                          MBEDTLS_OID_SIZE( MBEDTLS_OID_PKCS9_CSR_EXT_REQ ) ) );

        MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_len( &c, tmp_buf, len ) );
        MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_tag( &c, tmp_buf, MBEDTLS_ASN1_CONSTRUCTED |
                                                        MBEDTLS_ASN1_SEQUENCE ) );
    }

    MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_len( &c, tmp_buf, len ) );
    MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_tag( &c, tmp_buf, MBEDTLS_ASN1_CONSTRUCTED |
                                                    MBEDTLS_ASN1_CONTEXT_SPECIFIC ) );

    MBEDTLS_ASN1_CHK_ADD( pub_len, mbedtls_pk_write_pubkey_der( ctx->key,
                                                tmp_buf, c - tmp_buf ) );
    c -= pub_len;
    len += pub_len;

    /*
     *  Subject  ::=  Name
     */
    MBEDTLS_ASN1_CHK_ADD( len, mbedtls_x509_write_names( &c, tmp_buf, ctx->subject ) );

    /*
     *  Version  ::=  INTEGER  {  v1(0), v2(1), v3(2)  }
     */
    MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_int( &c, tmp_buf, 0 ) );

    MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_len( &c, tmp_buf, len ) );
    MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_tag( &c, tmp_buf, MBEDTLS_ASN1_CONSTRUCTED |
                                                    MBEDTLS_ASN1_SEQUENCE ) );

    /*
     * Prepare signature
     */
    mbedtls_md( mbedtls_md_info_from_type( ctx->md_alg ), c, len, hash );

    pk_alg = mbedtls_pk_get_type( ctx->key );
    if( pk_alg == MBEDTLS_PK_ECKEY )
        pk_alg = MBEDTLS_PK_ECDSA;

    if( ( ret = mbedtls_pk_sign( ctx->key, ctx->md_alg, hash, 0, sig, &sig_len,
                         f_rng, p_rng ) ) != 0 ||
        ( ret = mbedtls_oid_get_oid_by_sig_alg( pk_alg, ctx->md_alg,
                                        &sig_oid, &sig_oid_len ) ) != 0 )
    {
        return( ret );
    }

    /*
     * Write data to output buffer
     */
    c2 = buf + size;
    MBEDTLS_ASN1_CHK_ADD( sig_and_oid_len, mbedtls_x509_write_sig( &c2, buf,
                                        sig_oid, sig_oid_len, sig, sig_len ) );

    if( len > (size_t)( c2 - buf ) )
        return( MBEDTLS_ERR_ASN1_BUF_TOO_SMALL );

    c2 -= len;
    memcpy( c2, c, len );

    len += sig_and_oid_len;
    MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_len( &c2, buf, len ) );
    MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_tag( &c2, buf, MBEDTLS_ASN1_CONSTRUCTED |
                                                 MBEDTLS_ASN1_SEQUENCE ) );

    return( (int) len );
}