#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_4__ {int* P; } ;
typedef  TYPE_1__ mbedtls_blowfish_context ;

/* Variables and functions */
 int F (TYPE_1__*,int) ; 
 short MBEDTLS_BLOWFISH_ROUNDS ; 

__attribute__((used)) static void blowfish_enc( mbedtls_blowfish_context *ctx, uint32_t *xl, uint32_t *xr )
{
    uint32_t  Xl, Xr, temp;
    short i;

    Xl = *xl;
    Xr = *xr;

    for( i = 0; i < MBEDTLS_BLOWFISH_ROUNDS; ++i )
    {
        Xl = Xl ^ ctx->P[i];
        Xr = F( ctx, Xl ) ^ Xr;

        temp = Xl;
        Xl = Xr;
        Xr = temp;
    }

    temp = Xl;
    Xl = Xr;
    Xr = temp;

    Xr = Xr ^ ctx->P[MBEDTLS_BLOWFISH_ROUNDS];
    Xl = Xl ^ ctx->P[MBEDTLS_BLOWFISH_ROUNDS + 1];

    *xl = Xl;
    *xr = Xr;
}