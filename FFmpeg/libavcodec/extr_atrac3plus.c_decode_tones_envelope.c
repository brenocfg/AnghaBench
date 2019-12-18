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
struct TYPE_11__ {TYPE_2__* waves_info; TYPE_1__* channels; } ;
struct TYPE_9__ {int start_pos; int stop_pos; void* has_stop_point; void* has_start_point; } ;
struct TYPE_10__ {TYPE_3__ pend_env; } ;
struct TYPE_8__ {int num_tone_bands; } ;
struct TYPE_7__ {TYPE_4__* tones_info; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_4__ Atrac3pWavesData ;
typedef  TYPE_5__ Atrac3pChanUnitCtx ;

/* Variables and functions */
 int get_bits (int /*<<< orphan*/ *,int) ; 
 void* get_bits1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void decode_tones_envelope(GetBitContext *gb, Atrac3pChanUnitCtx *ctx,
                                  int ch_num, int band_has_tones[])
{
    int sb;
    Atrac3pWavesData *dst = ctx->channels[ch_num].tones_info;
    Atrac3pWavesData *ref = ctx->channels[0].tones_info;

    if (!ch_num || !get_bits1(gb)) { /* mode 0: fixed-length coding */
        for (sb = 0; sb < ctx->waves_info->num_tone_bands; sb++) {
            if (!band_has_tones[sb])
                continue;
            dst[sb].pend_env.has_start_point = get_bits1(gb);
            dst[sb].pend_env.start_pos       = dst[sb].pend_env.has_start_point
                                               ? get_bits(gb, 5) : -1;
            dst[sb].pend_env.has_stop_point  = get_bits1(gb);
            dst[sb].pend_env.stop_pos        = dst[sb].pend_env.has_stop_point
                                               ? get_bits(gb, 5) : 32;
        }
    } else { /* mode 1(slave only): copy master */
        for (sb = 0; sb < ctx->waves_info->num_tone_bands; sb++) {
            if (!band_has_tones[sb])
                continue;
            dst[sb].pend_env.has_start_point = ref[sb].pend_env.has_start_point;
            dst[sb].pend_env.has_stop_point  = ref[sb].pend_env.has_stop_point;
            dst[sb].pend_env.start_pos       = ref[sb].pend_env.start_pos;
            dst[sb].pend_env.stop_pos        = ref[sb].pend_env.stop_pos;
        }
    }
}