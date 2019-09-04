#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  bits; int /*<<< orphan*/  table; } ;
struct TYPE_14__ {int /*<<< orphan*/  frame_number; } ;
struct TYPE_13__ {TYPE_2__* waves_info; TYPE_1__* channels; } ;
struct TYPE_12__ {int num_wavs; int start_index; } ;
struct TYPE_11__ {int num_tone_bands; int tones_index; } ;
struct TYPE_10__ {TYPE_3__* tones_info; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_3__ Atrac3pWavesData ;
typedef  TYPE_4__ Atrac3pChanUnitCtx ;
typedef  TYPE_5__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 void* get_bits (int /*<<< orphan*/ *,int) ; 
 void* get_vlc2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int sign_extend (int,int) ; 
 TYPE_6__* tone_vlc_tabs ; 

__attribute__((used)) static int decode_band_numwavs(GetBitContext *gb, Atrac3pChanUnitCtx *ctx,
                               int ch_num, int band_has_tones[],
                               AVCodecContext *avctx)
{
    int mode, sb, delta;
    Atrac3pWavesData *dst = ctx->channels[ch_num].tones_info;
    Atrac3pWavesData *ref = ctx->channels[0].tones_info;

    mode = get_bits(gb, ch_num + 1);
    switch (mode) {
    case 0: /** fixed-length coding */
        for (sb = 0; sb < ctx->waves_info->num_tone_bands; sb++)
            if (band_has_tones[sb])
                dst[sb].num_wavs = get_bits(gb, 4);
        break;
    case 1: /** variable-length coding */
        for (sb = 0; sb < ctx->waves_info->num_tone_bands; sb++)
            if (band_has_tones[sb])
                dst[sb].num_wavs =
                    get_vlc2(gb, tone_vlc_tabs[1].table,
                             tone_vlc_tabs[1].bits, 1);
        break;
    case 2: /** VLC modulo delta to master (slave only) */
        for (sb = 0; sb < ctx->waves_info->num_tone_bands; sb++)
            if (band_has_tones[sb]) {
                delta = get_vlc2(gb, tone_vlc_tabs[2].table,
                                 tone_vlc_tabs[2].bits, 1);
                delta = sign_extend(delta, 3);
                dst[sb].num_wavs = (ref[sb].num_wavs + delta) & 0xF;
            }
        break;
    case 3: /** copy master (slave only) */
        for (sb = 0; sb < ctx->waves_info->num_tone_bands; sb++)
            if (band_has_tones[sb])
                dst[sb].num_wavs = ref[sb].num_wavs;
        break;
    }

    /** initialize start tone index for each subband */
    for (sb = 0; sb < ctx->waves_info->num_tone_bands; sb++)
        if (band_has_tones[sb]) {
            if (ctx->waves_info->tones_index + dst[sb].num_wavs > 48) {
                av_log(avctx, AV_LOG_ERROR,
                       "Too many tones: %d (max. 48), frame: %d!\n",
                       ctx->waves_info->tones_index + dst[sb].num_wavs,
                       avctx->frame_number);
                return AVERROR_INVALIDDATA;
            }
            dst[sb].start_index           = ctx->waves_info->tones_index;
            ctx->waves_info->tones_index += dst[sb].num_wavs;
        }

    return 0;
}