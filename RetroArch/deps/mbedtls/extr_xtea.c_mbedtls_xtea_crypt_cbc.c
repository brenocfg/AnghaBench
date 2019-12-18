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
typedef  int /*<<< orphan*/  mbedtls_xtea_context ;

/* Variables and functions */
 int MBEDTLS_ERR_XTEA_INVALID_INPUT_LENGTH ; 
 int MBEDTLS_XTEA_DECRYPT ; 
 int /*<<< orphan*/  mbedtls_xtea_crypt_ecb (int /*<<< orphan*/ *,int,unsigned char const*,unsigned char*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,int) ; 

int mbedtls_xtea_crypt_cbc( mbedtls_xtea_context *ctx, int mode, size_t length,
                    unsigned char iv[8], const unsigned char *input,
                    unsigned char *output)
{
    int i;
    unsigned char temp[8];

    if( length % 8 )
        return( MBEDTLS_ERR_XTEA_INVALID_INPUT_LENGTH );

    if( mode == MBEDTLS_XTEA_DECRYPT )
    {
        while( length > 0 )
        {
            memcpy( temp, input, 8 );
            mbedtls_xtea_crypt_ecb( ctx, mode, input, output );

            for( i = 0; i < 8; i++ )
                output[i] = (unsigned char)( output[i] ^ iv[i] );

            memcpy( iv, temp, 8 );

            input  += 8;
            output += 8;
            length -= 8;
        }
    }
    else
    {
        while( length > 0 )
        {
            for( i = 0; i < 8; i++ )
                output[i] = (unsigned char)( input[i] ^ iv[i] );

            mbedtls_xtea_crypt_ecb( ctx, mode, output, output );
            memcpy( iv, output, 8 );

            input  += 8;
            output += 8;
            length -= 8;
        }
    }

    return( 0 );
}