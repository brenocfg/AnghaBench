#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int frame_len_bits; int block_len_bits; float** windows; int /*<<< orphan*/ ** coefs; int /*<<< orphan*/ * output; int /*<<< orphan*/ * frame_out; TYPE_1__* fdsp; TYPE_3__* mdct_ctx; } ;
typedef  TYPE_2__ WMACodecContext ;
struct TYPE_14__ {int channels; TYPE_2__* priv_data; } ;
struct TYPE_13__ {int nb_samples; scalar_t__ extended_data; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* mdct_calc ) (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
struct TYPE_10__ {int /*<<< orphan*/  (* vector_fmul ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,float const*,int) ;int /*<<< orphan*/  (* vector_fmul_reverse ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,float const*,int) ;int /*<<< orphan*/  (* vector_fmul_scalar ) (int /*<<< orphan*/ ,float*,float,int) ;} ;
typedef  TYPE_3__ FFTContext ;
typedef  TYPE_4__ AVFrame ;
typedef  TYPE_5__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  isfinite (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,float*,float,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,float const*,int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,float const*,int) ; 
 int /*<<< orphan*/  stub4 (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int apply_window_and_mdct(AVCodecContext *avctx, const AVFrame *frame)
{
    WMACodecContext *s = avctx->priv_data;
    float **audio      = (float **) frame->extended_data;
    int len            = frame->nb_samples;
    int window_index   = s->frame_len_bits - s->block_len_bits;
    FFTContext *mdct   = &s->mdct_ctx[window_index];
    int ch;
    const float *win   = s->windows[window_index];
    int window_len     = 1 << s->block_len_bits;
    float n            = 2.0 * 32768.0 / window_len;

    for (ch = 0; ch < avctx->channels; ch++) {
        memcpy(s->output, s->frame_out[ch], window_len * sizeof(*s->output));
        s->fdsp->vector_fmul_scalar(s->frame_out[ch], audio[ch], n, len);
        s->fdsp->vector_fmul_reverse(&s->output[window_len], s->frame_out[ch],
                                    win, len);
        s->fdsp->vector_fmul(s->frame_out[ch], s->frame_out[ch], win, len);
        mdct->mdct_calc(mdct, s->coefs[ch], s->output);
        if (!isfinite(s->coefs[ch][0])) {
            av_log(avctx, AV_LOG_ERROR, "Input contains NaN/+-Inf\n");
            return AVERROR(EINVAL);
        }
    }

    return 0;
}