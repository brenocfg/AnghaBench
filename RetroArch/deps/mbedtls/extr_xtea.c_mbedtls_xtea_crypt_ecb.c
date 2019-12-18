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
typedef  int uint32_t ;
struct TYPE_3__ {int* k; } ;
typedef  TYPE_1__ mbedtls_xtea_context ;

/* Variables and functions */
 int /*<<< orphan*/  GET_UINT32_BE (int,unsigned char const*,int) ; 
 int MBEDTLS_XTEA_ENCRYPT ; 
 int /*<<< orphan*/  PUT_UINT32_BE (int,unsigned char*,int) ; 

int mbedtls_xtea_crypt_ecb( mbedtls_xtea_context *ctx, int mode,
                    const unsigned char input[8], unsigned char output[8])
{
    uint32_t *k, v0, v1, i;

    k = ctx->k;

    GET_UINT32_BE( v0, input, 0 );
    GET_UINT32_BE( v1, input, 4 );

    if( mode == MBEDTLS_XTEA_ENCRYPT )
    {
        uint32_t sum = 0, delta = 0x9E3779B9;

        for( i = 0; i < 32; i++ )
        {
            v0 += (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + k[sum & 3]);
            sum += delta;
            v1 += (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + k[(sum>>11) & 3]);
        }
    }
    else /* MBEDTLS_XTEA_DECRYPT */
    {
        uint32_t delta = 0x9E3779B9, sum = delta * 32;

        for( i = 0; i < 32; i++ )
        {
            v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + k[(sum>>11) & 3]);
            sum -= delta;
            v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + k[sum & 3]);
        }
    }

    PUT_UINT32_BE( v0, output, 0 );
    PUT_UINT32_BE( v1, output, 4 );

    return( 0 );
}