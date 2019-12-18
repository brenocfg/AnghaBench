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
typedef  int /*<<< orphan*/  mbedtls_camellia_context ;

/* Variables and functions */
 int MBEDTLS_CAMELLIA_DECRYPT ; 
 int MBEDTLS_ERR_CAMELLIA_INVALID_INPUT_LENGTH ; 
 int /*<<< orphan*/  mbedtls_camellia_crypt_ecb (int /*<<< orphan*/ *,int,unsigned char const*,unsigned char*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,int) ; 

int mbedtls_camellia_crypt_cbc( mbedtls_camellia_context *ctx,
                    int mode,
                    size_t length,
                    unsigned char iv[16],
                    const unsigned char *input,
                    unsigned char *output )
{
    int i;
    unsigned char temp[16];

    if( length % 16 )
        return( MBEDTLS_ERR_CAMELLIA_INVALID_INPUT_LENGTH );

    if( mode == MBEDTLS_CAMELLIA_DECRYPT )
    {
        while( length > 0 )
        {
            memcpy( temp, input, 16 );
            mbedtls_camellia_crypt_ecb( ctx, mode, input, output );

            for( i = 0; i < 16; i++ )
                output[i] = (unsigned char)( output[i] ^ iv[i] );

            memcpy( iv, temp, 16 );

            input  += 16;
            output += 16;
            length -= 16;
        }
    }
    else
    {
        while( length > 0 )
        {
            for( i = 0; i < 16; i++ )
                output[i] = (unsigned char)( input[i] ^ iv[i] );

            mbedtls_camellia_crypt_ecb( ctx, mode, output, output );
            memcpy( iv, output, 16 );

            input  += 16;
            output += 16;
            length -= 16;
        }
    }

    return( 0 );
}