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
struct TYPE_11__ {int /*<<< orphan*/  bits; int /*<<< orphan*/  table; } ;
typedef  TYPE_1__ VLC ;
struct TYPE_14__ {TYPE_2__* gain_data; } ;
struct TYPE_13__ {TYPE_4__* channels; } ;
struct TYPE_12__ {int num_points; int* loc_code; int /*<<< orphan*/ * lev_code; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_2__ AtracGainInfo ;
typedef  TYPE_3__ Atrac3pChanUnitCtx ;
typedef  TYPE_4__ Atrac3pChanParams ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int,int,int) ; 
 TYPE_1__* gain_vlc_tabs ; 
 int /*<<< orphan*/  gainc_loc_mode0 (int /*<<< orphan*/ *,TYPE_3__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  gainc_loc_mode1 (int /*<<< orphan*/ *,TYPE_3__*,TYPE_2__*) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  get_bits1 (int /*<<< orphan*/ *) ; 
 int get_vlc2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int decode_gainc_loc_codes(GetBitContext *gb, Atrac3pChanUnitCtx *ctx,
                                  int ch_num, int coded_subbands,
                                  AVCodecContext *avctx)
{
    int sb, i, delta, delta_bits, min_val, pred, more_than_ref;
    AtracGainInfo *dst, *ref;
    VLC *tab;
    Atrac3pChanParams *chan     = &ctx->channels[ch_num];
    Atrac3pChanParams *ref_chan = &ctx->channels[0];

    switch (get_bits(gb, 2)) { /* switch according to coding mode */
    case 0: /* sequence of numbers in ascending order */
        for (sb = 0; sb < coded_subbands; sb++)
            for (i = 0; i < chan->gain_data[sb].num_points; i++)
                gainc_loc_mode0(gb, ctx, &chan->gain_data[sb], i);
        break;
    case 1:
        if (ch_num) {
            for (sb = 0; sb < coded_subbands; sb++) {
                if (chan->gain_data[sb].num_points <= 0)
                    continue;
                dst = &chan->gain_data[sb];
                ref = &ref_chan->gain_data[sb];

                /* 1st value is vlc-coded modulo delta to master */
                delta = get_vlc2(gb, gain_vlc_tabs[10].table,
                                 gain_vlc_tabs[10].bits, 1);
                pred = ref->num_points > 0 ? ref->loc_code[0] : 0;
                dst->loc_code[0] = (pred + delta) & 0x1F;

                for (i = 1; i < dst->num_points; i++) {
                    more_than_ref = i >= ref->num_points;
                    if (dst->lev_code[i] > dst->lev_code[i - 1]) {
                        /* ascending curve */
                        if (more_than_ref) {
                            delta =
                                get_vlc2(gb, gain_vlc_tabs[9].table,
                                         gain_vlc_tabs[9].bits, 1);
                            dst->loc_code[i] = dst->loc_code[i - 1] + delta;
                        } else {
                            if (get_bits1(gb))
                                gainc_loc_mode0(gb, ctx, dst, i);  // direct coding
                            else
                                dst->loc_code[i] = ref->loc_code[i];  // clone master
                        }
                    } else { /* descending curve */
                        tab   = more_than_ref ? &gain_vlc_tabs[7]
                                              : &gain_vlc_tabs[10];
                        delta = get_vlc2(gb, tab->table, tab->bits, 1);
                        if (more_than_ref)
                            dst->loc_code[i] = dst->loc_code[i - 1] + delta;
                        else
                            dst->loc_code[i] = (ref->loc_code[i] + delta) & 0x1F;
                    }
                }
            }
        } else /* VLC delta to previous */
            for (sb = 0; sb < coded_subbands; sb++)
                gainc_loc_mode1(gb, ctx, &chan->gain_data[sb]);
        break;
    case 2:
        if (ch_num) {
            for (sb = 0; sb < coded_subbands; sb++) {
                if (chan->gain_data[sb].num_points <= 0)
                    continue;
                dst = &chan->gain_data[sb];
                ref = &ref_chan->gain_data[sb];
                if (dst->num_points > ref->num_points || get_bits1(gb))
                    gainc_loc_mode1(gb, ctx, dst);
                else /* clone master for the whole subband */
                    for (i = 0; i < chan->gain_data[sb].num_points; i++)
                        dst->loc_code[i] = ref->loc_code[i];
            }
        } else {
            /* data for the first subband is coded directly */
            for (i = 0; i < chan->gain_data[0].num_points; i++)
                gainc_loc_mode0(gb, ctx, &chan->gain_data[0], i);

            for (sb = 1; sb < coded_subbands; sb++) {
                if (chan->gain_data[sb].num_points <= 0)
                    continue;
                dst = &chan->gain_data[sb];

                /* 1st value is vlc-coded modulo delta to the corresponding
                 * value of the previous subband if any or zero */
                delta = get_vlc2(gb, gain_vlc_tabs[6].table,
                                 gain_vlc_tabs[6].bits, 1);
                pred             = dst[-1].num_points > 0
                                   ? dst[-1].loc_code[0] : 0;
                dst->loc_code[0] = (pred + delta) & 0x1F;

                for (i = 1; i < dst->num_points; i++) {
                    more_than_ref = i >= dst[-1].num_points;
                    /* Select VLC table according to curve direction and
                     * presence of prediction. */
                    tab = &gain_vlc_tabs[(dst->lev_code[i] > dst->lev_code[i - 1]) *
                                                   2 + more_than_ref + 6];
                    delta = get_vlc2(gb, tab->table, tab->bits, 1);
                    if (more_than_ref)
                        dst->loc_code[i] = dst->loc_code[i - 1] + delta;
                    else
                        dst->loc_code[i] = (dst[-1].loc_code[i] + delta) & 0x1F;
                }
            }
        }
        break;
    case 3:
        if (ch_num) { /* clone master or direct or direct coding */
            for (sb = 0; sb < coded_subbands; sb++)
                for (i = 0; i < chan->gain_data[sb].num_points; i++) {
                    if (i >= ref_chan->gain_data[sb].num_points)
                        gainc_loc_mode0(gb, ctx, &chan->gain_data[sb], i);
                    else
                        chan->gain_data[sb].loc_code[i] =
                            ref_chan->gain_data[sb].loc_code[i];
                }
        } else { /* shorter delta to min */
            delta_bits = get_bits(gb, 2) + 1;
            min_val    = get_bits(gb, 5);

            for (sb = 0; sb < coded_subbands; sb++)
                for (i = 0; i < chan->gain_data[sb].num_points; i++)
                    chan->gain_data[sb].loc_code[i] = min_val + i +
                                                      get_bits(gb, delta_bits);
        }
        break;
    }

    /* Validate decoded information */
    for (sb = 0; sb < coded_subbands; sb++) {
        dst = &chan->gain_data[sb];
        for (i = 0; i < chan->gain_data[sb].num_points; i++) {
            if (dst->loc_code[i] < 0 || dst->loc_code[i] > 31 ||
                (i && dst->loc_code[i] <= dst->loc_code[i - 1])) {
                av_log(avctx, AV_LOG_ERROR,
                       "Invalid gain location: ch=%d, sb=%d, pos=%d, val=%d\n",
                       ch_num, sb, i, dst->loc_code[i]);
                return AVERROR_INVALIDDATA;
            }
        }
    }

    return 0;
}