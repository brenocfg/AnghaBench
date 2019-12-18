#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_7__ {int order; int shift; int coeff_bits; int coeff_shift; } ;
struct TYPE_6__ {TYPE_1__* cur_channel_params; } ;
struct TYPE_5__ {int** coeff; TYPE_3__* filter_params; } ;
typedef  int /*<<< orphan*/  PutBitContext ;
typedef  TYPE_2__ MLPEncodeContext ;
typedef  TYPE_3__ FilterParams ;

/* Variables and functions */
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  put_sbits (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void write_filter_params(MLPEncodeContext *ctx, PutBitContext *pb,
                                unsigned int channel, unsigned int filter)
{
    FilterParams *fp = &ctx->cur_channel_params[channel].filter_params[filter];

    put_bits(pb, 4, fp->order);

    if (fp->order > 0) {
        int i;
        int32_t *fcoeff = ctx->cur_channel_params[channel].coeff[filter];

        put_bits(pb, 4, fp->shift      );
        put_bits(pb, 5, fp->coeff_bits );
        put_bits(pb, 3, fp->coeff_shift);

        for (i = 0; i < fp->order; i++) {
            put_sbits(pb, fp->coeff_bits, fcoeff[i] >> fp->coeff_shift);
        }

        /* TODO state data for IIR filter. */
        put_bits(pb, 1, 0);
    }
}