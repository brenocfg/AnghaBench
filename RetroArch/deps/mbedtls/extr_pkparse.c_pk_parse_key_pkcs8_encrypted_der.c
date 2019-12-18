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
typedef  int /*<<< orphan*/  mbedtls_md_type_t ;
typedef  int /*<<< orphan*/  mbedtls_cipher_type_t ;
typedef  int /*<<< orphan*/  mbedtls_asn1_buf ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 unsigned char MBEDTLS_ASN1_CONSTRUCTED ; 
 unsigned char MBEDTLS_ASN1_OCTET_STRING ; 
 unsigned char MBEDTLS_ASN1_SEQUENCE ; 
 int MBEDTLS_ERR_PKCS12_PASSWORD_MISMATCH ; 
 int MBEDTLS_ERR_PKCS5_PASSWORD_MISMATCH ; 
 int MBEDTLS_ERR_PK_BAD_INPUT_DATA ; 
 int MBEDTLS_ERR_PK_FEATURE_UNAVAILABLE ; 
 int MBEDTLS_ERR_PK_KEY_INVALID_FORMAT ; 
 int MBEDTLS_ERR_PK_PASSWORD_MISMATCH ; 
 int MBEDTLS_ERR_PK_PASSWORD_REQUIRED ; 
 scalar_t__ MBEDTLS_OID_CMP (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MBEDTLS_OID_PKCS12_PBE_SHA1_RC4_128 ; 
 int /*<<< orphan*/  MBEDTLS_OID_PKCS5_PBES2 ; 
 int /*<<< orphan*/  MBEDTLS_PKCS12_PBE_DECRYPT ; 
 int /*<<< orphan*/  MBEDTLS_PKCS5_DECRYPT ; 
 int mbedtls_asn1_get_alg (unsigned char**,unsigned char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int mbedtls_asn1_get_tag (unsigned char**,unsigned char*,size_t*,unsigned char) ; 
 scalar_t__ mbedtls_oid_get_pkcs12_pbe_alg (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int mbedtls_pkcs12_pbe (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char const*,size_t,unsigned char*,size_t,unsigned char*) ; 
 int mbedtls_pkcs12_pbe_sha1_rc4_128 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char const*,size_t,unsigned char*,size_t,unsigned char*) ; 
 int mbedtls_pkcs5_pbes2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char const*,size_t,unsigned char*,size_t,unsigned char*) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int pk_parse_key_pkcs8_unencrypted_der (int /*<<< orphan*/ *,unsigned char*,size_t) ; 

__attribute__((used)) static int pk_parse_key_pkcs8_encrypted_der(
                                    mbedtls_pk_context *pk,
                                    const unsigned char *key, size_t keylen,
                                    const unsigned char *pwd, size_t pwdlen )
{
    int ret, decrypted = 0;
    size_t len;
    unsigned char buf[2048];
    unsigned char *p, *end;
    mbedtls_asn1_buf pbe_alg_oid, pbe_params;
#if defined(MBEDTLS_PKCS12_C)
    mbedtls_cipher_type_t cipher_alg;
    mbedtls_md_type_t md_alg;
#endif

    memset( buf, 0, sizeof( buf ) );

    p = (unsigned char *) key;
    end = p + keylen;

    if( pwdlen == 0 )
        return( MBEDTLS_ERR_PK_PASSWORD_REQUIRED );

    /*
     * This function parses the EncryptedPrivatKeyInfo object (PKCS#8)
     *
     *  EncryptedPrivateKeyInfo ::= SEQUENCE {
     *    encryptionAlgorithm  EncryptionAlgorithmIdentifier,
     *    encryptedData        EncryptedData
     *  }
     *
     *  EncryptionAlgorithmIdentifier ::= AlgorithmIdentifier
     *
     *  EncryptedData ::= OCTET STRING
     *
     *  The EncryptedData OCTET STRING is a PKCS#8 PrivateKeyInfo
     */
    if( ( ret = mbedtls_asn1_get_tag( &p, end, &len,
            MBEDTLS_ASN1_CONSTRUCTED | MBEDTLS_ASN1_SEQUENCE ) ) != 0 )
    {
        return( MBEDTLS_ERR_PK_KEY_INVALID_FORMAT + ret );
    }

    end = p + len;

    if( ( ret = mbedtls_asn1_get_alg( &p, end, &pbe_alg_oid, &pbe_params ) ) != 0 )
        return( MBEDTLS_ERR_PK_KEY_INVALID_FORMAT + ret );

    if( ( ret = mbedtls_asn1_get_tag( &p, end, &len, MBEDTLS_ASN1_OCTET_STRING ) ) != 0 )
        return( MBEDTLS_ERR_PK_KEY_INVALID_FORMAT + ret );

    if( len > sizeof( buf ) )
        return( MBEDTLS_ERR_PK_BAD_INPUT_DATA );

    /*
     * Decrypt EncryptedData with appropriate PDE
     */
#if defined(MBEDTLS_PKCS12_C)
    if( mbedtls_oid_get_pkcs12_pbe_alg( &pbe_alg_oid, &md_alg, &cipher_alg ) == 0 )
    {
        if( ( ret = mbedtls_pkcs12_pbe( &pbe_params, MBEDTLS_PKCS12_PBE_DECRYPT,
                                cipher_alg, md_alg,
                                pwd, pwdlen, p, len, buf ) ) != 0 )
        {
            if( ret == MBEDTLS_ERR_PKCS12_PASSWORD_MISMATCH )
                return( MBEDTLS_ERR_PK_PASSWORD_MISMATCH );

            return( ret );
        }

        decrypted = 1;
    }
    else if( MBEDTLS_OID_CMP( MBEDTLS_OID_PKCS12_PBE_SHA1_RC4_128, &pbe_alg_oid ) == 0 )
    {
        if( ( ret = mbedtls_pkcs12_pbe_sha1_rc4_128( &pbe_params,
                                             MBEDTLS_PKCS12_PBE_DECRYPT,
                                             pwd, pwdlen,
                                             p, len, buf ) ) != 0 )
        {
            return( ret );
        }

        /* Best guess for password mismatch when using RC4. If first tag is
         * not MBEDTLS_ASN1_CONSTRUCTED | MBEDTLS_ASN1_SEQUENCE
         */
        if( *buf != ( MBEDTLS_ASN1_CONSTRUCTED | MBEDTLS_ASN1_SEQUENCE ) )
            return( MBEDTLS_ERR_PK_PASSWORD_MISMATCH );

        decrypted = 1;
    }
    else
#endif /* MBEDTLS_PKCS12_C */
#if defined(MBEDTLS_PKCS5_C)
    if( MBEDTLS_OID_CMP( MBEDTLS_OID_PKCS5_PBES2, &pbe_alg_oid ) == 0 )
    {
        if( ( ret = mbedtls_pkcs5_pbes2( &pbe_params, MBEDTLS_PKCS5_DECRYPT, pwd, pwdlen,
                                  p, len, buf ) ) != 0 )
        {
            if( ret == MBEDTLS_ERR_PKCS5_PASSWORD_MISMATCH )
                return( MBEDTLS_ERR_PK_PASSWORD_MISMATCH );

            return( ret );
        }

        decrypted = 1;
    }
    else
#endif /* MBEDTLS_PKCS5_C */
    {
        ((void) pwd);
    }

    if( decrypted == 0 )
        return( MBEDTLS_ERR_PK_FEATURE_UNAVAILABLE );

    return( pk_parse_key_pkcs8_unencrypted_der( pk, buf, len ) );
}