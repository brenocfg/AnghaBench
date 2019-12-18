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
struct TYPE_9__ {TYPE_1__* priv; int /*<<< orphan*/ ** outputs; int /*<<< orphan*/ ** inputs; } ;
struct TYPE_8__ {scalar_t__ pts; int /*<<< orphan*/  nb_samples; scalar_t__ extended_data; } ;
struct TYPE_7__ {scalar_t__ win_size; scalar_t__ pts; int /*<<< orphan*/  fifo; } ;
typedef  TYPE_1__ ShowFreqsContext ;
typedef  TYPE_2__ AVFrame ;
typedef  int /*<<< orphan*/  AVFilterLink ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 scalar_t__ AV_NOPTS_VALUE ; 
 int FFERROR_NOT_READY ; 
 int /*<<< orphan*/  FF_FILTER_FORWARD_STATUS (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FF_FILTER_FORWARD_STATUS_BACK (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FF_FILTER_FORWARD_WANTED (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ av_audio_fifo_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_audio_fifo_write (int /*<<< orphan*/ ,void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_2__**) ; 
 int ff_inlink_consume_samples (int /*<<< orphan*/ *,scalar_t__,scalar_t__,TYPE_2__**) ; 
 int filter_frame (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int activate(AVFilterContext *ctx)
{
    AVFilterLink *inlink = ctx->inputs[0];
    AVFilterLink *outlink = ctx->outputs[0];
    ShowFreqsContext *s = ctx->priv;
    AVFrame *in = NULL;
    int ret = 0;

    FF_FILTER_FORWARD_STATUS_BACK(outlink, inlink);

    if (av_audio_fifo_size(s->fifo) < s->win_size)
        ret = ff_inlink_consume_samples(inlink, s->win_size, s->win_size, &in);
    if (ret < 0)
        return ret;
    if (ret > 0) {
        av_audio_fifo_write(s->fifo, (void **)in->extended_data, in->nb_samples);
        if (s->pts == AV_NOPTS_VALUE)
            s->pts = in->pts;
        av_frame_free(&in);
    }

    if (av_audio_fifo_size(s->fifo) >= s->win_size) {
        ret = filter_frame(inlink);
        if (ret <= 0)
            return ret;
    }

    FF_FILTER_FORWARD_STATUS(inlink, outlink);
    FF_FILTER_FORWARD_WANTED(outlink, inlink);

    return FFERROR_NOT_READY;
}