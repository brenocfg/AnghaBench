#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  int8_t ;
struct TYPE_7__ {int channels_for_cur_subframe; int* channel_indexes_for_cur_subframe; int num_bands; size_t table_idx; TYPE_1__* channel; int /*<<< orphan*/  avctx; int /*<<< orphan*/  gb; int /*<<< orphan*/ *** sf_offsets; } ;
typedef  TYPE_2__ WMAProDecodeCtx ;
struct TYPE_9__ {int /*<<< orphan*/  table; } ;
struct TYPE_8__ {int /*<<< orphan*/  table; } ;
struct TYPE_6__ {int* scale_factors; int** saved_scale_factors; size_t scale_factor_idx; int reuse_sf; size_t table_idx; int scale_factor_step; int max_scale_factor; int /*<<< orphan*/  cur_subframe; } ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int FFMAX (int,int) ; 
 int /*<<< orphan*/  SCALEMAXDEPTH ; 
 int /*<<< orphan*/  SCALERLMAXDEPTH ; 
 int /*<<< orphan*/  SCALEVLCBITS ; 
 int /*<<< orphan*/  VLCBITS ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 void* get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits1 (int /*<<< orphan*/ *) ; 
 int get_vlc2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int* scale_rl_level ; 
 int* scale_rl_run ; 
 TYPE_4__ sf_rl_vlc ; 
 TYPE_3__ sf_vlc ; 

__attribute__((used)) static int decode_scale_factors(WMAProDecodeCtx* s)
{
    int i;

    /** should never consume more than 5344 bits
     *  MAX_CHANNELS * (1 +  MAX_BANDS * 23)
     */

    for (i = 0; i < s->channels_for_cur_subframe; i++) {
        int c = s->channel_indexes_for_cur_subframe[i];
        int* sf;
        int* sf_end;
        s->channel[c].scale_factors = s->channel[c].saved_scale_factors[!s->channel[c].scale_factor_idx];
        sf_end = s->channel[c].scale_factors + s->num_bands;

        /** resample scale factors for the new block size
         *  as the scale factors might need to be resampled several times
         *  before some  new values are transmitted, a backup of the last
         *  transmitted scale factors is kept in saved_scale_factors
         */
        if (s->channel[c].reuse_sf) {
            const int8_t* sf_offsets = s->sf_offsets[s->table_idx][s->channel[c].table_idx];
            int b;
            for (b = 0; b < s->num_bands; b++)
                s->channel[c].scale_factors[b] =
                    s->channel[c].saved_scale_factors[s->channel[c].scale_factor_idx][*sf_offsets++];
        }

        if (!s->channel[c].cur_subframe || get_bits1(&s->gb)) {

            if (!s->channel[c].reuse_sf) {
                int val;
                /** decode DPCM coded scale factors */
                s->channel[c].scale_factor_step = get_bits(&s->gb, 2) + 1;
                val = 45 / s->channel[c].scale_factor_step;
                for (sf = s->channel[c].scale_factors; sf < sf_end; sf++) {
                    val += get_vlc2(&s->gb, sf_vlc.table, SCALEVLCBITS, SCALEMAXDEPTH) - 60;
                    *sf = val;
                }
            } else {
                int i;
                /** run level decode differences to the resampled factors */
                for (i = 0; i < s->num_bands; i++) {
                    int idx;
                    int skip;
                    int val;
                    int sign;

                    idx = get_vlc2(&s->gb, sf_rl_vlc.table, VLCBITS, SCALERLMAXDEPTH);

                    if (!idx) {
                        uint32_t code = get_bits(&s->gb, 14);
                        val  =  code >> 6;
                        sign = (code & 1) - 1;
                        skip = (code & 0x3f) >> 1;
                    } else if (idx == 1) {
                        break;
                    } else {
                        skip = scale_rl_run[idx];
                        val  = scale_rl_level[idx];
                        sign = get_bits1(&s->gb)-1;
                    }

                    i += skip;
                    if (i >= s->num_bands) {
                        av_log(s->avctx, AV_LOG_ERROR,
                               "invalid scale factor coding\n");
                        return AVERROR_INVALIDDATA;
                    }
                    s->channel[c].scale_factors[i] += (val ^ sign) - sign;
                }
            }
            /** swap buffers */
            s->channel[c].scale_factor_idx = !s->channel[c].scale_factor_idx;
            s->channel[c].table_idx = s->table_idx;
            s->channel[c].reuse_sf  = 1;
        }

        /** calculate new scale factor maximum */
        s->channel[c].max_scale_factor = s->channel[c].scale_factors[0];
        for (sf = s->channel[c].scale_factors + 1; sf < sf_end; sf++) {
            s->channel[c].max_scale_factor =
                FFMAX(s->channel[c].max_scale_factor, *sf);
        }

    }
    return 0;
}