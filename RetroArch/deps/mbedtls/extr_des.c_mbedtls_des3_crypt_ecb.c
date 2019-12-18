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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/ * sk; } ;
typedef  TYPE_1__ mbedtls_des3_context ;

/* Variables and functions */
 int /*<<< orphan*/  DES_FP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DES_IP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DES_ROUND (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_UINT32_BE (int /*<<< orphan*/ ,unsigned char const*,int) ; 
 int /*<<< orphan*/  PUT_UINT32_BE (int /*<<< orphan*/ ,unsigned char*,int) ; 

int mbedtls_des3_crypt_ecb( mbedtls_des3_context *ctx,
                     const unsigned char input[8],
                     unsigned char output[8] )
{
    int i;
    uint32_t X, Y, T, *SK;

    SK = ctx->sk;

    GET_UINT32_BE( X, input, 0 );
    GET_UINT32_BE( Y, input, 4 );

    DES_IP( X, Y );

    for( i = 0; i < 8; i++ )
    {
        DES_ROUND( Y, X );
        DES_ROUND( X, Y );
    }

    for( i = 0; i < 8; i++ )
    {
        DES_ROUND( X, Y );
        DES_ROUND( Y, X );
    }

    for( i = 0; i < 8; i++ )
    {
        DES_ROUND( Y, X );
        DES_ROUND( X, Y );
    }

    DES_FP( Y, X );

    PUT_UINT32_BE( Y, output, 0 );
    PUT_UINT32_BE( X, output, 4 );

    return( 0 );
}