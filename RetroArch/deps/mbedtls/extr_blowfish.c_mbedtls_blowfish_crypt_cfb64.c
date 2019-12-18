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
typedef  int /*<<< orphan*/  mbedtls_blowfish_context ;

/* Variables and functions */
 size_t MBEDTLS_BLOWFISH_BLOCKSIZE ; 
 int MBEDTLS_BLOWFISH_DECRYPT ; 
 int /*<<< orphan*/  MBEDTLS_BLOWFISH_ENCRYPT ; 
 int /*<<< orphan*/  mbedtls_blowfish_crypt_ecb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char*,unsigned char*) ; 

int mbedtls_blowfish_crypt_cfb64( mbedtls_blowfish_context *ctx,
                       int mode,
                       size_t length,
                       size_t *iv_off,
                       unsigned char iv[MBEDTLS_BLOWFISH_BLOCKSIZE],
                       const unsigned char *input,
                       unsigned char *output )
{
    int c;
    size_t n = *iv_off;

    if( mode == MBEDTLS_BLOWFISH_DECRYPT )
    {
        while( length-- )
        {
            if( n == 0 )
                mbedtls_blowfish_crypt_ecb( ctx, MBEDTLS_BLOWFISH_ENCRYPT, iv, iv );

            c = *input++;
            *output++ = (unsigned char)( c ^ iv[n] );
            iv[n] = (unsigned char) c;

            n = ( n + 1 ) % MBEDTLS_BLOWFISH_BLOCKSIZE;
        }
    }
    else
    {
        while( length-- )
        {
            if( n == 0 )
                mbedtls_blowfish_crypt_ecb( ctx, MBEDTLS_BLOWFISH_ENCRYPT, iv, iv );

            iv[n] = *output++ = (unsigned char)( iv[n] ^ *input++ );

            n = ( n + 1 ) % MBEDTLS_BLOWFISH_BLOCKSIZE;
        }
    }

    *iv_off = n;

    return( 0 );
}