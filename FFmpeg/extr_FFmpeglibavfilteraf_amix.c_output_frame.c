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
struct TYPE_18__ {TYPE_2__* priv; } ;
struct TYPE_17__ {TYPE_5__* src; } ;
struct TYPE_16__ {scalar_t__ format; scalar_t__ pts; scalar_t__* extended_data; } ;
struct TYPE_15__ {int* input_state; int nb_inputs; scalar_t__ next_pts; int nb_channels; int /*<<< orphan*/ * input_scale; TYPE_1__* fdsp; scalar_t__ planar; int /*<<< orphan*/ * fifos; int /*<<< orphan*/  frame_list; } ;
struct TYPE_14__ {int /*<<< orphan*/  (* vector_dmac_scalar ) (double*,double*,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* vector_fmac_scalar ) (float*,float*,int /*<<< orphan*/ ,int) ;} ;
typedef  TYPE_2__ MixContext ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVFilterLink ;
typedef  TYPE_5__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVERROR_EOF ; 
 scalar_t__ AV_NOPTS_VALUE ; 
 scalar_t__ AV_SAMPLE_FMT_FLT ; 
 scalar_t__ AV_SAMPLE_FMT_FLTP ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FFALIGN (int,int) ; 
 int FFMIN (int,int) ; 
 int INPUT_EOF ; 
 int INPUT_ON ; 
 int INT_MAX ; 
 int /*<<< orphan*/  av_audio_fifo_read (int /*<<< orphan*/ ,void**,int) ; 
 int av_audio_fifo_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_3__**) ; 
 int /*<<< orphan*/  calculate_scales (TYPE_2__*,int) ; 
 int ff_filter_frame (TYPE_4__*,TYPE_3__*) ; 
 TYPE_3__* ff_get_audio_buffer (TYPE_4__*,int) ; 
 int /*<<< orphan*/  ff_outlink_set_status (TYPE_4__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int frame_list_next_frame_size (int /*<<< orphan*/ ) ; 
 scalar_t__ frame_list_next_pts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  frame_list_remove_samples (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (float*,float*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (double*,double*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int output_frame(AVFilterLink *outlink)
{
    AVFilterContext *ctx = outlink->src;
    MixContext      *s = ctx->priv;
    AVFrame *out_buf, *in_buf;
    int nb_samples, ns, i;

    if (s->input_state[0] & INPUT_ON) {
        /* first input live: use the corresponding frame size */
        nb_samples = frame_list_next_frame_size(s->frame_list);
        for (i = 1; i < s->nb_inputs; i++) {
            if (s->input_state[i] & INPUT_ON) {
                ns = av_audio_fifo_size(s->fifos[i]);
                if (ns < nb_samples) {
                    if (!(s->input_state[i] & INPUT_EOF))
                        /* unclosed input with not enough samples */
                        return 0;
                    /* closed input to drain */
                    nb_samples = ns;
                }
            }
        }
    } else {
        /* first input closed: use the available samples */
        nb_samples = INT_MAX;
        for (i = 1; i < s->nb_inputs; i++) {
            if (s->input_state[i] & INPUT_ON) {
                ns = av_audio_fifo_size(s->fifos[i]);
                nb_samples = FFMIN(nb_samples, ns);
            }
        }
        if (nb_samples == INT_MAX) {
            ff_outlink_set_status(outlink, AVERROR_EOF, s->next_pts);
            return 0;
        }
    }

    s->next_pts = frame_list_next_pts(s->frame_list);
    frame_list_remove_samples(s->frame_list, nb_samples);

    calculate_scales(s, nb_samples);

    if (nb_samples == 0)
        return 0;

    out_buf = ff_get_audio_buffer(outlink, nb_samples);
    if (!out_buf)
        return AVERROR(ENOMEM);

    in_buf = ff_get_audio_buffer(outlink, nb_samples);
    if (!in_buf) {
        av_frame_free(&out_buf);
        return AVERROR(ENOMEM);
    }

    for (i = 0; i < s->nb_inputs; i++) {
        if (s->input_state[i] & INPUT_ON) {
            int planes, plane_size, p;

            av_audio_fifo_read(s->fifos[i], (void **)in_buf->extended_data,
                               nb_samples);

            planes     = s->planar ? s->nb_channels : 1;
            plane_size = nb_samples * (s->planar ? 1 : s->nb_channels);
            plane_size = FFALIGN(plane_size, 16);

            if (out_buf->format == AV_SAMPLE_FMT_FLT ||
                out_buf->format == AV_SAMPLE_FMT_FLTP) {
                for (p = 0; p < planes; p++) {
                    s->fdsp->vector_fmac_scalar((float *)out_buf->extended_data[p],
                                                (float *) in_buf->extended_data[p],
                                                s->input_scale[i], plane_size);
                }
            } else {
                for (p = 0; p < planes; p++) {
                    s->fdsp->vector_dmac_scalar((double *)out_buf->extended_data[p],
                                                (double *) in_buf->extended_data[p],
                                                s->input_scale[i], plane_size);
                }
            }
        }
    }
    av_frame_free(&in_buf);

    out_buf->pts = s->next_pts;
    if (s->next_pts != AV_NOPTS_VALUE)
        s->next_pts += nb_samples;

    return ff_filter_frame(outlink, out_buf);
}