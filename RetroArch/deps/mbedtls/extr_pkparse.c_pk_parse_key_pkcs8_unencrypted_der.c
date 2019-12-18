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
typedef  scalar_t__ mbedtls_pk_type_t ;
typedef  int /*<<< orphan*/  mbedtls_pk_info_t ;
typedef  int /*<<< orphan*/  mbedtls_pk_context ;
typedef  int /*<<< orphan*/  mbedtls_asn1_buf ;
struct TYPE_3__ {int /*<<< orphan*/  grp; } ;

/* Variables and functions */
 int MBEDTLS_ASN1_CONSTRUCTED ; 
 int MBEDTLS_ASN1_OCTET_STRING ; 
 int MBEDTLS_ASN1_SEQUENCE ; 
 int MBEDTLS_ERR_ASN1_OUT_OF_DATA ; 
 int MBEDTLS_ERR_PK_KEY_INVALID_FORMAT ; 
 int MBEDTLS_ERR_PK_KEY_INVALID_VERSION ; 
 int MBEDTLS_ERR_PK_UNKNOWN_PK_ALG ; 
 scalar_t__ MBEDTLS_PK_ECKEY ; 
 scalar_t__ MBEDTLS_PK_ECKEY_DH ; 
 scalar_t__ MBEDTLS_PK_NONE ; 
 scalar_t__ MBEDTLS_PK_RSA ; 
 int mbedtls_asn1_get_int (unsigned char**,unsigned char*,int*) ; 
 int mbedtls_asn1_get_tag (unsigned char**,unsigned char*,size_t*,int) ; 
 TYPE_1__* mbedtls_pk_ec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_pk_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mbedtls_pk_info_from_type (scalar_t__) ; 
 int /*<<< orphan*/  mbedtls_pk_rsa (int /*<<< orphan*/ ) ; 
 int mbedtls_pk_setup (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int pk_get_pk_alg (unsigned char**,unsigned char*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int pk_parse_key_pkcs1_der (int /*<<< orphan*/ ,unsigned char*,size_t) ; 
 int pk_parse_key_sec1_der (TYPE_1__*,unsigned char*,size_t) ; 
 int pk_use_ecparams (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pk_parse_key_pkcs8_unencrypted_der(
                                    mbedtls_pk_context *pk,
                                    const unsigned char* key,
                                    size_t keylen )
{
    int ret, version;
    size_t len;
    mbedtls_asn1_buf params;
    unsigned char *p = (unsigned char *) key;
    unsigned char *end = p + keylen;
    mbedtls_pk_type_t pk_alg = MBEDTLS_PK_NONE;
    const mbedtls_pk_info_t *pk_info;

    /*
     * This function parses the PrivatKeyInfo object (PKCS#8 v1.2 = RFC 5208)
     *
     *    PrivateKeyInfo ::= SEQUENCE {
     *      version                   Version,
     *      privateKeyAlgorithm       PrivateKeyAlgorithmIdentifier,
     *      privateKey                PrivateKey,
     *      attributes           [0]  IMPLICIT Attributes OPTIONAL }
     *
     *    Version ::= INTEGER
     *    PrivateKeyAlgorithmIdentifier ::= AlgorithmIdentifier
     *    PrivateKey ::= OCTET STRING
     *
     *  The PrivateKey OCTET STRING is a SEC1 ECPrivateKey
     */

    if( ( ret = mbedtls_asn1_get_tag( &p, end, &len,
            MBEDTLS_ASN1_CONSTRUCTED | MBEDTLS_ASN1_SEQUENCE ) ) != 0 )
    {
        return( MBEDTLS_ERR_PK_KEY_INVALID_FORMAT + ret );
    }

    end = p + len;

    if( ( ret = mbedtls_asn1_get_int( &p, end, &version ) ) != 0 )
        return( MBEDTLS_ERR_PK_KEY_INVALID_FORMAT + ret );

    if( version != 0 )
        return( MBEDTLS_ERR_PK_KEY_INVALID_VERSION + ret );

    if( ( ret = pk_get_pk_alg( &p, end, &pk_alg, &params ) ) != 0 )
        return( MBEDTLS_ERR_PK_KEY_INVALID_FORMAT + ret );

    if( ( ret = mbedtls_asn1_get_tag( &p, end, &len, MBEDTLS_ASN1_OCTET_STRING ) ) != 0 )
        return( MBEDTLS_ERR_PK_KEY_INVALID_FORMAT + ret );

    if( len < 1 )
        return( MBEDTLS_ERR_PK_KEY_INVALID_FORMAT +
                MBEDTLS_ERR_ASN1_OUT_OF_DATA );

    if( ( pk_info = mbedtls_pk_info_from_type( pk_alg ) ) == NULL )
        return( MBEDTLS_ERR_PK_UNKNOWN_PK_ALG );

    if( ( ret = mbedtls_pk_setup( pk, pk_info ) ) != 0 )
        return( ret );

#if defined(MBEDTLS_RSA_C)
    if( pk_alg == MBEDTLS_PK_RSA )
    {
        if( ( ret = pk_parse_key_pkcs1_der( mbedtls_pk_rsa( *pk ), p, len ) ) != 0 )
        {
            mbedtls_pk_free( pk );
            return( ret );
        }
    } else
#endif /* MBEDTLS_RSA_C */
#if defined(MBEDTLS_ECP_C)
    if( pk_alg == MBEDTLS_PK_ECKEY || pk_alg == MBEDTLS_PK_ECKEY_DH )
    {
        if( ( ret = pk_use_ecparams( &params, &mbedtls_pk_ec( *pk )->grp ) ) != 0 ||
            ( ret = pk_parse_key_sec1_der( mbedtls_pk_ec( *pk ), p, len )  ) != 0 )
        {
            mbedtls_pk_free( pk );
            return( ret );
        }
    } else
#endif /* MBEDTLS_ECP_C */
        return( MBEDTLS_ERR_PK_UNKNOWN_PK_ALG );

    return( 0 );
}