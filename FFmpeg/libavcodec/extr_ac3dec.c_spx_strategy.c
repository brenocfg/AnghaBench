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
struct TYPE_3__ {int fbw_channels; scalar_t__ channel_mode; int* channel_uses_spx; int spx_dst_end_freq; int spx_dst_start_freq; int spx_src_start_freq; int /*<<< orphan*/  spx_band_struct; int /*<<< orphan*/  spx_band_sizes; int /*<<< orphan*/  num_spx_bands; int /*<<< orphan*/  eac3; int /*<<< orphan*/  avctx; int /*<<< orphan*/  gbc; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_1__ AC3DecodeContext ;

/* Variables and functions */
 scalar_t__ AC3_CHMODE_MONO ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  USE_FIXED ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  decode_band_structure (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int* end_freq_inv_tab ; 
 int /*<<< orphan*/  ff_eac3_default_spx_band_struct ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int spx_strategy(AC3DecodeContext *s, int blk)
{
    GetBitContext *bc = &s->gbc;
    int fbw_channels = s->fbw_channels;
    int dst_start_freq, dst_end_freq, src_start_freq,
        start_subband, end_subband, ch;

    /* determine which channels use spx */
    if (s->channel_mode == AC3_CHMODE_MONO) {
        s->channel_uses_spx[1] = 1;
    } else {
        for (ch = 1; ch <= fbw_channels; ch++)
            s->channel_uses_spx[ch] = get_bits1(bc);
    }

    /* get the frequency bins of the spx copy region and the spx start
       and end subbands */
    dst_start_freq = get_bits(bc, 2);
    start_subband  = get_bits(bc, 3) + 2;
    if (start_subband > 7)
        start_subband += start_subband - 7;
    end_subband    = get_bits(bc, 3) + 5;
#if USE_FIXED
    s->spx_dst_end_freq = end_freq_inv_tab[end_subband-5];
#endif
    if (end_subband   > 7)
        end_subband   += end_subband   - 7;
    dst_start_freq = dst_start_freq * 12 + 25;
    src_start_freq = start_subband  * 12 + 25;
    dst_end_freq   = end_subband    * 12 + 25;

    /* check validity of spx ranges */
    if (start_subband >= end_subband) {
        av_log(s->avctx, AV_LOG_ERROR, "invalid spectral extension "
               "range (%d >= %d)\n", start_subband, end_subband);
        return AVERROR_INVALIDDATA;
    }
    if (dst_start_freq >= src_start_freq) {
        av_log(s->avctx, AV_LOG_ERROR, "invalid spectral extension "
               "copy start bin (%d >= %d)\n", dst_start_freq, src_start_freq);
        return AVERROR_INVALIDDATA;
    }

    s->spx_dst_start_freq = dst_start_freq;
    s->spx_src_start_freq = src_start_freq;
    if (!USE_FIXED)
        s->spx_dst_end_freq   = dst_end_freq;

    decode_band_structure(bc, blk, s->eac3, 0,
                          start_subband, end_subband,
                          ff_eac3_default_spx_band_struct,
                          &s->num_spx_bands,
                          s->spx_band_sizes,
                          s->spx_band_struct, sizeof(s->spx_band_struct));
    return 0;
}