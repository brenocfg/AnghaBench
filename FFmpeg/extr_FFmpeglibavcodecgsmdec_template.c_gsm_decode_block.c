#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_6__ {TYPE_1__* priv_data; } ;
struct TYPE_5__ {int** lar; size_t lar_idx; int /*<<< orphan*/  msr; int /*<<< orphan*/ * ref_buf; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_1__ GSMContext ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  apcm_dequant_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int av_clip (int,int,int) ; 
 int decode_log_area (int,int,int) ; 
 int /*<<< orphan*/ ** ff_gsm_apcm_bits ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  long_term_synth (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  postprocess (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  short_term_synth (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gsm_decode_block(AVCodecContext *avctx, int16_t *samples,
                            GetBitContext *gb, int mode)
{
    GSMContext *ctx = avctx->priv_data;
    int i;
    int16_t *ref_dst = ctx->ref_buf + 120;
    int *lar = ctx->lar[ctx->lar_idx];
    lar[0] = decode_log_area(get_bits(gb, 6), 13107,  1 << 15);
    lar[1] = decode_log_area(get_bits(gb, 6), 13107,  1 << 15);
    lar[2] = decode_log_area(get_bits(gb, 5), 13107, (1 << 14) + 2048*2);
    lar[3] = decode_log_area(get_bits(gb, 5), 13107, (1 << 14) - 2560*2);
    lar[4] = decode_log_area(get_bits(gb, 4), 19223, (1 << 13) +   94*2);
    lar[5] = decode_log_area(get_bits(gb, 4), 17476, (1 << 13) - 1792*2);
    lar[6] = decode_log_area(get_bits(gb, 3), 31454, (1 << 12) -  341*2);
    lar[7] = decode_log_area(get_bits(gb, 3), 29708, (1 << 12) - 1144*2);

    for (i = 0; i < 4; i++) {
        int lag      = get_bits(gb, 7);
        int gain_idx = get_bits(gb, 2);
        int offset   = get_bits(gb, 2);
        lag = av_clip(lag, 40, 120);
        long_term_synth(ref_dst, lag, gain_idx);
        apcm_dequant_add(gb, ref_dst + offset, ff_gsm_apcm_bits[mode][i]);
        ref_dst += 40;
    }
    memcpy(ctx->ref_buf, ctx->ref_buf + 160, 120 * sizeof(*ctx->ref_buf));
    short_term_synth(ctx, samples, ctx->ref_buf + 120);
    // for optimal speed this could be merged with short_term_synth,
    // not done yet because it is a bit ugly
    ctx->msr = postprocess(samples, ctx->msr);
    return 0;
}