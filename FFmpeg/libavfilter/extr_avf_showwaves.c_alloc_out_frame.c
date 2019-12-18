#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  const int16_t ;
struct TYPE_12__ {int w; int h; int channels; int /*<<< orphan*/  time_base; int /*<<< orphan*/  sample_rate; } ;
struct TYPE_11__ {int width; int height; int* linesize; scalar_t__* data; scalar_t__ pts; } ;
struct TYPE_10__ {int pixstep; TYPE_2__* outpicref; } ;
typedef  TYPE_1__ ShowWavesContext ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterLink ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_make_q (int,int /*<<< orphan*/ ) ; 
 scalar_t__ av_rescale_q (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* ff_get_video_buffer (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int alloc_out_frame(ShowWavesContext *showwaves, const int16_t *p,
                           const AVFilterLink *inlink, AVFilterLink *outlink,
                           const AVFrame *in)
{
    if (!showwaves->outpicref) {
        int j;
        AVFrame *out = showwaves->outpicref =
            ff_get_video_buffer(outlink, outlink->w, outlink->h);
        if (!out)
            return AVERROR(ENOMEM);
        out->width  = outlink->w;
        out->height = outlink->h;
        out->pts = in->pts + av_rescale_q((p - (int16_t *)in->data[0]) / inlink->channels,
                                          av_make_q(1, inlink->sample_rate),
                                          outlink->time_base);
        for (j = 0; j < outlink->h; j++)
            memset(out->data[0] + j*out->linesize[0], 0, outlink->w * showwaves->pixstep);
    }
    return 0;
}