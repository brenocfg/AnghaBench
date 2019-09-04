#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_10__ {int lsp_bit0; int lsp_bit1; int lsp_split; int lsp_bit2; int ppc_period_bit; int pgain_bit; TYPE_2__* fmode; } ;
typedef  TYPE_3__ TwinVQModeTab ;
struct TYPE_11__ {int window_type; size_t ftype; void** g_coef; void** p_coef; int /*<<< orphan*/  ppc_coeffs; void*** lpc_idx2; void** lpc_idx1; void** lpc_hist_idx; void** sub_gain_bits; void** gain_bits; int /*<<< orphan*/ ** bark_use_hist; void**** bark1; int /*<<< orphan*/  main_coeffs; } ;
typedef  TYPE_4__ TwinVQFrameData ;
struct TYPE_12__ {TYPE_4__* bits; TYPE_1__* avctx; TYPE_3__* mtab; } ;
typedef  TYPE_5__ TwinVQContext ;
struct TYPE_9__ {int sub; int bark_n_coef; int bark_n_bit; } ;
struct TYPE_8__ {int channels; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 size_t TWINVQ_FT_LONG ; 
 int TWINVQ_GAIN_BITS ; 
 int TWINVQ_SUB_GAIN_BITS ; 
 int TWINVQ_WINDOW_TYPE_BITS ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 size_t* ff_twinvq_wtype_to_ftype_table ; 
 void* get_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  get_bits1 (int /*<<< orphan*/ *) ; 
 int get_bits_count (int /*<<< orphan*/ *) ; 
 int init_get_bits8 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  read_cb_data (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static int twinvq_read_bitstream(AVCodecContext *avctx, TwinVQContext *tctx,
                                 const uint8_t *buf, int buf_size)
{
    TwinVQFrameData     *bits = &tctx->bits[0];
    const TwinVQModeTab *mtab = tctx->mtab;
    int channels              = tctx->avctx->channels;
    int sub;
    GetBitContext gb;
    int i, j, k, ret;

    if ((ret = init_get_bits8(&gb, buf, buf_size)) < 0)
        return ret;
    skip_bits(&gb, get_bits(&gb, 8));

    bits->window_type = get_bits(&gb, TWINVQ_WINDOW_TYPE_BITS);

    if (bits->window_type > 8) {
        av_log(avctx, AV_LOG_ERROR, "Invalid window type, broken sample?\n");
        return AVERROR_INVALIDDATA;
    }

    bits->ftype = ff_twinvq_wtype_to_ftype_table[tctx->bits[0].window_type];

    sub = mtab->fmode[bits->ftype].sub;

    read_cb_data(tctx, &gb, bits->main_coeffs, bits->ftype);

    for (i = 0; i < channels; i++)
        for (j = 0; j < sub; j++)
            for (k = 0; k < mtab->fmode[bits->ftype].bark_n_coef; k++)
                bits->bark1[i][j][k] =
                    get_bits(&gb, mtab->fmode[bits->ftype].bark_n_bit);

    for (i = 0; i < channels; i++)
        for (j = 0; j < sub; j++)
            bits->bark_use_hist[i][j] = get_bits1(&gb);

    if (bits->ftype == TWINVQ_FT_LONG) {
        for (i = 0; i < channels; i++)
            bits->gain_bits[i] = get_bits(&gb, TWINVQ_GAIN_BITS);
    } else {
        for (i = 0; i < channels; i++) {
            bits->gain_bits[i] = get_bits(&gb, TWINVQ_GAIN_BITS);
            for (j = 0; j < sub; j++)
                bits->sub_gain_bits[i * sub + j] = get_bits(&gb,
                                                       TWINVQ_SUB_GAIN_BITS);
        }
    }

    for (i = 0; i < channels; i++) {
        bits->lpc_hist_idx[i] = get_bits(&gb, mtab->lsp_bit0);
        bits->lpc_idx1[i]     = get_bits(&gb, mtab->lsp_bit1);

        for (j = 0; j < mtab->lsp_split; j++)
            bits->lpc_idx2[i][j] = get_bits(&gb, mtab->lsp_bit2);
    }

    if (bits->ftype == TWINVQ_FT_LONG) {
        read_cb_data(tctx, &gb, bits->ppc_coeffs, 3);
        for (i = 0; i < channels; i++) {
            bits->p_coef[i] = get_bits(&gb, mtab->ppc_period_bit);
            bits->g_coef[i] = get_bits(&gb, mtab->pgain_bit);
        }
    }

    return (get_bits_count(&gb) + 7) / 8;
}