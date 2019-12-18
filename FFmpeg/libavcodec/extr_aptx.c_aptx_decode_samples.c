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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_3__ {int /*<<< orphan*/ * channels; int /*<<< orphan*/  sync_idx; int /*<<< orphan*/  hd; } ;
typedef  TYPE_1__ AptXContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_RB16 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  AV_RB24 (int /*<<< orphan*/  const*) ; 
 int NB_CHANNELS ; 
 int aptx_check_parity (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aptx_decode_channel (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aptx_generate_dither (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aptx_invert_quantize_and_prediction (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aptx_unpack_codeword (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aptxhd_unpack_codeword (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int aptx_decode_samples(AptXContext *ctx,
                                const uint8_t *input,
                                int32_t samples[NB_CHANNELS][4])
{
    int channel, ret;

    for (channel = 0; channel < NB_CHANNELS; channel++) {
        aptx_generate_dither(&ctx->channels[channel]);

        if (ctx->hd)
            aptxhd_unpack_codeword(&ctx->channels[channel],
                                   AV_RB24(input + 3*channel));
        else
            aptx_unpack_codeword(&ctx->channels[channel],
                                 AV_RB16(input + 2*channel));
        aptx_invert_quantize_and_prediction(&ctx->channels[channel], ctx->hd);
    }

    ret = aptx_check_parity(ctx->channels, &ctx->sync_idx);

    for (channel = 0; channel < NB_CHANNELS; channel++)
        aptx_decode_channel(&ctx->channels[channel], samples[channel]);

    return ret;
}