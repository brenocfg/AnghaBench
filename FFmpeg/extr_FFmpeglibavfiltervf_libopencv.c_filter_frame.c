#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_2__** outputs; TYPE_1__* priv; } ;
struct TYPE_9__ {int /*<<< orphan*/  format; int /*<<< orphan*/  h; int /*<<< orphan*/  w; TYPE_3__* dst; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* end_frame_filter ) (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ OCVContext ;
typedef  int /*<<< orphan*/  IplImage ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_2__ AVFilterLink ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_frame_copy_props (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_frame_free (int /*<<< orphan*/ **) ; 
 int ff_filter_frame (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ff_get_video_buffer (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill_frame_from_iplimage (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill_iplimage_from_frame (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *in)
{
    AVFilterContext *ctx = inlink->dst;
    OCVContext *s = ctx->priv;
    AVFilterLink *outlink= inlink->dst->outputs[0];
    AVFrame *out;
    IplImage inimg, outimg;

    out = ff_get_video_buffer(outlink, outlink->w, outlink->h);
    if (!out) {
        av_frame_free(&in);
        return AVERROR(ENOMEM);
    }
    av_frame_copy_props(out, in);

    fill_iplimage_from_frame(&inimg , in , inlink->format);
    fill_iplimage_from_frame(&outimg, out, inlink->format);
    s->end_frame_filter(ctx, &inimg, &outimg);
    fill_frame_from_iplimage(out, &outimg, inlink->format);

    av_frame_free(&in);

    return ff_filter_frame(outlink, out);
}