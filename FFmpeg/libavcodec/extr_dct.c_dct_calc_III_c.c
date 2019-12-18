#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  (* rdft_calc ) (TYPE_2__*,float*) ;} ;
struct TYPE_6__ {int nbits; float* csc2; TYPE_2__ rdft; } ;
typedef  float FFTSample ;
typedef  TYPE_1__ DCTContext ;

/* Variables and functions */
 float COS (TYPE_1__*,int,int) ; 
 float SIN (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,float*) ; 

__attribute__((used)) static void dct_calc_III_c(DCTContext *ctx, FFTSample *data)
{
    int n = 1 << ctx->nbits;
    int i;

    float next  = data[n - 1];
    float inv_n = 1.0f / n;

    for (i = n - 2; i >= 2; i -= 2) {
        float val1 = data[i];
        float val2 = data[i - 1] - data[i + 1];
        float c    = COS(ctx, n, i);
        float s    = SIN(ctx, n, i);

        data[i]     = c * val1 + s * val2;
        data[i + 1] = s * val1 - c * val2;
    }

    data[1] = 2 * next;

    ctx->rdft.rdft_calc(&ctx->rdft, data);

    for (i = 0; i < n / 2; i++) {
        float tmp1 = data[i]         * inv_n;
        float tmp2 = data[n - i - 1] * inv_n;
        float csc  = ctx->csc2[i] * (tmp1 - tmp2);

        tmp1            += tmp2;
        data[i]          = tmp1 + csc;
        data[n - i - 1]  = tmp1 - csc;
    }
}