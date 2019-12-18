#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {unsigned char* p; size_t len; } ;
struct TYPE_9__ {unsigned char* p; int len; } ;
struct TYPE_8__ {unsigned char* p; int len; } ;
struct TYPE_11__ {int version; int /*<<< orphan*/  sig; int /*<<< orphan*/  sig_opts; int /*<<< orphan*/  sig_pk; int /*<<< orphan*/  sig_md; int /*<<< orphan*/  sig_oid; TYPE_3__ raw; int /*<<< orphan*/  pk; TYPE_2__ subject_raw; int /*<<< orphan*/  subject; TYPE_1__ cri; } ;
typedef  TYPE_4__ mbedtls_x509_csr ;
typedef  int /*<<< orphan*/  mbedtls_x509_buf ;

/* Variables and functions */
 int MBEDTLS_ASN1_CONSTRUCTED ; 
 int MBEDTLS_ASN1_CONTEXT_SPECIFIC ; 
 int MBEDTLS_ASN1_SEQUENCE ; 
 int MBEDTLS_ERR_ASN1_LENGTH_MISMATCH ; 
 int MBEDTLS_ERR_X509_ALLOC_FAILED ; 
 int MBEDTLS_ERR_X509_BAD_INPUT_DATA ; 
 int MBEDTLS_ERR_X509_INVALID_FORMAT ; 
 int MBEDTLS_ERR_X509_UNKNOWN_SIG_ALG ; 
 int MBEDTLS_ERR_X509_UNKNOWN_VERSION ; 
 int mbedtls_asn1_get_tag (unsigned char**,unsigned char*,size_t*,int) ; 
 unsigned char* mbedtls_calloc (int,size_t) ; 
 int mbedtls_pk_parse_subpubkey (unsigned char**,unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_x509_csr_free (TYPE_4__*) ; 
 int /*<<< orphan*/  mbedtls_x509_csr_init (TYPE_4__*) ; 
 int mbedtls_x509_get_alg (unsigned char**,unsigned char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int mbedtls_x509_get_name (unsigned char**,unsigned char*,int /*<<< orphan*/ *) ; 
 int mbedtls_x509_get_sig (unsigned char**,unsigned char*,int /*<<< orphan*/ *) ; 
 int mbedtls_x509_get_sig_alg (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int x509_csr_get_version (unsigned char**,unsigned char*,int*) ; 

int mbedtls_x509_csr_parse_der( mbedtls_x509_csr *csr,
                        const unsigned char *buf, size_t buflen )
{
    int ret;
    size_t len;
    unsigned char *p, *end;
    mbedtls_x509_buf sig_params;

    memset( &sig_params, 0, sizeof( mbedtls_x509_buf ) );

    /*
     * Check for valid input
     */
    if( csr == NULL || buf == NULL || buflen == 0 )
        return( MBEDTLS_ERR_X509_BAD_INPUT_DATA );

    mbedtls_x509_csr_init( csr );

    /*
     * first copy the raw DER data
     */
    p = mbedtls_calloc( 1, len = buflen );

    if( p == NULL )
        return( MBEDTLS_ERR_X509_ALLOC_FAILED );

    memcpy( p, buf, buflen );

    csr->raw.p = p;
    csr->raw.len = len;
    end = p + len;

    /*
     *  CertificationRequest ::= SEQUENCE {
     *       certificationRequestInfo CertificationRequestInfo,
     *       signatureAlgorithm AlgorithmIdentifier,
     *       signature          BIT STRING
     *  }
     */
    if( ( ret = mbedtls_asn1_get_tag( &p, end, &len,
            MBEDTLS_ASN1_CONSTRUCTED | MBEDTLS_ASN1_SEQUENCE ) ) != 0 )
    {
        mbedtls_x509_csr_free( csr );
        return( MBEDTLS_ERR_X509_INVALID_FORMAT );
    }

    if( len != (size_t) ( end - p ) )
    {
        mbedtls_x509_csr_free( csr );
        return( MBEDTLS_ERR_X509_INVALID_FORMAT +
                MBEDTLS_ERR_ASN1_LENGTH_MISMATCH );
    }

    /*
     *  CertificationRequestInfo ::= SEQUENCE {
     */
    csr->cri.p = p;

    if( ( ret = mbedtls_asn1_get_tag( &p, end, &len,
            MBEDTLS_ASN1_CONSTRUCTED | MBEDTLS_ASN1_SEQUENCE ) ) != 0 )
    {
        mbedtls_x509_csr_free( csr );
        return( MBEDTLS_ERR_X509_INVALID_FORMAT + ret );
    }

    end = p + len;
    csr->cri.len = end - csr->cri.p;

    /*
     *  Version  ::=  INTEGER {  v1(0) }
     */
    if( ( ret = x509_csr_get_version( &p, end, &csr->version ) ) != 0 )
    {
        mbedtls_x509_csr_free( csr );
        return( ret );
    }

    csr->version++;

    if( csr->version != 1 )
    {
        mbedtls_x509_csr_free( csr );
        return( MBEDTLS_ERR_X509_UNKNOWN_VERSION );
    }

    /*
     *  subject               Name
     */
    csr->subject_raw.p = p;

    if( ( ret = mbedtls_asn1_get_tag( &p, end, &len,
            MBEDTLS_ASN1_CONSTRUCTED | MBEDTLS_ASN1_SEQUENCE ) ) != 0 )
    {
        mbedtls_x509_csr_free( csr );
        return( MBEDTLS_ERR_X509_INVALID_FORMAT + ret );
    }

    if( ( ret = mbedtls_x509_get_name( &p, p + len, &csr->subject ) ) != 0 )
    {
        mbedtls_x509_csr_free( csr );
        return( ret );
    }

    csr->subject_raw.len = p - csr->subject_raw.p;

    /*
     *  subjectPKInfo SubjectPublicKeyInfo
     */
    if( ( ret = mbedtls_pk_parse_subpubkey( &p, end, &csr->pk ) ) != 0 )
    {
        mbedtls_x509_csr_free( csr );
        return( ret );
    }

    /*
     *  attributes    [0] Attributes
     *
     *  The list of possible attributes is open-ended, though RFC 2985
     *  (PKCS#9) defines a few in section 5.4. We currently don't support any,
     *  so we just ignore them. This is a safe thing to do as the worst thing
     *  that could happen is that we issue a certificate that does not match
     *  the requester's expectations - this cannot cause a violation of our
     *  signature policies.
     */
    if( ( ret = mbedtls_asn1_get_tag( &p, end, &len,
            MBEDTLS_ASN1_CONSTRUCTED | MBEDTLS_ASN1_CONTEXT_SPECIFIC ) ) != 0 )
    {
        mbedtls_x509_csr_free( csr );
        return( MBEDTLS_ERR_X509_INVALID_FORMAT + ret );
    }

    p += len;

    end = csr->raw.p + csr->raw.len;

    /*
     *  signatureAlgorithm   AlgorithmIdentifier,
     *  signature            BIT STRING
     */
    if( ( ret = mbedtls_x509_get_alg( &p, end, &csr->sig_oid, &sig_params ) ) != 0 )
    {
        mbedtls_x509_csr_free( csr );
        return( ret );
    }

    if( ( ret = mbedtls_x509_get_sig_alg( &csr->sig_oid, &sig_params,
                                  &csr->sig_md, &csr->sig_pk,
                                  &csr->sig_opts ) ) != 0 )
    {
        mbedtls_x509_csr_free( csr );
        return( MBEDTLS_ERR_X509_UNKNOWN_SIG_ALG );
    }

    if( ( ret = mbedtls_x509_get_sig( &p, end, &csr->sig ) ) != 0 )
    {
        mbedtls_x509_csr_free( csr );
        return( ret );
    }

    if( p != end )
    {
        mbedtls_x509_csr_free( csr );
        return( MBEDTLS_ERR_X509_INVALID_FORMAT +
                MBEDTLS_ERR_ASN1_LENGTH_MISMATCH );
    }

    return( 0 );
}