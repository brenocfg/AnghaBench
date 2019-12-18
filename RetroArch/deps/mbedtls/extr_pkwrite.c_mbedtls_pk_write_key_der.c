#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  N; int /*<<< orphan*/  E; int /*<<< orphan*/  D; int /*<<< orphan*/  P; int /*<<< orphan*/  Q; int /*<<< orphan*/  DP; int /*<<< orphan*/  DQ; int /*<<< orphan*/  QP; } ;
typedef  TYPE_1__ mbedtls_rsa_context ;
typedef  int /*<<< orphan*/  mbedtls_pk_context ;
struct TYPE_8__ {int /*<<< orphan*/  d; } ;
typedef  TYPE_2__ mbedtls_ecp_keypair ;

/* Variables and functions */
 int MBEDTLS_ASN1_BIT_STRING ; 
 int /*<<< orphan*/  MBEDTLS_ASN1_CHK_ADD (size_t,int /*<<< orphan*/ ) ; 
 int MBEDTLS_ASN1_CONSTRUCTED ; 
 int MBEDTLS_ASN1_CONTEXT_SPECIFIC ; 
 unsigned char MBEDTLS_ASN1_OCTET_STRING ; 
 int MBEDTLS_ASN1_SEQUENCE ; 
 int MBEDTLS_ERR_ASN1_BUF_TOO_SMALL ; 
 int MBEDTLS_ERR_PK_FEATURE_UNAVAILABLE ; 
 scalar_t__ MBEDTLS_PK_ECKEY ; 
 scalar_t__ MBEDTLS_PK_RSA ; 
 int /*<<< orphan*/  mbedtls_asn1_write_int (unsigned char**,unsigned char*,int) ; 
 int /*<<< orphan*/  mbedtls_asn1_write_len (unsigned char**,unsigned char*,size_t) ; 
 int /*<<< orphan*/  mbedtls_asn1_write_mpi (unsigned char**,unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_asn1_write_tag (unsigned char**,unsigned char*,int) ; 
 TYPE_2__* mbedtls_pk_ec (int /*<<< orphan*/ ) ; 
 scalar_t__ mbedtls_pk_get_type (int /*<<< orphan*/ *) ; 
 TYPE_1__* mbedtls_pk_rsa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pk_write_ec_param (unsigned char**,unsigned char*,TYPE_2__*) ; 
 int /*<<< orphan*/  pk_write_ec_pubkey (unsigned char**,unsigned char*,TYPE_2__*) ; 

int mbedtls_pk_write_key_der( mbedtls_pk_context *key, unsigned char *buf, size_t size )
{
    int ret;
    unsigned char *c = buf + size;
    size_t len = 0;

#if defined(MBEDTLS_RSA_C)
    if( mbedtls_pk_get_type( key ) == MBEDTLS_PK_RSA )
    {
        mbedtls_rsa_context *rsa = mbedtls_pk_rsa( *key );

        MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_mpi( &c, buf, &rsa->QP ) );
        MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_mpi( &c, buf, &rsa->DQ ) );
        MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_mpi( &c, buf, &rsa->DP ) );
        MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_mpi( &c, buf, &rsa->Q ) );
        MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_mpi( &c, buf, &rsa->P ) );
        MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_mpi( &c, buf, &rsa->D ) );
        MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_mpi( &c, buf, &rsa->E ) );
        MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_mpi( &c, buf, &rsa->N ) );
        MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_int( &c, buf, 0 ) );

        MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_len( &c, buf, len ) );
        MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_tag( &c, buf, MBEDTLS_ASN1_CONSTRUCTED |
                                                    MBEDTLS_ASN1_SEQUENCE ) );
    }
    else
#endif /* MBEDTLS_RSA_C */
#if defined(MBEDTLS_ECP_C)
    if( mbedtls_pk_get_type( key ) == MBEDTLS_PK_ECKEY )
    {
        mbedtls_ecp_keypair *ec = mbedtls_pk_ec( *key );
        size_t pub_len = 0, par_len = 0;

        /*
         * RFC 5915, or SEC1 Appendix C.4
         *
         * ECPrivateKey ::= SEQUENCE {
         *      version        INTEGER { ecPrivkeyVer1(1) } (ecPrivkeyVer1),
         *      privateKey     OCTET STRING,
         *      parameters [0] ECParameters {{ NamedCurve }} OPTIONAL,
         *      publicKey  [1] BIT STRING OPTIONAL
         *    }
         */

        /* publicKey */
        MBEDTLS_ASN1_CHK_ADD( pub_len, pk_write_ec_pubkey( &c, buf, ec ) );

        if( c - buf < 1 )
            return( MBEDTLS_ERR_ASN1_BUF_TOO_SMALL );
        *--c = 0;
        pub_len += 1;

        MBEDTLS_ASN1_CHK_ADD( pub_len, mbedtls_asn1_write_len( &c, buf, pub_len ) );
        MBEDTLS_ASN1_CHK_ADD( pub_len, mbedtls_asn1_write_tag( &c, buf, MBEDTLS_ASN1_BIT_STRING ) );

        MBEDTLS_ASN1_CHK_ADD( pub_len, mbedtls_asn1_write_len( &c, buf, pub_len ) );
        MBEDTLS_ASN1_CHK_ADD( pub_len, mbedtls_asn1_write_tag( &c, buf,
                            MBEDTLS_ASN1_CONTEXT_SPECIFIC | MBEDTLS_ASN1_CONSTRUCTED | 1 ) );
        len += pub_len;

        /* parameters */
        MBEDTLS_ASN1_CHK_ADD( par_len, pk_write_ec_param( &c, buf, ec ) );

        MBEDTLS_ASN1_CHK_ADD( par_len, mbedtls_asn1_write_len( &c, buf, par_len ) );
        MBEDTLS_ASN1_CHK_ADD( par_len, mbedtls_asn1_write_tag( &c, buf,
                            MBEDTLS_ASN1_CONTEXT_SPECIFIC | MBEDTLS_ASN1_CONSTRUCTED | 0 ) );
        len += par_len;

        /* privateKey: write as MPI then fix tag */
        MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_mpi( &c, buf, &ec->d ) );
        *c = MBEDTLS_ASN1_OCTET_STRING;

        /* version */
        MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_int( &c, buf, 1 ) );

        MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_len( &c, buf, len ) );
        MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_tag( &c, buf, MBEDTLS_ASN1_CONSTRUCTED |
                                                    MBEDTLS_ASN1_SEQUENCE ) );
    }
    else
#endif /* MBEDTLS_ECP_C */
        return( MBEDTLS_ERR_PK_FEATURE_UNAVAILABLE );

    return( (int) len );
}