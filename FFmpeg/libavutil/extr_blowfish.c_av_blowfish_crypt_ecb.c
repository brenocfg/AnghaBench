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
struct TYPE_3__ {int /*<<< orphan*/ * p; } ;
typedef  TYPE_1__ AVBlowfish ;

/* Variables and functions */
 int AV_BF_ROUNDS ; 
 int /*<<< orphan*/  F (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void av_blowfish_crypt_ecb(AVBlowfish *ctx, uint32_t *xl, uint32_t *xr,
                           int decrypt)
{
    uint32_t Xl, Xr;
    int i;

    Xl = *xl;
    Xr = *xr;

    if (decrypt) {
        Xl ^= ctx->p[AV_BF_ROUNDS + 1];
        for (i = AV_BF_ROUNDS; i > 0; i-=2) {
            F(Xl, Xr, ctx->p[i  ]);
            F(Xr, Xl, ctx->p[i-1]);
        }

        Xr ^= ctx->p[0];
    } else {
        Xl ^= ctx->p[0];
        for (i = 1; i < AV_BF_ROUNDS+1; i+=2){
            F(Xl, Xr, ctx->p[i  ]);
            F(Xr, Xl, ctx->p[i+1]);
        }

        Xr ^= ctx->p[AV_BF_ROUNDS + 1];
    }

    *xl = Xr;
    *xr = Xl;
}