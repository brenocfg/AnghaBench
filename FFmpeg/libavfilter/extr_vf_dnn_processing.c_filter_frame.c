#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int channels; } ;
struct TYPE_14__ {TYPE_2__* priv; TYPE_3__** outputs; } ;
struct TYPE_13__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; TYPE_4__* dst; } ;
struct TYPE_12__ {TYPE_5__ output; int /*<<< orphan*/  model; TYPE_1__* dnn_module; int /*<<< orphan*/  input; } ;
struct TYPE_11__ {scalar_t__ (* execute_model ) (int /*<<< orphan*/ ,TYPE_5__*,int) ;} ;
typedef  TYPE_2__ DnnProcessingContext ;
typedef  scalar_t__ DNNReturnType ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ DNN_SUCCESS ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_frame_copy_props (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_frame_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  copy_from_dnn_to_frame (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  copy_from_frame_to_dnn (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ff_filter_frame (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ff_get_video_buffer (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,TYPE_5__*,int) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *in)
{
    AVFilterContext *context  = inlink->dst;
    AVFilterLink *outlink = context->outputs[0];
    DnnProcessingContext *ctx = context->priv;
    DNNReturnType dnn_result;
    AVFrame *out;

    copy_from_frame_to_dnn(&ctx->input, in);

    dnn_result = (ctx->dnn_module->execute_model)(ctx->model, &ctx->output, 1);
    if (dnn_result != DNN_SUCCESS){
        av_log(ctx, AV_LOG_ERROR, "failed to execute model\n");
        av_frame_free(&in);
        return AVERROR(EIO);
    }
    av_assert0(ctx->output.channels == 3);

    out = ff_get_video_buffer(outlink, outlink->w, outlink->h);
    if (!out) {
        av_frame_free(&in);
        return AVERROR(ENOMEM);
    }

    av_frame_copy_props(out, in);
    copy_from_dnn_to_frame(out, &ctx->output);
    av_frame_free(&in);
    return ff_filter_frame(outlink, out);
}