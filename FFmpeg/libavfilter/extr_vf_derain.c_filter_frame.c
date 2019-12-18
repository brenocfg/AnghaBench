#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_24__ {int height; int width; scalar_t__ data; } ;
struct TYPE_23__ {TYPE_3__* priv; TYPE_5__** outputs; } ;
struct TYPE_22__ {int w; int h; TYPE_6__* dst; } ;
struct TYPE_21__ {int height; int width; int* linesize; double** data; } ;
struct TYPE_19__ {scalar_t__ data; } ;
struct TYPE_20__ {TYPE_7__ output; TYPE_2__ input; int /*<<< orphan*/  model; TYPE_1__* dnn_module; } ;
struct TYPE_18__ {scalar_t__ (* execute_model ) (int /*<<< orphan*/ ,TYPE_7__*,int) ;} ;
typedef  TYPE_3__ DRContext ;
typedef  scalar_t__ DNNReturnType ;
typedef  TYPE_4__ AVFrame ;
typedef  TYPE_5__ AVFilterLink ;
typedef  TYPE_6__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 double CLIP (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ DNN_SUCCESS ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_frame_copy_props (TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_4__**) ; 
 int /*<<< orphan*/  av_log (TYPE_6__*,int /*<<< orphan*/ ,char*) ; 
 int ff_filter_frame (TYPE_5__*,TYPE_4__*) ; 
 TYPE_4__* ff_get_video_buffer (TYPE_5__*,int,int) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,TYPE_7__*,int) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *in)
{
    AVFilterContext *ctx  = inlink->dst;
    AVFilterLink *outlink = ctx->outputs[0];
    DRContext *dr_context = ctx->priv;
    DNNReturnType dnn_result;
    int pad_size;

    AVFrame *out = ff_get_video_buffer(outlink, outlink->w, outlink->h);
    if (!out) {
        av_log(ctx, AV_LOG_ERROR, "could not allocate memory for output frame\n");
        av_frame_free(&in);
        return AVERROR(ENOMEM);
    }

    av_frame_copy_props(out, in);

    for (int i = 0; i < in->height; i++){
        for(int j = 0; j < in->width * 3; j++){
            int k = i * in->linesize[0] + j;
            int t = i * in->width * 3 + j;
            ((float *)dr_context->input.data)[t] = in->data[0][k] / 255.0;
        }
    }

    dnn_result = (dr_context->dnn_module->execute_model)(dr_context->model, &dr_context->output, 1);
    if (dnn_result != DNN_SUCCESS){
        av_log(ctx, AV_LOG_ERROR, "failed to execute model\n");
        return AVERROR(EIO);
    }

    out->height = dr_context->output.height;
    out->width  = dr_context->output.width;
    outlink->h  = dr_context->output.height;
    outlink->w  = dr_context->output.width;
    pad_size    = (in->height - out->height) >> 1;

    for (int i = 0; i < out->height; i++){
        for(int j = 0; j < out->width * 3; j++){
            int k = i * out->linesize[0] + j;
            int t = i * out->width * 3 + j;

            int t_in =  (i + pad_size) * in->width * 3 + j + pad_size * 3;
            out->data[0][k] = CLIP((int)((((float *)dr_context->input.data)[t_in] - ((float *)dr_context->output.data)[t]) * 255), 0, 255);
        }
    }

    av_frame_free(&in);

    return ff_filter_frame(outlink, out);
}