#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_9__ {int /*<<< orphan*/ ** coeff; TYPE_2__* filter_params; } ;
struct TYPE_8__ {int order; int shift; } ;
struct TYPE_7__ {int substream_info; unsigned int number_of_samples; int /*<<< orphan*/ * lpc_sample_buffer; int /*<<< orphan*/  lpc_ctx; int /*<<< orphan*/  num_channels; TYPE_3__* cur_channel_params; int /*<<< orphan*/ * sample_buffer; } ;
typedef  TYPE_1__ MLPEncodeContext ;
typedef  TYPE_2__ FilterParams ;
typedef  TYPE_3__ ChannelParams ;

/* Variables and functions */
 int /*<<< orphan*/  FF_LPC_TYPE_LEVINSON ; 
 unsigned int FIR ; 
 unsigned int IIR ; 
 int MAX_LPC_ORDER ; 
 int MLP_MAX_LPC_ORDER ; 
 int /*<<< orphan*/  MLP_MAX_LPC_SHIFT ; 
 int /*<<< orphan*/  MLP_MIN_LPC_ORDER ; 
 int /*<<< orphan*/  MLP_MIN_LPC_SHIFT ; 
 int /*<<< orphan*/  ORDER_METHOD_EST ; 
 int SUBSTREAM_INFO_HIGH_RATE ; 
 int /*<<< orphan*/  code_filter_coeffs (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int ff_lpc_calc_coefs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ,int const,int,int /*<<< orphan*/ **,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_filter_params(MLPEncodeContext *ctx,
                              unsigned int channel, unsigned int filter,
                              int clear_filter)
{
    ChannelParams *cp = &ctx->cur_channel_params[channel];
    FilterParams *fp = &cp->filter_params[filter];

    if ((filter == IIR && ctx->substream_info & SUBSTREAM_INFO_HIGH_RATE) ||
        clear_filter) {
        fp->order = 0;
    } else if (filter == IIR) {
        fp->order = 0;
    } else if (filter == FIR) {
        const int max_order = (ctx->substream_info & SUBSTREAM_INFO_HIGH_RATE)
                              ? 4 : MLP_MAX_LPC_ORDER;
        int32_t *sample_buffer = ctx->sample_buffer + channel;
        int32_t coefs[MAX_LPC_ORDER][MAX_LPC_ORDER];
        int32_t *lpc_samples = ctx->lpc_sample_buffer;
        int32_t *fcoeff = ctx->cur_channel_params[channel].coeff[filter];
        int shift[MLP_MAX_LPC_ORDER];
        unsigned int i;
        int order;

        for (i = 0; i < ctx->number_of_samples; i++) {
            *lpc_samples++ = *sample_buffer;
            sample_buffer += ctx->num_channels;
        }

        order = ff_lpc_calc_coefs(&ctx->lpc_ctx, ctx->lpc_sample_buffer,
                                  ctx->number_of_samples, MLP_MIN_LPC_ORDER,
                                  max_order, 11, coefs, shift, FF_LPC_TYPE_LEVINSON, 0,
                                  ORDER_METHOD_EST, MLP_MIN_LPC_SHIFT,
                                  MLP_MAX_LPC_SHIFT, MLP_MIN_LPC_SHIFT);

        fp->order = order;
        fp->shift = shift[order-1];

        for (i = 0; i < order; i++)
            fcoeff[i] = coefs[order-1][i];

        code_filter_coeffs(ctx, fp, fcoeff);
    }
}