#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_1__* priv; } ;
struct TYPE_13__ {TYPE_4__* dst; } ;
struct TYPE_12__ {scalar_t__ extended_data; int /*<<< orphan*/  pts; } ;
struct TYPE_11__ {scalar_t__ hop_size; int /*<<< orphan*/  fifo; int /*<<< orphan*/  win_size; int /*<<< orphan*/  pts; } ;
typedef  TYPE_1__ ShowFreqsContext ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_audio_fifo_drain (int /*<<< orphan*/ ,scalar_t__) ; 
 int av_audio_fifo_peek (int /*<<< orphan*/ ,void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_2__**) ; 
 TYPE_2__* ff_get_audio_buffer (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int plot_freqs (TYPE_3__*,TYPE_2__*) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink)
{
    AVFilterContext *ctx = inlink->dst;
    ShowFreqsContext *s = ctx->priv;
    AVFrame *fin = NULL;
    int ret = 0;

    fin = ff_get_audio_buffer(inlink, s->win_size);
    if (!fin) {
        ret = AVERROR(ENOMEM);
        goto fail;
    }

    fin->pts = s->pts;
    s->pts += s->hop_size;
    ret = av_audio_fifo_peek(s->fifo, (void **)fin->extended_data, s->win_size);
    if (ret < 0)
        goto fail;

    ret = plot_freqs(inlink, fin);
    av_frame_free(&fin);
    av_audio_fifo_drain(s->fifo, s->hop_size);

fail:
    av_frame_free(&fin);
    return ret;
}