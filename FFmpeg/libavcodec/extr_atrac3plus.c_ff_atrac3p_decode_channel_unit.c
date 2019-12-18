#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int num_quant_units; int used_quant_units; void* noise_table_index; void* noise_level_index; void* noise_present; void* num_coded_subbands; int /*<<< orphan*/  negate_coeffs; int /*<<< orphan*/  swap_channels; void* num_subbands; void* mute_flag; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_1__ Atrac3pChanUnitCtx ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 void** atrac3p_qu_to_subband ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int decode_code_table_indexes (int /*<<< orphan*/ *,TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int decode_gainc_data (int /*<<< orphan*/ *,TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int decode_quant_wordlen (int /*<<< orphan*/ *,TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int decode_scale_factors (int /*<<< orphan*/ *,TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  decode_spectrum (int /*<<< orphan*/ *,TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int decode_tones_info (int /*<<< orphan*/ *,TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  decode_window_shape (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 void* get_bits (int /*<<< orphan*/ *,int) ; 
 void* get_bits1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_subband_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 

int ff_atrac3p_decode_channel_unit(GetBitContext *gb, Atrac3pChanUnitCtx *ctx,
                                   int num_channels, AVCodecContext *avctx)
{
    int ret;

    /* parse sound header */
    ctx->num_quant_units = get_bits(gb, 5) + 1;
    if (ctx->num_quant_units > 28 && ctx->num_quant_units < 32) {
        av_log(avctx, AV_LOG_ERROR,
               "Invalid number of quantization units: %d!\n",
               ctx->num_quant_units);
        return AVERROR_INVALIDDATA;
    }

    ctx->mute_flag = get_bits1(gb);

    /* decode various sound parameters */
    if ((ret = decode_quant_wordlen(gb, ctx, num_channels, avctx)) < 0)
        return ret;

    ctx->num_subbands       = atrac3p_qu_to_subband[ctx->num_quant_units - 1] + 1;
    ctx->num_coded_subbands = ctx->used_quant_units
                              ? atrac3p_qu_to_subband[ctx->used_quant_units - 1] + 1
                              : 0;

    if ((ret = decode_scale_factors(gb, ctx, num_channels, avctx)) < 0)
        return ret;

    if ((ret = decode_code_table_indexes(gb, ctx, num_channels, avctx)) < 0)
        return ret;

    decode_spectrum(gb, ctx, num_channels, avctx);

    if (num_channels == 2) {
        get_subband_flags(gb, ctx->swap_channels, ctx->num_coded_subbands);
        get_subband_flags(gb, ctx->negate_coeffs, ctx->num_coded_subbands);
    }

    decode_window_shape(gb, ctx, num_channels);

    if ((ret = decode_gainc_data(gb, ctx, num_channels, avctx)) < 0)
        return ret;

    if ((ret = decode_tones_info(gb, ctx, num_channels, avctx)) < 0)
        return ret;

    /* decode global noise info */
    ctx->noise_present = get_bits1(gb);
    if (ctx->noise_present) {
        ctx->noise_level_index = get_bits(gb, 4);
        ctx->noise_table_index = get_bits(gb, 4);
    }

    return 0;
}