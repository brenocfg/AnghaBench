#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VagueDenoiserContext ;
struct TYPE_7__ {TYPE_1__** outputs; int /*<<< orphan*/ * priv; } ;
struct TYPE_6__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; TYPE_2__* dst; } ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_1__ AVFilterLink ;
typedef  TYPE_2__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_frame_copy_props (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_frame_free (int /*<<< orphan*/ **) ; 
 int av_frame_is_writable (int /*<<< orphan*/ *) ; 
 int ff_filter_frame (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ff_get_video_buffer (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filter (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *in)
{
    AVFilterContext *ctx  = inlink->dst;
    VagueDenoiserContext *s = ctx->priv;
    AVFilterLink *outlink = ctx->outputs[0];
    AVFrame *out;
    int direct = av_frame_is_writable(in);

    if (direct) {
        out = in;
    } else {
        out = ff_get_video_buffer(outlink, outlink->w, outlink->h);
        if (!out) {
            av_frame_free(&in);
            return AVERROR(ENOMEM);
        }

        av_frame_copy_props(out, in);
    }

    filter(s, in, out);

    if (!direct)
        av_frame_free(&in);

    return ff_filter_frame(outlink, out);
}