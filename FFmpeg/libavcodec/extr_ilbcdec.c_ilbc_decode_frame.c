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
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int int16_t ;
struct TYPE_19__ {int start; int /*<<< orphan*/  lsf; int /*<<< orphan*/  cb_index; } ;
struct TYPE_18__ {TYPE_1__* priv_data; } ;
struct TYPE_17__ {int nb_samples; int** data; } ;
struct TYPE_16__ {int size; int /*<<< orphan*/ * data; } ;
struct TYPE_15__ {int mode; int* plc_residual; int block_samples; int* syntdenum; int* decresidual; int nsub; int last_lag; int* syntMem; int* old_syntdenum; int prev_enh_pl; int /*<<< orphan*/  hpimemx; int /*<<< orphan*/  hpimemy; scalar_t__ enhancer; int /*<<< orphan*/  plc_lpc; TYPE_6__ frame; int /*<<< orphan*/  lsfdeq; int /*<<< orphan*/  weightdenum; int /*<<< orphan*/  lpc_n; int /*<<< orphan*/  gb; } ;
typedef  int /*<<< orphan*/  ILBCFrame ;
typedef  TYPE_1__ ILBCContext ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 size_t ENH_BLOCKL ; 
 size_t LPC_FILTERORDER ; 
 int SUBL ; 
 int /*<<< orphan*/  decode_residual (TYPE_1__*,TYPE_6__*,int*,int*) ; 
 int /*<<< orphan*/  do_plc (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*,int,TYPE_1__*) ; 
 int ff_get_buffer (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filter_arfq12 (int*,int*,int*,size_t,int) ; 
 int /*<<< orphan*/  hp_out_coeffs ; 
 int /*<<< orphan*/  hp_output (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  index_conv (int /*<<< orphan*/ ) ; 
 int init_get_bits8 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  lsf_check_stability (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lsf_dequantization (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lsp_interpolate (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (int*,int*,size_t) ; 
 int /*<<< orphan*/  memset (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unpack_frame (TYPE_1__*) ; 
 int xcorr_coeff (int*,int*,size_t,int,int,int) ; 

__attribute__((used)) static int ilbc_decode_frame(AVCodecContext *avctx, void *data,
                             int *got_frame_ptr, AVPacket *avpkt)
{
    const uint8_t *buf = avpkt->data;
    AVFrame *frame     = data;
    ILBCContext *s     = avctx->priv_data;
    int mode = s->mode, ret;
    int16_t *plc_data = &s->plc_residual[LPC_FILTERORDER];

    if ((ret = init_get_bits8(&s->gb, buf, avpkt->size)) < 0)
        return ret;
    memset(&s->frame, 0, sizeof(ILBCFrame));

    frame->nb_samples = s->block_samples;
    if ((ret = ff_get_buffer(avctx, frame, 0)) < 0)
        return ret;

    if (unpack_frame(s))
        mode = 0;
    if (s->frame.start < 1 || s->frame.start > 5)
        mode = 0;

    if (mode) {
        index_conv(s->frame.cb_index);

        lsf_dequantization(s->lsfdeq, s->frame.lsf, s->lpc_n);
        lsf_check_stability(s->lsfdeq, LPC_FILTERORDER, s->lpc_n);
        lsp_interpolate(s->syntdenum, s->weightdenum,
                        s->lsfdeq, LPC_FILTERORDER, s);
        decode_residual(s, &s->frame, s->decresidual, s->syntdenum);

        do_plc(s->plc_residual, s->plc_lpc, 0,
                               s->decresidual, s->syntdenum + (LPC_FILTERORDER + 1) * (s->nsub - 1),
                               s->last_lag, s);

        memcpy(s->decresidual, s->plc_residual, s->block_samples * 2);
    }

    if (s->enhancer) {
        /* TODO */
    } else {
        int16_t lag, i;

        /* Find last lag (since the enhancer is not called to give this info) */
        if (s->mode == 20) {
            lag = xcorr_coeff(&s->decresidual[s->block_samples-60], &s->decresidual[s->block_samples-80],
                              60, 80, 20, -1);
        } else {
            lag = xcorr_coeff(&s->decresidual[s->block_samples-ENH_BLOCKL],
                              &s->decresidual[s->block_samples-ENH_BLOCKL-20],
                              ENH_BLOCKL, 100, 20, -1);
        }

        /* Store lag (it is needed if next packet is lost) */
        s->last_lag = lag;

        /* copy data and run synthesis filter */
        memcpy(plc_data, s->decresidual, s->block_samples * 2);

        /* Set up the filter state */
        memcpy(&plc_data[-LPC_FILTERORDER], s->syntMem, LPC_FILTERORDER * 2);

        for (i = 0; i < s->nsub; i++) {
            filter_arfq12(plc_data+i*SUBL, plc_data+i*SUBL,
                                      s->syntdenum + i*(LPC_FILTERORDER + 1),
                                      LPC_FILTERORDER + 1, SUBL);
        }

        /* Save the filter state */
        memcpy(s->syntMem, &plc_data[s->block_samples-LPC_FILTERORDER], LPC_FILTERORDER * 2);
    }

    memcpy(frame->data[0], plc_data, s->block_samples * 2);

    hp_output((int16_t *)frame->data[0], hp_out_coeffs,
              s->hpimemy, s->hpimemx, s->block_samples);

    memcpy(s->old_syntdenum, s->syntdenum, s->nsub*(LPC_FILTERORDER + 1) * 2);

    s->prev_enh_pl = 0;
    if (mode == 0)
        s->prev_enh_pl = 1;

    *got_frame_ptr = 1;

    return avpkt->size;
}