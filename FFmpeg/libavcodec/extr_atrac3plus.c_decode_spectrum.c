#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int* qu_wordlen; int* qu_tab_idx; size_t table_type; int /*<<< orphan*/ * power_levs; int /*<<< orphan*/ * spectrum; } ;
struct TYPE_8__ {int used_quant_units; int num_coded_subbands; TYPE_3__* channels; int /*<<< orphan*/  use_full_table; } ;
struct TYPE_7__ {int redirect; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_1__ Atrac3pSpecCodeTab ;
typedef  TYPE_2__ Atrac3pChanUnitCtx ;
typedef  TYPE_3__ Atrac3pChanParams ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  ATRAC3P_POWER_COMP_OFF ; 
 int*** atrac3p_ct_restricted_to_full ; 
 TYPE_1__* atrac3p_spectra_tabs ; 
 int* atrac3p_subband_to_num_powgrps ; 
 int /*<<< orphan*/  decode_qu_spectra (int /*<<< orphan*/ *,TYPE_1__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 size_t* ff_atrac3p_qu_to_spec_pos ; 
 int /*<<< orphan*/  get_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * spec_vlc_tabs ; 

__attribute__((used)) static void decode_spectrum(GetBitContext *gb, Atrac3pChanUnitCtx *ctx,
                            int num_channels, AVCodecContext *avctx)
{
    int i, ch_num, qu, wordlen, codetab, tab_index, num_specs;
    const Atrac3pSpecCodeTab *tab;
    Atrac3pChanParams *chan;

    for (ch_num = 0; ch_num < num_channels; ch_num++) {
        chan = &ctx->channels[ch_num];

        memset(chan->spectrum, 0, sizeof(chan->spectrum));

        /* set power compensation level to disabled */
        memset(chan->power_levs, ATRAC3P_POWER_COMP_OFF, sizeof(chan->power_levs));

        for (qu = 0; qu < ctx->used_quant_units; qu++) {
            num_specs = ff_atrac3p_qu_to_spec_pos[qu + 1] -
                        ff_atrac3p_qu_to_spec_pos[qu];

            wordlen = chan->qu_wordlen[qu];
            codetab = chan->qu_tab_idx[qu];
            if (wordlen) {
                if (!ctx->use_full_table)
                    codetab = atrac3p_ct_restricted_to_full[chan->table_type][wordlen - 1][codetab];

                tab_index = (chan->table_type * 8 + codetab) * 7 + wordlen - 1;
                tab       = &atrac3p_spectra_tabs[tab_index];

                /* this allows reusing VLC tables */
                if (tab->redirect >= 0)
                    tab_index = tab->redirect;

                decode_qu_spectra(gb, tab, &spec_vlc_tabs[tab_index],
                                  &chan->spectrum[ff_atrac3p_qu_to_spec_pos[qu]],
                                  num_specs);
            } else if (ch_num && ctx->channels[0].qu_wordlen[qu] && !codetab) {
                /* copy coefficients from master */
                memcpy(&chan->spectrum[ff_atrac3p_qu_to_spec_pos[qu]],
                       &ctx->channels[0].spectrum[ff_atrac3p_qu_to_spec_pos[qu]],
                       num_specs *
                       sizeof(chan->spectrum[ff_atrac3p_qu_to_spec_pos[qu]]));
                chan->qu_wordlen[qu] = ctx->channels[0].qu_wordlen[qu];
            }
        }

        /* Power compensation levels only present in the bitstream
         * if there are more than 2 quant units. The lowest two units
         * correspond to the frequencies 0...351 Hz, whose shouldn't
         * be affected by the power compensation. */
        if (ctx->used_quant_units > 2) {
            num_specs = atrac3p_subband_to_num_powgrps[ctx->num_coded_subbands - 1];
            for (i = 0; i < num_specs; i++)
                chan->power_levs[i] = get_bits(gb, 4);
        }
    }
}