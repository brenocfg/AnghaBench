#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {scalar_t__ sample_fmt; int channels; } ;
struct TYPE_17__ {int /*<<< orphan*/ * data; scalar_t__ nb_samples; } ;
struct TYPE_14__ {int /*<<< orphan*/  (* mlp_pack_output ) (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int) ;int /*<<< orphan*/  (* mlp_rematrix_channel ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,unsigned int,scalar_t__,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_16__ {int /*<<< orphan*/ ** sample_buffer; TYPE_1__ dsp; int /*<<< orphan*/  access_unit_size_pow2; int /*<<< orphan*/  noise_buffer; int /*<<< orphan*/ ** bypassed_lsbs; TYPE_5__* avctx; TYPE_2__* substream; } ;
struct TYPE_15__ {int max_matrix_channel; unsigned int num_primitive_matrices; unsigned int* matrix_out_ch; int /*<<< orphan*/  matrix_encoding; int /*<<< orphan*/  output_shift; int /*<<< orphan*/  ch_assign; scalar_t__ blockpos; int /*<<< orphan*/  lossless_check_data; int /*<<< orphan*/ * quant_step_size; int /*<<< orphan*/ * matrix_noise_shift; int /*<<< orphan*/ * matrix_coeff; int /*<<< orphan*/  noise_type; } ;
typedef  TYPE_2__ SubStream ;
typedef  TYPE_3__ MLPDecodeContext ;
typedef  TYPE_4__ AVFrame ;
typedef  TYPE_5__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ AV_SAMPLE_FMT_S32 ; 
 int /*<<< orphan*/  MSB_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*) ; 
 int ff_get_buffer (TYPE_5__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int ff_side_data_update_matrix_encoding (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill_noise_buffer (TYPE_3__*,unsigned int) ; 
 int /*<<< orphan*/  generate_2_noise_channels (TYPE_3__*,unsigned int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,unsigned int,scalar_t__,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int) ; 

__attribute__((used)) static int output_data(MLPDecodeContext *m, unsigned int substr,
                       AVFrame *frame, int *got_frame_ptr)
{
    AVCodecContext *avctx = m->avctx;
    SubStream *s = &m->substream[substr];
    unsigned int mat;
    unsigned int maxchan;
    int ret;
    int is32 = (m->avctx->sample_fmt == AV_SAMPLE_FMT_S32);

    if (m->avctx->channels != s->max_matrix_channel + 1) {
        av_log(m->avctx, AV_LOG_ERROR, "channel count mismatch\n");
        return AVERROR_INVALIDDATA;
    }

    if (!s->blockpos) {
        av_log(avctx, AV_LOG_ERROR, "No samples to output.\n");
        return AVERROR_INVALIDDATA;
    }

    maxchan = s->max_matrix_channel;
    if (!s->noise_type) {
        generate_2_noise_channels(m, substr);
        maxchan += 2;
    } else {
        fill_noise_buffer(m, substr);
    }

    /* Apply the channel matrices in turn to reconstruct the original audio
     * samples. */
    for (mat = 0; mat < s->num_primitive_matrices; mat++) {
        unsigned int dest_ch = s->matrix_out_ch[mat];
        m->dsp.mlp_rematrix_channel(&m->sample_buffer[0][0],
                                    s->matrix_coeff[mat],
                                    &m->bypassed_lsbs[0][mat],
                                    m->noise_buffer,
                                    s->num_primitive_matrices - mat,
                                    dest_ch,
                                    s->blockpos,
                                    maxchan,
                                    s->matrix_noise_shift[mat],
                                    m->access_unit_size_pow2,
                                    MSB_MASK(s->quant_step_size[dest_ch]));
    }

    /* get output buffer */
    frame->nb_samples = s->blockpos;
    if ((ret = ff_get_buffer(avctx, frame, 0)) < 0)
        return ret;
    s->lossless_check_data = m->dsp.mlp_pack_output(s->lossless_check_data,
                                                    s->blockpos,
                                                    m->sample_buffer,
                                                    frame->data[0],
                                                    s->ch_assign,
                                                    s->output_shift,
                                                    s->max_matrix_channel,
                                                    is32);

    /* Update matrix encoding side data */
    if ((ret = ff_side_data_update_matrix_encoding(frame, s->matrix_encoding)) < 0)
        return ret;

    *got_frame_ptr = 1;

    return 0;
}