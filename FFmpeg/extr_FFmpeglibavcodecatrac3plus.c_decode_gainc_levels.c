#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  bits; int /*<<< orphan*/  table; } ;
struct TYPE_11__ {int num_points; int* lev_code; } ;
struct TYPE_10__ {TYPE_3__* gain_data; } ;
struct TYPE_9__ {TYPE_2__* channels; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_1__ Atrac3pChanUnitCtx ;
typedef  TYPE_2__ Atrac3pChanParams ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 TYPE_7__* gain_vlc_tabs ; 
 int /*<<< orphan*/  gainc_level_mode1m (int /*<<< orphan*/ *,TYPE_1__*,TYPE_3__*) ; 
 int /*<<< orphan*/  gainc_level_mode3s (TYPE_3__*,TYPE_3__*) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  get_bits1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_bitsz (int /*<<< orphan*/ *,int) ; 
 int get_vlc2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int decode_gainc_levels(GetBitContext *gb, Atrac3pChanUnitCtx *ctx,
                               int ch_num, int coded_subbands)
{
    int sb, i, delta, delta_bits, min_val, pred;
    Atrac3pChanParams *chan     = &ctx->channels[ch_num];
    Atrac3pChanParams *ref_chan = &ctx->channels[0];

    switch (get_bits(gb, 2)) { /* switch according to coding mode */
    case 0: /* fixed-length coding */
        for (sb = 0; sb < coded_subbands; sb++)
            for (i = 0; i < chan->gain_data[sb].num_points; i++)
                chan->gain_data[sb].lev_code[i] = get_bits(gb, 4);
        break;
    case 1:
        if (ch_num) { /* VLC modulo delta to master channel */
            for (sb = 0; sb < coded_subbands; sb++)
                for (i = 0; i < chan->gain_data[sb].num_points; i++) {
                    delta = get_vlc2(gb, gain_vlc_tabs[5].table,
                                     gain_vlc_tabs[5].bits, 1);
                    pred = (i >= ref_chan->gain_data[sb].num_points)
                           ? 7 : ref_chan->gain_data[sb].lev_code[i];
                    chan->gain_data[sb].lev_code[i] = (pred + delta) & 0xF;
                }
        } else { /* VLC modulo delta to previous */
            for (sb = 0; sb < coded_subbands; sb++)
                gainc_level_mode1m(gb, ctx, &chan->gain_data[sb]);
        }
        break;
    case 2:
        if (ch_num) { /* VLC modulo delta to previous or clone master */
            for (sb = 0; sb < coded_subbands; sb++)
                if (chan->gain_data[sb].num_points > 0) {
                    if (get_bits1(gb))
                        gainc_level_mode1m(gb, ctx, &chan->gain_data[sb]);
                    else
                        gainc_level_mode3s(&chan->gain_data[sb],
                                           &ref_chan->gain_data[sb]);
                }
        } else { /* VLC modulo delta to lev_codes of previous subband */
            if (chan->gain_data[0].num_points > 0)
                gainc_level_mode1m(gb, ctx, &chan->gain_data[0]);

            for (sb = 1; sb < coded_subbands; sb++)
                for (i = 0; i < chan->gain_data[sb].num_points; i++) {
                    delta = get_vlc2(gb, gain_vlc_tabs[4].table,
                                     gain_vlc_tabs[4].bits, 1);
                    pred = (i >= chan->gain_data[sb - 1].num_points)
                           ? 7 : chan->gain_data[sb - 1].lev_code[i];
                    chan->gain_data[sb].lev_code[i] = (pred + delta) & 0xF;
                }
        }
        break;
    case 3:
        if (ch_num) { /* clone master */
            for (sb = 0; sb < coded_subbands; sb++)
                gainc_level_mode3s(&chan->gain_data[sb],
                                   &ref_chan->gain_data[sb]);
        } else { /* shorter delta to min */
            delta_bits = get_bits(gb, 2);
            min_val    = get_bits(gb, 4);

            for (sb = 0; sb < coded_subbands; sb++)
                for (i = 0; i < chan->gain_data[sb].num_points; i++) {
                    chan->gain_data[sb].lev_code[i] = min_val + get_bitsz(gb, delta_bits);
                    if (chan->gain_data[sb].lev_code[i] > 15)
                        return AVERROR_INVALIDDATA;
                }
        }
        break;
    }

    return 0;
}