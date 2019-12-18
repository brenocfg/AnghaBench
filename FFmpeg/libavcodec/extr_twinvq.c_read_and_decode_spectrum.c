#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  enum TwinVQFrameType { ____Placeholder_TwinVQFrameType } TwinVQFrameType ;
struct TYPE_17__ {int size; int ppc_shape_len; TYPE_2__* fmode; scalar_t__ ppc_shape_cb; } ;
typedef  TYPE_4__ TwinVQModeTab ;
struct TYPE_18__ {int /*<<< orphan*/ * lpc_hist_idx; int /*<<< orphan*/ * lpc_idx2; int /*<<< orphan*/ * lpc_idx1; int /*<<< orphan*/ * g_coef; int /*<<< orphan*/ * p_coef; int /*<<< orphan*/ ** bark_use_hist; int /*<<< orphan*/ ** bark1; int /*<<< orphan*/  ppc_coeffs; int /*<<< orphan*/  main_coeffs; } ;
typedef  TYPE_5__ TwinVQFrameData ;
struct TYPE_19__ {size_t cur_frame; int* n_div; int /*<<< orphan*/  tmp_buf; TYPE_3__* fdsp; int /*<<< orphan*/ * lsp_hist; int /*<<< orphan*/  (* decode_ppc ) (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float*,float*) ;int /*<<< orphan*/  (* dec_bark_env ) (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,float,int) ;TYPE_1__* avctx; TYPE_5__* bits; TYPE_4__* mtab; } ;
typedef  TYPE_6__ TwinVQContext ;
struct TYPE_16__ {int /*<<< orphan*/  (* vector_fmul ) (float*,float*,int /*<<< orphan*/ ,int) ;} ;
struct TYPE_15__ {int sub; int cb_len_read; scalar_t__ cb1; scalar_t__ cb0; } ;
struct TYPE_14__ {int channels; } ;

/* Variables and functions */
 int TWINVQ_CHANNELS_MAX ; 
 int TWINVQ_FT_LONG ; 
 int TWINVQ_FT_PPC ; 
 int TWINVQ_LSP_COEFS_MAX ; 
 int TWINVQ_PPC_SHAPE_CB_SIZE ; 
 int TWINVQ_PPC_SHAPE_LEN_MAX ; 
 int TWINVQ_SUBBLOCKS_MAX ; 
 int /*<<< orphan*/  dec_gain (TYPE_6__*,int,float*) ; 
 int /*<<< orphan*/  dec_lpc_spectrum_inv (TYPE_6__*,float*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decode_lsp (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dequant (TYPE_6__*,int /*<<< orphan*/ ,float*,int,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,float,int) ; 
 int /*<<< orphan*/  stub2 (float*,float*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float*,float*) ; 
 int /*<<< orphan*/  stub4 (float*,float*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void read_and_decode_spectrum(TwinVQContext *tctx, float *out,
                                     enum TwinVQFrameType ftype)
{
    const TwinVQModeTab *mtab = tctx->mtab;
    TwinVQFrameData *bits     = &tctx->bits[tctx->cur_frame];
    int channels              = tctx->avctx->channels;
    int sub        = mtab->fmode[ftype].sub;
    int block_size = mtab->size / sub;
    float gain[TWINVQ_CHANNELS_MAX * TWINVQ_SUBBLOCKS_MAX];
    float ppc_shape[TWINVQ_PPC_SHAPE_LEN_MAX * TWINVQ_CHANNELS_MAX * 4];

    int i, j;

    dequant(tctx, bits->main_coeffs, out, ftype,
            mtab->fmode[ftype].cb0, mtab->fmode[ftype].cb1,
            mtab->fmode[ftype].cb_len_read);

    dec_gain(tctx, ftype, gain);

    if (ftype == TWINVQ_FT_LONG) {
        int cb_len_p = (tctx->n_div[3] + mtab->ppc_shape_len * channels - 1) /
                       tctx->n_div[3];
        dequant(tctx, bits->ppc_coeffs, ppc_shape,
                TWINVQ_FT_PPC, mtab->ppc_shape_cb,
                mtab->ppc_shape_cb + cb_len_p * TWINVQ_PPC_SHAPE_CB_SIZE,
                cb_len_p);
    }

    for (i = 0; i < channels; i++) {
        float *chunk = out + mtab->size * i;
        float lsp[TWINVQ_LSP_COEFS_MAX];

        for (j = 0; j < sub; j++) {
            tctx->dec_bark_env(tctx, bits->bark1[i][j],
                               bits->bark_use_hist[i][j], i,
                               tctx->tmp_buf, gain[sub * i + j], ftype);

            tctx->fdsp->vector_fmul(chunk + block_size * j,
                                   chunk + block_size * j,
                                   tctx->tmp_buf, block_size);
        }

        if (ftype == TWINVQ_FT_LONG)
            tctx->decode_ppc(tctx, bits->p_coef[i], bits->g_coef[i],
                             ppc_shape + i * mtab->ppc_shape_len, chunk);

        decode_lsp(tctx, bits->lpc_idx1[i], bits->lpc_idx2[i],
                   bits->lpc_hist_idx[i], lsp, tctx->lsp_hist[i]);

        dec_lpc_spectrum_inv(tctx, lsp, ftype, tctx->tmp_buf);

        for (j = 0; j < mtab->fmode[ftype].sub; j++) {
            tctx->fdsp->vector_fmul(chunk, chunk, tctx->tmp_buf, block_size);
            chunk += block_size;
        }
    }
}