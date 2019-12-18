#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_1__* waves_info; TYPE_2__* channels; } ;
struct TYPE_10__ {int /*<<< orphan*/  phase_index; } ;
struct TYPE_9__ {size_t start_index; int num_wavs; } ;
struct TYPE_8__ {TYPE_3__* tones_info; } ;
struct TYPE_7__ {int num_tone_bands; TYPE_4__* waves; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_3__ Atrac3pWavesData ;
typedef  TYPE_4__ Atrac3pWaveParam ;
typedef  TYPE_5__ Atrac3pChanUnitCtx ;

/* Variables and functions */
 int /*<<< orphan*/  get_bits (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void decode_tones_phase(GetBitContext *gb, Atrac3pChanUnitCtx *ctx,
                               int ch_num, int band_has_tones[])
{
    int sb, i;
    Atrac3pWaveParam *wparam;
    Atrac3pWavesData *dst = ctx->channels[ch_num].tones_info;

    for (sb = 0; sb < ctx->waves_info->num_tone_bands; sb++) {
        if (!band_has_tones[sb])
            continue;
        wparam = &ctx->waves_info->waves[dst[sb].start_index];
        for (i = 0; i < dst[sb].num_wavs; i++)
            wparam[i].phase_index = get_bits(gb, 5);
    }
}