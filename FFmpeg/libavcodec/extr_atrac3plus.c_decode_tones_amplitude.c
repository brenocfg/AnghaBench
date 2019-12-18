#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  bits; int /*<<< orphan*/  table; } ;
struct TYPE_12__ {TYPE_2__* waves_info; TYPE_1__* channels; } ;
struct TYPE_11__ {int amp_sf; scalar_t__ freq_index; } ;
struct TYPE_10__ {int num_wavs; size_t start_index; } ;
struct TYPE_9__ {int num_tone_bands; TYPE_4__* waves; int /*<<< orphan*/  amplitude_mode; } ;
struct TYPE_8__ {TYPE_3__* tones_info; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_3__ Atrac3pWavesData ;
typedef  TYPE_4__ Atrac3pWaveParam ;
typedef  TYPE_5__ Atrac3pChanUnitCtx ;

/* Variables and functions */
 int FFABS (scalar_t__) ; 
 void* get_bits (int /*<<< orphan*/ *,int) ; 
 int get_vlc2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int sign_extend (int,int) ; 
 TYPE_6__* tone_vlc_tabs ; 

__attribute__((used)) static void decode_tones_amplitude(GetBitContext *gb, Atrac3pChanUnitCtx *ctx,
                                   int ch_num, int band_has_tones[])
{
    int mode, sb, j, i, diff, maxdiff, fi, delta, pred;
    Atrac3pWaveParam *wsrc, *wref;
    int refwaves[48] = { 0 };
    Atrac3pWavesData *dst = ctx->channels[ch_num].tones_info;
    Atrac3pWavesData *ref = ctx->channels[0].tones_info;

    if (ch_num) {
        for (sb = 0; sb < ctx->waves_info->num_tone_bands; sb++) {
            if (!band_has_tones[sb] || !dst[sb].num_wavs)
                continue;
            wsrc = &ctx->waves_info->waves[dst[sb].start_index];
            wref = &ctx->waves_info->waves[ref[sb].start_index];
            for (j = 0; j < dst[sb].num_wavs; j++) {
                for (i = 0, fi = 0, maxdiff = 1024; i < ref[sb].num_wavs; i++) {
                    diff = FFABS(wsrc[j].freq_index - wref[i].freq_index);
                    if (diff < maxdiff) {
                        maxdiff = diff;
                        fi      = i;
                    }
                }

                if (maxdiff < 8)
                    refwaves[dst[sb].start_index + j] = fi + ref[sb].start_index;
                else if (j < ref[sb].num_wavs)
                    refwaves[dst[sb].start_index + j] = j + ref[sb].start_index;
                else
                    refwaves[dst[sb].start_index + j] = -1;
            }
        }
    }

    mode = get_bits(gb, ch_num + 1);

    switch (mode) {
    case 0: /** fixed-length coding */
        for (sb = 0; sb < ctx->waves_info->num_tone_bands; sb++) {
            if (!band_has_tones[sb] || !dst[sb].num_wavs)
                continue;
            if (ctx->waves_info->amplitude_mode)
                for (i = 0; i < dst[sb].num_wavs; i++)
                    ctx->waves_info->waves[dst[sb].start_index + i].amp_sf = get_bits(gb, 6);
            else
                ctx->waves_info->waves[dst[sb].start_index].amp_sf = get_bits(gb, 6);
        }
        break;
    case 1: /** min + VLC delta */
        for (sb = 0; sb < ctx->waves_info->num_tone_bands; sb++) {
            if (!band_has_tones[sb] || !dst[sb].num_wavs)
                continue;
            if (ctx->waves_info->amplitude_mode)
                for (i = 0; i < dst[sb].num_wavs; i++)
                    ctx->waves_info->waves[dst[sb].start_index + i].amp_sf =
                        get_vlc2(gb, tone_vlc_tabs[3].table,
                                 tone_vlc_tabs[3].bits, 1) + 20;
            else
                ctx->waves_info->waves[dst[sb].start_index].amp_sf =
                    get_vlc2(gb, tone_vlc_tabs[4].table,
                             tone_vlc_tabs[4].bits, 1) + 24;
        }
        break;
    case 2: /** VLC modulo delta to master (slave only) */
        for (sb = 0; sb < ctx->waves_info->num_tone_bands; sb++) {
            if (!band_has_tones[sb] || !dst[sb].num_wavs)
                continue;
            for (i = 0; i < dst[sb].num_wavs; i++) {
                delta = get_vlc2(gb, tone_vlc_tabs[5].table,
                                 tone_vlc_tabs[5].bits, 1);
                delta = sign_extend(delta, 5);
                pred  = refwaves[dst[sb].start_index + i] >= 0 ?
                        ctx->waves_info->waves[refwaves[dst[sb].start_index + i]].amp_sf : 34;
                ctx->waves_info->waves[dst[sb].start_index + i].amp_sf = (pred + delta) & 0x3F;
            }
        }
        break;
    case 3: /** clone master (slave only) */
        for (sb = 0; sb < ctx->waves_info->num_tone_bands; sb++) {
            if (!band_has_tones[sb])
                continue;
            for (i = 0; i < dst[sb].num_wavs; i++)
                ctx->waves_info->waves[dst[sb].start_index + i].amp_sf =
                    refwaves[dst[sb].start_index + i] >= 0
                    ? ctx->waves_info->waves[refwaves[dst[sb].start_index + i]].amp_sf
                    : 32;
        }
        break;
    }
}