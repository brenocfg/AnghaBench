#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* channels; } ;
struct TYPE_7__ {int num_gain_subbands; int /*<<< orphan*/ * gain_data; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_2__ Atrac3pChanUnitCtx ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int ATRAC3P_SUBBANDS ; 
 int decode_gainc_levels (int /*<<< orphan*/ *,TYPE_2__*,int,int) ; 
 int decode_gainc_loc_codes (int /*<<< orphan*/ *,TYPE_2__*,int,int,int /*<<< orphan*/ *) ; 
 int decode_gainc_npoints (int /*<<< orphan*/ *,TYPE_2__*,int,int) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 scalar_t__ get_bits1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int decode_gainc_data(GetBitContext *gb, Atrac3pChanUnitCtx *ctx,
                             int num_channels, AVCodecContext *avctx)
{
    int ch_num, coded_subbands, sb, ret;

    for (ch_num = 0; ch_num < num_channels; ch_num++) {
        memset(ctx->channels[ch_num].gain_data, 0,
               sizeof(*ctx->channels[ch_num].gain_data) * ATRAC3P_SUBBANDS);

        if (get_bits1(gb)) { /* gain control data present? */
            coded_subbands = get_bits(gb, 4) + 1;
            if (get_bits1(gb)) /* is high band gain data replication on? */
                ctx->channels[ch_num].num_gain_subbands = get_bits(gb, 4) + 1;
            else
                ctx->channels[ch_num].num_gain_subbands = coded_subbands;

            if ((ret = decode_gainc_npoints(gb, ctx, ch_num, coded_subbands)) < 0 ||
                (ret = decode_gainc_levels(gb, ctx, ch_num, coded_subbands))  < 0 ||
                (ret = decode_gainc_loc_codes(gb, ctx, ch_num, coded_subbands, avctx)) < 0)
                return ret;

            if (coded_subbands > 0) { /* propagate gain data if requested */
                for (sb = coded_subbands; sb < ctx->channels[ch_num].num_gain_subbands; sb++)
                    ctx->channels[ch_num].gain_data[sb] =
                        ctx->channels[ch_num].gain_data[sb - 1];
            }
        } else {
            ctx->channels[ch_num].num_gain_subbands = 0;
        }
    }

    return 0;
}