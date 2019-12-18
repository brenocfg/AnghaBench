#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VLC ;
struct TYPE_5__ {int /*<<< orphan*/  table_type; } ;
struct TYPE_4__ {int use_full_table; TYPE_2__* channels; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_1__ Atrac3pChanUnitCtx ;
typedef  TYPE_2__ Atrac3pChanParams ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  CODING_DIRECT ; 
 int /*<<< orphan*/  CODING_VLC ; 
 int /*<<< orphan*/  CODING_VLC_DELTA ; 
 int /*<<< orphan*/  CODING_VLC_DIFF ; 
 int /*<<< orphan*/  DEC_CT_IDX_COMMON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ct_vlc_tabs ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  get_bits1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int decode_channel_code_tab(GetBitContext *gb, Atrac3pChanUnitCtx *ctx,
                                   int ch_num, AVCodecContext *avctx)
{
    int i, num_vals, num_bits, pred;
    int mask = ctx->use_full_table ? 7 : 3; /* mask for modular arithmetic */
    VLC *vlc_tab, *delta_vlc;
    Atrac3pChanParams *chan     = &ctx->channels[ch_num];
    Atrac3pChanParams *ref_chan = &ctx->channels[0];

    chan->table_type = get_bits1(gb);

    switch (get_bits(gb, 2)) { /* switch according to coding mode */
    case 0: /* directly coded */
        num_bits = ctx->use_full_table + 2;
        DEC_CT_IDX_COMMON(CODING_DIRECT);
        break;
    case 1: /* entropy-coded */
        vlc_tab = ctx->use_full_table ? &ct_vlc_tabs[1]
                                      : ct_vlc_tabs;
        DEC_CT_IDX_COMMON(CODING_VLC);
        break;
    case 2: /* entropy-coded delta */
        if (ctx->use_full_table) {
            vlc_tab   = &ct_vlc_tabs[1];
            delta_vlc = &ct_vlc_tabs[2];
        } else {
            vlc_tab   = ct_vlc_tabs;
            delta_vlc = ct_vlc_tabs;
        }
        pred = 0;
        DEC_CT_IDX_COMMON(CODING_VLC_DELTA);
        break;
    case 3: /* entropy-coded difference to master */
        if (ch_num) {
            vlc_tab = ctx->use_full_table ? &ct_vlc_tabs[3]
                                          : ct_vlc_tabs;
            DEC_CT_IDX_COMMON(CODING_VLC_DIFF);
        }
        break;
    }

    return 0;
}