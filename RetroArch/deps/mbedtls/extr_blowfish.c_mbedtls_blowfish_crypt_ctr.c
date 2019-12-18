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
 int /*<<< orphan*/  MBEDTLS_BLOWFISH_ENCRYPT ; 
 int /*<<< orphan*/  mbedtls_blowfish_crypt_ecb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char*,unsigned char*) ; 

int mbedtls_blowfish_crypt_ctr( mbedtls_blowfish_context *ctx,
                       size_t length,
                       size_t *nc_off,
                       unsigned char nonce_counter[MBEDTLS_BLOWFISH_BLOCKSIZE],
                       unsigned char stream_block[MBEDTLS_BLOWFISH_BLOCKSIZE],
                       const unsigned char *input,
                       unsigned char *output )
{
    int c, i;
    size_t n = *nc_off;

    while( length-- )
    {
        if( n == 0 ) {
            mbedtls_blowfish_crypt_ecb( ctx, MBEDTLS_BLOWFISH_ENCRYPT, nonce_counter,
                                stream_block );

            for( i = MBEDTLS_BLOWFISH_BLOCKSIZE; i > 0; i-- )
                if( ++nonce_counter[i - 1] != 0 )
                    break;
        }
        c = *input++;
        *output++ = (unsigned char)( c ^ stream_block[n] );

        n = ( n + 1 ) % MBEDTLS_BLOWFISH_BLOCKSIZE;
    }

    *nc_off = n;

    return( 0 );
}