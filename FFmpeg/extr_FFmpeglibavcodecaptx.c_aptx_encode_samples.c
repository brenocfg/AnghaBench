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
struct TYPE_3__ {int /*<<< orphan*/ * channels; int /*<<< orphan*/  hd; int /*<<< orphan*/  sync_idx; } ;
typedef  TYPE_1__ AptXContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_WB16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_WB24 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int NB_CHANNELS ; 
 int /*<<< orphan*/  aptx_encode_channel (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aptx_insert_sync (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aptx_invert_quantize_and_prediction (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aptx_pack_codeword (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aptxhd_pack_codeword (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void aptx_encode_samples(AptXContext *ctx,
                                int32_t samples[NB_CHANNELS][4],
                                uint8_t *output)
{
    int channel;
    for (channel = 0; channel < NB_CHANNELS; channel++)
        aptx_encode_channel(&ctx->channels[channel], samples[channel], ctx->hd);

    aptx_insert_sync(ctx->channels, &ctx->sync_idx);

    for (channel = 0; channel < NB_CHANNELS; channel++) {
        aptx_invert_quantize_and_prediction(&ctx->channels[channel], ctx->hd);
        if (ctx->hd)
            AV_WB24(output + 3*channel,
                    aptxhd_pack_codeword(&ctx->channels[channel]));
        else
            AV_WB16(output + 2*channel,
                    aptx_pack_codeword(&ctx->channels[channel]));
    }
}