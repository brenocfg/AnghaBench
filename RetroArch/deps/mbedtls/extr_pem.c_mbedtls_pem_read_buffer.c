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
struct TYPE_3__ {unsigned char* buf; size_t buflen; } ;
typedef  TYPE_1__ mbedtls_pem_context ;
typedef  scalar_t__ mbedtls_cipher_type_t ;

/* Variables and functions */
 scalar_t__ MBEDTLS_CIPHER_AES_128_CBC ; 
 scalar_t__ MBEDTLS_CIPHER_AES_192_CBC ; 
 scalar_t__ MBEDTLS_CIPHER_AES_256_CBC ; 
 scalar_t__ MBEDTLS_CIPHER_DES_CBC ; 
 scalar_t__ MBEDTLS_CIPHER_DES_EDE3_CBC ; 
 scalar_t__ MBEDTLS_CIPHER_NONE ; 
 int MBEDTLS_ERR_BASE64_INVALID_CHARACTER ; 
 int MBEDTLS_ERR_PEM_ALLOC_FAILED ; 
 int MBEDTLS_ERR_PEM_BAD_INPUT_DATA ; 
 int MBEDTLS_ERR_PEM_FEATURE_UNAVAILABLE ; 
 int MBEDTLS_ERR_PEM_INVALID_DATA ; 
 int MBEDTLS_ERR_PEM_INVALID_ENC_IV ; 
 int MBEDTLS_ERR_PEM_NO_HEADER_FOOTER_PRESENT ; 
 int MBEDTLS_ERR_PEM_PASSWORD_MISMATCH ; 
 int MBEDTLS_ERR_PEM_PASSWORD_REQUIRED ; 
 int MBEDTLS_ERR_PEM_UNKNOWN_ENC_ALG ; 
 int mbedtls_base64_decode (unsigned char*,size_t,size_t*,unsigned char const*,int) ; 
 scalar_t__ mbedtls_calloc (int,size_t) ; 
 int /*<<< orphan*/  mbedtls_free (unsigned char*) ; 
 scalar_t__ memcmp (unsigned char const*,char*,int) ; 
 int /*<<< orphan*/  pem_aes_decrypt (unsigned char*,int,unsigned char*,size_t,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  pem_des3_decrypt (unsigned char*,unsigned char*,size_t,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  pem_des_decrypt (unsigned char*,unsigned char*,size_t,unsigned char const*,size_t) ; 
 scalar_t__ pem_get_iv (unsigned char const*,unsigned char*,int) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 scalar_t__ strstr (char const*,char const*) ; 

int mbedtls_pem_read_buffer( mbedtls_pem_context *ctx, const char *header, const char *footer,
                     const unsigned char *data, const unsigned char *pwd,
                     size_t pwdlen, size_t *use_len )
{
    int ret, enc;
    size_t len;
    unsigned char *buf;
    const unsigned char *s1, *s2, *end;
#if defined(MBEDTLS_MD5_C) && defined(MBEDTLS_CIPHER_MODE_CBC) &&         \
    ( defined(MBEDTLS_DES_C) || defined(MBEDTLS_AES_C) )
    unsigned char pem_iv[16];
    mbedtls_cipher_type_t enc_alg = MBEDTLS_CIPHER_NONE;
#else
    ((void) pwd);
    ((void) pwdlen);
#endif /* MBEDTLS_MD5_C && MBEDTLS_CIPHER_MODE_CBC &&
          ( MBEDTLS_AES_C || MBEDTLS_DES_C ) */

    if( ctx == NULL )
        return( MBEDTLS_ERR_PEM_BAD_INPUT_DATA );

    s1 = (unsigned char *) strstr( (const char *) data, header );

    if( s1 == NULL )
        return( MBEDTLS_ERR_PEM_NO_HEADER_FOOTER_PRESENT );

    s2 = (unsigned char *) strstr( (const char *) data, footer );

    if( s2 == NULL || s2 <= s1 )
        return( MBEDTLS_ERR_PEM_NO_HEADER_FOOTER_PRESENT );

    s1 += strlen( header );
    if( *s1 == ' '  ) s1++;
    if( *s1 == '\r' ) s1++;
    if( *s1 == '\n' ) s1++;
    else return( MBEDTLS_ERR_PEM_NO_HEADER_FOOTER_PRESENT );

    end = s2;
    end += strlen( footer );
    if( *end == ' '  ) end++;
    if( *end == '\r' ) end++;
    if( *end == '\n' ) end++;
    *use_len = end - data;

    enc = 0;

    if( s2 - s1 >= 22 && memcmp( s1, "Proc-Type: 4,ENCRYPTED", 22 ) == 0 )
    {
#if defined(MBEDTLS_MD5_C) && defined(MBEDTLS_CIPHER_MODE_CBC) &&         \
    ( defined(MBEDTLS_DES_C) || defined(MBEDTLS_AES_C) )
        enc++;

        s1 += 22;
        if( *s1 == '\r' ) s1++;
        if( *s1 == '\n' ) s1++;
        else return( MBEDTLS_ERR_PEM_INVALID_DATA );


#if defined(MBEDTLS_DES_C)
        if( s2 - s1 >= 23 && memcmp( s1, "DEK-Info: DES-EDE3-CBC,", 23 ) == 0 )
        {
            enc_alg = MBEDTLS_CIPHER_DES_EDE3_CBC;

            s1 += 23;
            if( s2 - s1 < 16 || pem_get_iv( s1, pem_iv, 8 ) != 0 )
                return( MBEDTLS_ERR_PEM_INVALID_ENC_IV );

            s1 += 16;
        }
        else if( s2 - s1 >= 18 && memcmp( s1, "DEK-Info: DES-CBC,", 18 ) == 0 )
        {
            enc_alg = MBEDTLS_CIPHER_DES_CBC;

            s1 += 18;
            if( s2 - s1 < 16 || pem_get_iv( s1, pem_iv, 8) != 0 )
                return( MBEDTLS_ERR_PEM_INVALID_ENC_IV );

            s1 += 16;
        }
#endif /* MBEDTLS_DES_C */

#if defined(MBEDTLS_AES_C)
        if( s2 - s1 >= 14 && memcmp( s1, "DEK-Info: AES-", 14 ) == 0 )
        {
            if( s2 - s1 < 22 )
                return( MBEDTLS_ERR_PEM_UNKNOWN_ENC_ALG );
            else if( memcmp( s1, "DEK-Info: AES-128-CBC,", 22 ) == 0 )
                enc_alg = MBEDTLS_CIPHER_AES_128_CBC;
            else if( memcmp( s1, "DEK-Info: AES-192-CBC,", 22 ) == 0 )
                enc_alg = MBEDTLS_CIPHER_AES_192_CBC;
            else if( memcmp( s1, "DEK-Info: AES-256-CBC,", 22 ) == 0 )
                enc_alg = MBEDTLS_CIPHER_AES_256_CBC;
            else
                return( MBEDTLS_ERR_PEM_UNKNOWN_ENC_ALG );

            s1 += 22;
            if( s2 - s1 < 32 || pem_get_iv( s1, pem_iv, 16 ) != 0 )
                return( MBEDTLS_ERR_PEM_INVALID_ENC_IV );

            s1 += 32;
        }
#endif /* MBEDTLS_AES_C */

        if( enc_alg == MBEDTLS_CIPHER_NONE )
            return( MBEDTLS_ERR_PEM_UNKNOWN_ENC_ALG );

        if( *s1 == '\r' ) s1++;
        if( *s1 == '\n' ) s1++;
        else return( MBEDTLS_ERR_PEM_INVALID_DATA );
#else
        return( MBEDTLS_ERR_PEM_FEATURE_UNAVAILABLE );
#endif /* MBEDTLS_MD5_C && MBEDTLS_CIPHER_MODE_CBC &&
          ( MBEDTLS_AES_C || MBEDTLS_DES_C ) */
    }

    if( s1 >= s2 )
        return( MBEDTLS_ERR_PEM_INVALID_DATA );

    ret = mbedtls_base64_decode( NULL, 0, &len, s1, s2 - s1 );

    if( ret == MBEDTLS_ERR_BASE64_INVALID_CHARACTER )
        return( MBEDTLS_ERR_PEM_INVALID_DATA + ret );

    if( ( buf = (unsigned char*)mbedtls_calloc( 1, len ) ) == NULL )
        return( MBEDTLS_ERR_PEM_ALLOC_FAILED );

    if( ( ret = mbedtls_base64_decode( buf, len, &len, s1, s2 - s1 ) ) != 0 )
    {
        mbedtls_free( buf );
        return( MBEDTLS_ERR_PEM_INVALID_DATA + ret );
    }

    if( enc != 0 )
    {
#if defined(MBEDTLS_MD5_C) && defined(MBEDTLS_CIPHER_MODE_CBC) &&         \
    ( defined(MBEDTLS_DES_C) || defined(MBEDTLS_AES_C) )
        if( pwd == NULL )
        {
            mbedtls_free( buf );
            return( MBEDTLS_ERR_PEM_PASSWORD_REQUIRED );
        }

#if defined(MBEDTLS_DES_C)
        if( enc_alg == MBEDTLS_CIPHER_DES_EDE3_CBC )
            pem_des3_decrypt( pem_iv, buf, len, pwd, pwdlen );
        else if( enc_alg == MBEDTLS_CIPHER_DES_CBC )
            pem_des_decrypt( pem_iv, buf, len, pwd, pwdlen );
#endif /* MBEDTLS_DES_C */

#if defined(MBEDTLS_AES_C)
        if( enc_alg == MBEDTLS_CIPHER_AES_128_CBC )
            pem_aes_decrypt( pem_iv, 16, buf, len, pwd, pwdlen );
        else if( enc_alg == MBEDTLS_CIPHER_AES_192_CBC )
            pem_aes_decrypt( pem_iv, 24, buf, len, pwd, pwdlen );
        else if( enc_alg == MBEDTLS_CIPHER_AES_256_CBC )
            pem_aes_decrypt( pem_iv, 32, buf, len, pwd, pwdlen );
#endif /* MBEDTLS_AES_C */

        /*
         * The result will be ASN.1 starting with a SEQUENCE tag, with 1 to 3
         * length bytes (allow 4 to be sure) in all known use cases.
         *
         * Use that as heurisitic to try detecting password mismatchs.
         */
        if( len <= 2 || buf[0] != 0x30 || buf[1] > 0x83 )
        {
            mbedtls_free( buf );
            return( MBEDTLS_ERR_PEM_PASSWORD_MISMATCH );
        }
#else
        mbedtls_free( buf );
        return( MBEDTLS_ERR_PEM_FEATURE_UNAVAILABLE );
#endif /* MBEDTLS_MD5_C && MBEDTLS_CIPHER_MODE_CBC &&
          ( MBEDTLS_AES_C || MBEDTLS_DES_C ) */
    }

    ctx->buf = buf;
    ctx->buflen = len;

    return( 0 );
}