#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  bits; int /*<<< orphan*/  table; } ;
typedef  TYPE_1__ VLC ;
struct TYPE_12__ {int fill_mode; size_t* qu_wordlen; int num_coded_vals; int split_point; } ;
struct TYPE_11__ {int num_quant_units; TYPE_3__* channels; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_2__ Atrac3pChanUnitCtx ;
typedef  TYPE_3__ Atrac3pChanParams ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int FF_ARRAY_ELEMS (int*) ; 
 int add_wordlen_weights (TYPE_2__*,TYPE_3__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ *** atrac3p_wl_shapes ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 size_t get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_bitsz (int /*<<< orphan*/ *,int) ; 
 int get_vlc2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int num_coded_units (int /*<<< orphan*/ *,TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unpack_vq_shape (int,int /*<<< orphan*/ *,int*,int) ; 
 TYPE_1__* wl_vlc_tabs ; 

__attribute__((used)) static int decode_channel_wordlen(GetBitContext *gb, Atrac3pChanUnitCtx *ctx,
                                  int ch_num, AVCodecContext *avctx)
{
    int i, weight_idx = 0, delta, diff, pos, delta_bits, min_val, flag,
        ret, start_val;
    VLC *vlc_tab;
    Atrac3pChanParams *chan     = &ctx->channels[ch_num];
    Atrac3pChanParams *ref_chan = &ctx->channels[0];

    chan->fill_mode = 0;

    switch (get_bits(gb, 2)) { /* switch according to coding mode */
    case 0: /* coded using constant number of bits */
        for (i = 0; i < ctx->num_quant_units; i++)
            chan->qu_wordlen[i] = get_bits(gb, 3);
        break;
    case 1:
        if (ch_num) {
            if ((ret = num_coded_units(gb, chan, ctx, avctx)) < 0)
                return ret;

            if (chan->num_coded_vals) {
                vlc_tab = &wl_vlc_tabs[get_bits(gb, 2)];

                for (i = 0; i < chan->num_coded_vals; i++) {
                    delta = get_vlc2(gb, vlc_tab->table, vlc_tab->bits, 1);
                    chan->qu_wordlen[i] = (ref_chan->qu_wordlen[i] + delta) & 7;
                }
            }
        } else {
            weight_idx = get_bits(gb, 2);
            if ((ret = num_coded_units(gb, chan, ctx, avctx)) < 0)
                return ret;

            if (chan->num_coded_vals) {
                pos = get_bits(gb, 5);
                if (pos > chan->num_coded_vals) {
                    av_log(avctx, AV_LOG_ERROR,
                           "WL mode 1: invalid position!\n");
                    return AVERROR_INVALIDDATA;
                }

                delta_bits = get_bits(gb, 2);
                min_val    = get_bits(gb, 3);

                for (i = 0; i < pos; i++)
                    chan->qu_wordlen[i] = get_bits(gb, 3);

                for (i = pos; i < chan->num_coded_vals; i++)
                    chan->qu_wordlen[i] = (min_val + get_bitsz(gb, delta_bits)) & 7;
            }
        }
        break;
    case 2:
        if ((ret = num_coded_units(gb, chan, ctx, avctx)) < 0)
            return ret;

        if (ch_num && chan->num_coded_vals) {
            vlc_tab = &wl_vlc_tabs[get_bits(gb, 2)];
            delta = get_vlc2(gb, vlc_tab->table, vlc_tab->bits, 1);
            chan->qu_wordlen[0] = (ref_chan->qu_wordlen[0] + delta) & 7;

            for (i = 1; i < chan->num_coded_vals; i++) {
                diff = ref_chan->qu_wordlen[i] - ref_chan->qu_wordlen[i - 1];
                delta = get_vlc2(gb, vlc_tab->table, vlc_tab->bits, 1);
                chan->qu_wordlen[i] = (chan->qu_wordlen[i - 1] + diff + delta) & 7;
            }
        } else if (chan->num_coded_vals) {
            flag    = get_bits(gb, 1);
            vlc_tab = &wl_vlc_tabs[get_bits(gb, 1)];

            start_val = get_bits(gb, 3);
            unpack_vq_shape(start_val,
                            &atrac3p_wl_shapes[start_val][get_bits(gb, 4)][0],
                            chan->qu_wordlen, chan->num_coded_vals);

            if (!flag) {
                for (i = 0; i < chan->num_coded_vals; i++) {
                    delta = get_vlc2(gb, vlc_tab->table, vlc_tab->bits, 1);
                    chan->qu_wordlen[i] = (chan->qu_wordlen[i] + delta) & 7;
                }
            } else {
                for (i = 0; i < (chan->num_coded_vals & - 2); i += 2)
                    if (!get_bits1(gb)) {
                        chan->qu_wordlen[i]     = (chan->qu_wordlen[i] +
                                                   get_vlc2(gb, vlc_tab->table,
                                                            vlc_tab->bits, 1)) & 7;
                        chan->qu_wordlen[i + 1] = (chan->qu_wordlen[i + 1] +
                                                   get_vlc2(gb, vlc_tab->table,
                                                            vlc_tab->bits, 1)) & 7;
                    }

                if (chan->num_coded_vals & 1)
                    chan->qu_wordlen[i] = (chan->qu_wordlen[i] +
                                           get_vlc2(gb, vlc_tab->table,
                                                    vlc_tab->bits, 1)) & 7;
            }
        }
        break;
    case 3:
        weight_idx = get_bits(gb, 2);
        if ((ret = num_coded_units(gb, chan, ctx, avctx)) < 0)
            return ret;

        if (chan->num_coded_vals) {
            vlc_tab = &wl_vlc_tabs[get_bits(gb, 2)];

            /* first coefficient is coded directly */
            chan->qu_wordlen[0] = get_bits(gb, 3);

            for (i = 1; i < chan->num_coded_vals; i++) {
                delta = get_vlc2(gb, vlc_tab->table, vlc_tab->bits, 1);
                chan->qu_wordlen[i] = (chan->qu_wordlen[i - 1] + delta) & 7;
            }
        }
        break;
    }

    if (chan->fill_mode == 2) {
        for (i = chan->num_coded_vals; i < ctx->num_quant_units; i++)
            chan->qu_wordlen[i] = ch_num ? get_bits1(gb) : 1;
    } else if (chan->fill_mode == 3) {
        pos = ch_num ? chan->num_coded_vals + chan->split_point
                     : ctx->num_quant_units - chan->split_point;
        if (pos > FF_ARRAY_ELEMS(chan->qu_wordlen)) {
            av_log(avctx, AV_LOG_ERROR, "Split point beyond array\n");
            pos = FF_ARRAY_ELEMS(chan->qu_wordlen);
        }
        for (i = chan->num_coded_vals; i < pos; i++)
            chan->qu_wordlen[i] = 1;
    }

    if (weight_idx)
        return add_wordlen_weights(ctx, chan, weight_idx, avctx);

    return 0;
}