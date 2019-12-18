#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mbedtls_pk_info_t ;
typedef  int /*<<< orphan*/  mbedtls_pk_context ;
struct TYPE_5__ {unsigned char const* buf; size_t buflen; } ;
typedef  TYPE_1__ mbedtls_pem_context ;

/* Variables and functions */
 int MBEDTLS_ERR_PEM_NO_HEADER_FOOTER_PRESENT ; 
 int MBEDTLS_ERR_PEM_PASSWORD_MISMATCH ; 
 int MBEDTLS_ERR_PEM_PASSWORD_REQUIRED ; 
 int MBEDTLS_ERR_PK_KEY_INVALID_FORMAT ; 
 int MBEDTLS_ERR_PK_PASSWORD_MISMATCH ; 
 int MBEDTLS_ERR_PK_PASSWORD_REQUIRED ; 
 int MBEDTLS_ERR_PK_UNKNOWN_PK_ALG ; 
 int /*<<< orphan*/  MBEDTLS_PK_ECKEY ; 
 int /*<<< orphan*/  MBEDTLS_PK_RSA ; 
 int /*<<< orphan*/  mbedtls_pem_free (TYPE_1__*) ; 
 int /*<<< orphan*/  mbedtls_pem_init (TYPE_1__*) ; 
 int mbedtls_pem_read_buffer (TYPE_1__*,char*,char*,unsigned char const*,unsigned char const*,size_t,size_t*) ; 
 int /*<<< orphan*/  mbedtls_pk_ec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_pk_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mbedtls_pk_info_from_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_pk_rsa (int /*<<< orphan*/ ) ; 
 int mbedtls_pk_setup (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int pk_parse_key_pkcs1_der (int /*<<< orphan*/ ,unsigned char const*,size_t) ; 
 int pk_parse_key_pkcs8_encrypted_der (int /*<<< orphan*/ *,unsigned char const*,size_t,unsigned char const*,size_t) ; 
 int pk_parse_key_pkcs8_unencrypted_der (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 
 int pk_parse_key_sec1_der (int /*<<< orphan*/ ,unsigned char const*,size_t) ; 

int mbedtls_pk_parse_key( mbedtls_pk_context *pk,
                  const unsigned char *key, size_t keylen,
                  const unsigned char *pwd, size_t pwdlen )
{
    int ret;
    const mbedtls_pk_info_t *pk_info;

#if defined(MBEDTLS_PEM_PARSE_C)
    size_t len;
    mbedtls_pem_context pem;

    mbedtls_pem_init( &pem );

#if defined(MBEDTLS_RSA_C)
    /* Avoid calling mbedtls_pem_read_buffer() on non-null-terminated string */
    if( keylen == 0 || key[keylen - 1] != '\0' )
        ret = MBEDTLS_ERR_PEM_NO_HEADER_FOOTER_PRESENT;
    else
        ret = mbedtls_pem_read_buffer( &pem,
                               "-----BEGIN RSA PRIVATE KEY-----",
                               "-----END RSA PRIVATE KEY-----",
                               key, pwd, pwdlen, &len );

    if( ret == 0 )
    {
        if( ( pk_info = mbedtls_pk_info_from_type( MBEDTLS_PK_RSA ) ) == NULL )
            return( MBEDTLS_ERR_PK_UNKNOWN_PK_ALG );

        if( ( ret = mbedtls_pk_setup( pk, pk_info                    ) ) != 0 ||
            ( ret = pk_parse_key_pkcs1_der( mbedtls_pk_rsa( *pk ),
                                            pem.buf, pem.buflen ) ) != 0 )
        {
            mbedtls_pk_free( pk );
        }

        mbedtls_pem_free( &pem );
        return( ret );
    }
    else if( ret == MBEDTLS_ERR_PEM_PASSWORD_MISMATCH )
        return( MBEDTLS_ERR_PK_PASSWORD_MISMATCH );
    else if( ret == MBEDTLS_ERR_PEM_PASSWORD_REQUIRED )
        return( MBEDTLS_ERR_PK_PASSWORD_REQUIRED );
    else if( ret != MBEDTLS_ERR_PEM_NO_HEADER_FOOTER_PRESENT )
        return( ret );
#endif /* MBEDTLS_RSA_C */

#if defined(MBEDTLS_ECP_C)
    /* Avoid calling mbedtls_pem_read_buffer() on non-null-terminated string */
    if( keylen == 0 || key[keylen - 1] != '\0' )
        ret = MBEDTLS_ERR_PEM_NO_HEADER_FOOTER_PRESENT;
    else
        ret = mbedtls_pem_read_buffer( &pem,
                               "-----BEGIN EC PRIVATE KEY-----",
                               "-----END EC PRIVATE KEY-----",
                               key, pwd, pwdlen, &len );
    if( ret == 0 )
    {
        if( ( pk_info = mbedtls_pk_info_from_type( MBEDTLS_PK_ECKEY ) ) == NULL )
            return( MBEDTLS_ERR_PK_UNKNOWN_PK_ALG );

        if( ( ret = mbedtls_pk_setup( pk, pk_info                   ) ) != 0 ||
            ( ret = pk_parse_key_sec1_der( mbedtls_pk_ec( *pk ),
                                           pem.buf, pem.buflen ) ) != 0 )
        {
            mbedtls_pk_free( pk );
        }

        mbedtls_pem_free( &pem );
        return( ret );
    }
    else if( ret == MBEDTLS_ERR_PEM_PASSWORD_MISMATCH )
        return( MBEDTLS_ERR_PK_PASSWORD_MISMATCH );
    else if( ret == MBEDTLS_ERR_PEM_PASSWORD_REQUIRED )
        return( MBEDTLS_ERR_PK_PASSWORD_REQUIRED );
    else if( ret != MBEDTLS_ERR_PEM_NO_HEADER_FOOTER_PRESENT )
        return( ret );
#endif /* MBEDTLS_ECP_C */

    /* Avoid calling mbedtls_pem_read_buffer() on non-null-terminated string */
    if( keylen == 0 || key[keylen - 1] != '\0' )
        ret = MBEDTLS_ERR_PEM_NO_HEADER_FOOTER_PRESENT;
    else
        ret = mbedtls_pem_read_buffer( &pem,
                               "-----BEGIN PRIVATE KEY-----",
                               "-----END PRIVATE KEY-----",
                               key, NULL, 0, &len );
    if( ret == 0 )
    {
        if( ( ret = pk_parse_key_pkcs8_unencrypted_der( pk,
                                                pem.buf, pem.buflen ) ) != 0 )
        {
            mbedtls_pk_free( pk );
        }

        mbedtls_pem_free( &pem );
        return( ret );
    }
    else if( ret != MBEDTLS_ERR_PEM_NO_HEADER_FOOTER_PRESENT )
        return( ret );

#if defined(MBEDTLS_PKCS12_C) || defined(MBEDTLS_PKCS5_C)
    /* Avoid calling mbedtls_pem_read_buffer() on non-null-terminated string */
    if( keylen == 0 || key[keylen - 1] != '\0' )
        ret = MBEDTLS_ERR_PEM_NO_HEADER_FOOTER_PRESENT;
    else
        ret = mbedtls_pem_read_buffer( &pem,
                               "-----BEGIN ENCRYPTED PRIVATE KEY-----",
                               "-----END ENCRYPTED PRIVATE KEY-----",
                               key, NULL, 0, &len );
    if( ret == 0 )
    {
        if( ( ret = pk_parse_key_pkcs8_encrypted_der( pk,
                                                      pem.buf, pem.buflen,
                                                      pwd, pwdlen ) ) != 0 )
        {
            mbedtls_pk_free( pk );
        }

        mbedtls_pem_free( &pem );
        return( ret );
    }
    else if( ret != MBEDTLS_ERR_PEM_NO_HEADER_FOOTER_PRESENT )
        return( ret );
#endif /* MBEDTLS_PKCS12_C || MBEDTLS_PKCS5_C */
#else
    ((void) ret);
    ((void) pwd);
    ((void) pwdlen);
#endif /* MBEDTLS_PEM_PARSE_C */

    /*
     * At this point we only know it's not a PEM formatted key. Could be any
     * of the known DER encoded private key formats
     *
     * We try the different DER format parsers to see if one passes without
     * error
     */
#if defined(MBEDTLS_PKCS12_C) || defined(MBEDTLS_PKCS5_C)
    if( ( ret = pk_parse_key_pkcs8_encrypted_der( pk, key, keylen,
                                                  pwd, pwdlen ) ) == 0 )
    {
        return( 0 );
    }

    mbedtls_pk_free( pk );

    if( ret == MBEDTLS_ERR_PK_PASSWORD_MISMATCH )
    {
        return( ret );
    }
#endif /* MBEDTLS_PKCS12_C || MBEDTLS_PKCS5_C */

    if( ( ret = pk_parse_key_pkcs8_unencrypted_der( pk, key, keylen ) ) == 0 )
        return( 0 );

    mbedtls_pk_free( pk );

#if defined(MBEDTLS_RSA_C)
    if( ( pk_info = mbedtls_pk_info_from_type( MBEDTLS_PK_RSA ) ) == NULL )
        return( MBEDTLS_ERR_PK_UNKNOWN_PK_ALG );

    if( ( ret = mbedtls_pk_setup( pk, pk_info                           ) ) != 0 ||
        ( ret = pk_parse_key_pkcs1_der( mbedtls_pk_rsa( *pk ), key, keylen ) ) == 0 )
    {
        return( 0 );
    }

    mbedtls_pk_free( pk );
#endif /* MBEDTLS_RSA_C */

#if defined(MBEDTLS_ECP_C)
    if( ( pk_info = mbedtls_pk_info_from_type( MBEDTLS_PK_ECKEY ) ) == NULL )
        return( MBEDTLS_ERR_PK_UNKNOWN_PK_ALG );

    if( ( ret = mbedtls_pk_setup( pk, pk_info                         ) ) != 0 ||
        ( ret = pk_parse_key_sec1_der( mbedtls_pk_ec( *pk ), key, keylen ) ) == 0 )
    {
        return( 0 );
    }

    mbedtls_pk_free( pk );
#endif /* MBEDTLS_ECP_C */

    return( MBEDTLS_ERR_PK_KEY_INVALID_FORMAT );
}