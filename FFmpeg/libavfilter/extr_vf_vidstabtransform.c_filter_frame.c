#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VSTransformData ;
struct TYPE_20__ {int /*<<< orphan*/ * linesize; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ VSFrame ;
struct TYPE_21__ {int /*<<< orphan*/  trans; int /*<<< orphan*/  td; } ;
typedef  TYPE_2__ TransformContext ;
struct TYPE_26__ {int planes; } ;
struct TYPE_25__ {int planes; } ;
struct TYPE_24__ {TYPE_4__** outputs; TYPE_2__* priv; } ;
struct TYPE_23__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; TYPE_5__* dst; } ;
struct TYPE_22__ {int /*<<< orphan*/ * linesize; int /*<<< orphan*/ * data; } ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVFilterLink ;
typedef  TYPE_5__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_frame_copy_props (TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_3__**) ; 
 scalar_t__ av_frame_is_writable (TYPE_3__*) ; 
 int ff_filter_frame (TYPE_4__*,TYPE_3__*) ; 
 TYPE_3__* ff_get_video_buffer (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vsDoTransform (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vsGetNextTransform (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vsTransformFinish (int /*<<< orphan*/ *) ; 
 TYPE_9__* vsTransformGetDestFrameInfo (int /*<<< orphan*/ *) ; 
 TYPE_8__* vsTransformGetSrcFrameInfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vsTransformPrepare (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *in)
{
    AVFilterContext *ctx = inlink->dst;
    TransformContext *tc = ctx->priv;
    VSTransformData* td = &(tc->td);

    AVFilterLink *outlink = inlink->dst->outputs[0];
    int direct = 0;
    AVFrame *out;
    VSFrame inframe;
    int plane;

    if (av_frame_is_writable(in)) {
        direct = 1;
        out = in;
    } else {
        out = ff_get_video_buffer(outlink, outlink->w, outlink->h);
        if (!out) {
            av_frame_free(&in);
            return AVERROR(ENOMEM);
        }
        av_frame_copy_props(out, in);
    }

    for (plane = 0; plane < vsTransformGetSrcFrameInfo(td)->planes; plane++) {
        inframe.data[plane] = in->data[plane];
        inframe.linesize[plane] = in->linesize[plane];
    }
    if (direct) {
        vsTransformPrepare(td, &inframe, &inframe);
    } else { // separate frames
        VSFrame outframe;
        for (plane = 0; plane < vsTransformGetDestFrameInfo(td)->planes; plane++) {
            outframe.data[plane] = out->data[plane];
            outframe.linesize[plane] = out->linesize[plane];
        }
        vsTransformPrepare(td, &inframe, &outframe);
    }

    vsDoTransform(td, vsGetNextTransform(td, &tc->trans));

    vsTransformFinish(td);

    if (!direct)
        av_frame_free(&in);

    return ff_filter_frame(outlink, out);
}