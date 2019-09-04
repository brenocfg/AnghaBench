#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  bits; int /*<<< orphan*/  table; } ;
struct TYPE_13__ {TYPE_2__* channels; TYPE_1__* waves_info; } ;
struct TYPE_12__ {int /*<<< orphan*/ * tones_info; } ;
struct TYPE_11__ {int num_tone_bands; scalar_t__* tone_master; scalar_t__* tone_sharing; scalar_t__ tones_index; scalar_t__* invert_phase; void* amplitude_mode; int /*<<< orphan*/ * waves; void* tones_present; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_3__ Atrac3pChanUnitCtx ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int ATRAC3P_SUBBANDS ; 
 int AVERROR_PATCHWELCOME ; 
 int /*<<< orphan*/  Atrac3pWavesData ; 
 int /*<<< orphan*/  FFSWAP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avpriv_report_missing_feature (int /*<<< orphan*/ *,char*) ; 
 int decode_band_numwavs (int /*<<< orphan*/ *,TYPE_3__*,int,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  decode_tones_amplitude (int /*<<< orphan*/ *,TYPE_3__*,int,int*) ; 
 int /*<<< orphan*/  decode_tones_envelope (int /*<<< orphan*/ *,TYPE_3__*,int,int*) ; 
 int /*<<< orphan*/  decode_tones_frequency (int /*<<< orphan*/ *,TYPE_3__*,int,int*) ; 
 int /*<<< orphan*/  decode_tones_phase (int /*<<< orphan*/ *,TYPE_3__*,int,int*) ; 
 void* get_bits1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_subband_flags (int /*<<< orphan*/ *,scalar_t__*,int) ; 
 int get_vlc2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_4__* tone_vlc_tabs ; 

__attribute__((used)) static int decode_tones_info(GetBitContext *gb, Atrac3pChanUnitCtx *ctx,
                             int num_channels, AVCodecContext *avctx)
{
    int ch_num, i, ret;
    int band_has_tones[16];

    for (ch_num = 0; ch_num < num_channels; ch_num++)
        memset(ctx->channels[ch_num].tones_info, 0,
               sizeof(*ctx->channels[ch_num].tones_info) * ATRAC3P_SUBBANDS);

    ctx->waves_info->tones_present = get_bits1(gb);
    if (!ctx->waves_info->tones_present)
        return 0;

    memset(ctx->waves_info->waves, 0, sizeof(ctx->waves_info->waves));

    ctx->waves_info->amplitude_mode = get_bits1(gb);
    if (!ctx->waves_info->amplitude_mode) {
        avpriv_report_missing_feature(avctx, "GHA amplitude mode 0");
        return AVERROR_PATCHWELCOME;
    }

    ctx->waves_info->num_tone_bands =
        get_vlc2(gb, tone_vlc_tabs[0].table,
                 tone_vlc_tabs[0].bits, 1) + 1;

    if (num_channels == 2) {
        get_subband_flags(gb, ctx->waves_info->tone_sharing, ctx->waves_info->num_tone_bands);
        get_subband_flags(gb, ctx->waves_info->tone_master,  ctx->waves_info->num_tone_bands);
        get_subband_flags(gb, ctx->waves_info->invert_phase, ctx->waves_info->num_tone_bands);
    }

    ctx->waves_info->tones_index = 0;

    for (ch_num = 0; ch_num < num_channels; ch_num++) {
        for (i = 0; i < ctx->waves_info->num_tone_bands; i++)
            band_has_tones[i] = !ch_num ? 1 : !ctx->waves_info->tone_sharing[i];

        decode_tones_envelope(gb, ctx, ch_num, band_has_tones);
        if ((ret = decode_band_numwavs(gb, ctx, ch_num, band_has_tones,
                                       avctx)) < 0)
            return ret;

        decode_tones_frequency(gb, ctx, ch_num, band_has_tones);
        decode_tones_amplitude(gb, ctx, ch_num, band_has_tones);
        decode_tones_phase(gb, ctx, ch_num, band_has_tones);
    }

    if (num_channels == 2) {
        for (i = 0; i < ctx->waves_info->num_tone_bands; i++) {
            if (ctx->waves_info->tone_sharing[i])
                ctx->channels[1].tones_info[i] = ctx->channels[0].tones_info[i];

            if (ctx->waves_info->tone_master[i])
                FFSWAP(Atrac3pWavesData, ctx->channels[0].tones_info[i],
                       ctx->channels[1].tones_info[i]);
        }
    }

    return 0;
}