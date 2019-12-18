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
struct TYPE_11__ {int freq_index; } ;
struct TYPE_10__ {int num_wavs; size_t start_index; } ;
struct TYPE_9__ {int num_tone_bands; TYPE_4__* waves; } ;
struct TYPE_8__ {TYPE_3__* tones_info; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_3__ Atrac3pWavesData ;
typedef  TYPE_4__ Atrac3pWaveParam ;
typedef  TYPE_5__ Atrac3pChanUnitCtx ;

/* Variables and functions */
 int av_log2 (int) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits1 (int /*<<< orphan*/ *) ; 
 int get_vlc2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int sign_extend (int,int) ; 
 TYPE_6__* tone_vlc_tabs ; 

__attribute__((used)) static void decode_tones_frequency(GetBitContext *gb, Atrac3pChanUnitCtx *ctx,
                                   int ch_num, int band_has_tones[])
{
    int sb, i, direction, nbits, pred, delta;
    Atrac3pWaveParam *iwav, *owav;
    Atrac3pWavesData *dst = ctx->channels[ch_num].tones_info;
    Atrac3pWavesData *ref = ctx->channels[0].tones_info;

    if (!ch_num || !get_bits1(gb)) { /* mode 0: fixed-length coding */
        for (sb = 0; sb < ctx->waves_info->num_tone_bands; sb++) {
            if (!band_has_tones[sb] || !dst[sb].num_wavs)
                continue;
            iwav      = &ctx->waves_info->waves[dst[sb].start_index];
            direction = (dst[sb].num_wavs > 1) ? get_bits1(gb) : 0;
            if (direction) { /** packed numbers in descending order */
                if (dst[sb].num_wavs)
                    iwav[dst[sb].num_wavs - 1].freq_index = get_bits(gb, 10);
                for (i = dst[sb].num_wavs - 2; i >= 0 ; i--) {
                    nbits = av_log2(iwav[i+1].freq_index) + 1;
                    iwav[i].freq_index = get_bits(gb, nbits);
                }
            } else { /** packed numbers in ascending order */
                for (i = 0; i < dst[sb].num_wavs; i++) {
                    if (!i || iwav[i - 1].freq_index < 512)
                        iwav[i].freq_index = get_bits(gb, 10);
                    else {
                        nbits = av_log2(1023 - iwav[i - 1].freq_index) + 1;
                        iwav[i].freq_index = get_bits(gb, nbits) +
                                             1024 - (1 << nbits);
                    }
                }
            }
        }
    } else { /* mode 1: VLC modulo delta to master (slave only) */
        for (sb = 0; sb < ctx->waves_info->num_tone_bands; sb++) {
            if (!band_has_tones[sb] || !dst[sb].num_wavs)
                continue;
            iwav = &ctx->waves_info->waves[ref[sb].start_index];
            owav = &ctx->waves_info->waves[dst[sb].start_index];
            for (i = 0; i < dst[sb].num_wavs; i++) {
                delta = get_vlc2(gb, tone_vlc_tabs[6].table,
                                 tone_vlc_tabs[6].bits, 1);
                delta = sign_extend(delta, 8);
                pred  = (i < ref[sb].num_wavs) ? iwav[i].freq_index :
                        (ref[sb].num_wavs ? iwav[ref[sb].num_wavs - 1].freq_index : 0);
                owav[i].freq_index = (pred + delta) & 0x3FF;
            }
        }
    }
}