#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int width; int height; int channels; } ;
struct TYPE_18__ {int height; int width; } ;
struct TYPE_17__ {scalar_t__ (* set_input_output ) (int /*<<< orphan*/ ,TYPE_7__*,char*,char const**,int) ;int /*<<< orphan*/  model; } ;
struct TYPE_16__ {TYPE_3__** outputs; TYPE_2__* priv; } ;
struct TYPE_15__ {int w; int h; int format; TYPE_4__* dst; } ;
struct TYPE_14__ {int scale_factor; int sws_input_linesize; int sws_output_linesize; int sws_slice_h; void** sws_contexts; TYPE_6__ output; TYPE_7__ input; TYPE_5__* model; TYPE_1__* dnn_module; } ;
struct TYPE_13__ {scalar_t__ (* execute_model ) (TYPE_5__*,TYPE_6__*,int) ;} ;
typedef  TYPE_2__ SRContext ;
typedef  scalar_t__ DNNReturnType ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AV_CEIL_RSHIFT (int,int) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int AV_PIX_FMT_GRAY8 ; 
 int AV_PIX_FMT_GRAYF32 ; 
#define  AV_PIX_FMT_YUV410P 132 
#define  AV_PIX_FMT_YUV411P 131 
#define  AV_PIX_FMT_YUV420P 130 
#define  AV_PIX_FMT_YUV422P 129 
#define  AV_PIX_FMT_YUV444P 128 
 scalar_t__ DNN_SUCCESS ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  SWS_BICUBIC ; 
 int /*<<< orphan*/  av_get_pix_fmt_name (int) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,TYPE_7__*,char*,char const**,int) ; 
 scalar_t__ stub2 (TYPE_5__*,TYPE_6__*,int) ; 
 scalar_t__ stub3 (int /*<<< orphan*/ ,TYPE_7__*,char*,char const**,int) ; 
 scalar_t__ stub4 (TYPE_5__*,TYPE_6__*,int) ; 
 void* sws_getContext (int,int,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int config_props(AVFilterLink *inlink)
{
    AVFilterContext *context = inlink->dst;
    SRContext *sr_context = context->priv;
    AVFilterLink *outlink = context->outputs[0];
    DNNReturnType result;
    int sws_src_h, sws_src_w, sws_dst_h, sws_dst_w;
    const char *model_output_name = "y";

    sr_context->input.width = inlink->w * sr_context->scale_factor;
    sr_context->input.height = inlink->h * sr_context->scale_factor;
    sr_context->input.channels = 1;

    result = (sr_context->model->set_input_output)(sr_context->model->model, &sr_context->input, "x", &model_output_name, 1);
    if (result != DNN_SUCCESS){
        av_log(context, AV_LOG_ERROR, "could not set input and output for the model\n");
        return AVERROR(EIO);
    }

    result = (sr_context->dnn_module->execute_model)(sr_context->model, &sr_context->output, 1);
    if (result != DNN_SUCCESS){
        av_log(context, AV_LOG_ERROR, "failed to execute loaded model\n");
        return AVERROR(EIO);
    }

    if (sr_context->input.height != sr_context->output.height || sr_context->input.width != sr_context->output.width){
        sr_context->input.width = inlink->w;
        sr_context->input.height = inlink->h;
        result = (sr_context->model->set_input_output)(sr_context->model->model, &sr_context->input, "x", &model_output_name, 1);
        if (result != DNN_SUCCESS){
            av_log(context, AV_LOG_ERROR, "could not set input and output for the model\n");
            return AVERROR(EIO);
        }
        result = (sr_context->dnn_module->execute_model)(sr_context->model, &sr_context->output, 1);
        if (result != DNN_SUCCESS){
            av_log(context, AV_LOG_ERROR, "failed to execute loaded model\n");
            return AVERROR(EIO);
        }
        sr_context->scale_factor = 0;
    }
    outlink->h = sr_context->output.height;
    outlink->w = sr_context->output.width;
    sr_context->sws_contexts[1] = sws_getContext(sr_context->input.width, sr_context->input.height, AV_PIX_FMT_GRAY8,
                                                 sr_context->input.width, sr_context->input.height, AV_PIX_FMT_GRAYF32,
                                                 0, NULL, NULL, NULL);
    sr_context->sws_input_linesize = sr_context->input.width << 2;
    sr_context->sws_contexts[2] = sws_getContext(sr_context->output.width, sr_context->output.height, AV_PIX_FMT_GRAYF32,
                                                 sr_context->output.width, sr_context->output.height, AV_PIX_FMT_GRAY8,
                                                 0, NULL, NULL, NULL);
    sr_context->sws_output_linesize = sr_context->output.width << 2;
    if (!sr_context->sws_contexts[1] || !sr_context->sws_contexts[2]){
        av_log(context, AV_LOG_ERROR, "could not create SwsContext for conversions\n");
        return AVERROR(ENOMEM);
    }
    if (sr_context->scale_factor){
        sr_context->sws_contexts[0] = sws_getContext(inlink->w, inlink->h, inlink->format,
                                                     outlink->w, outlink->h, outlink->format,
                                                     SWS_BICUBIC, NULL, NULL, NULL);
        if (!sr_context->sws_contexts[0]){
            av_log(context, AV_LOG_ERROR, "could not create SwsContext for scaling\n");
            return AVERROR(ENOMEM);
        }
        sr_context->sws_slice_h = inlink->h;
    } else {
        if (inlink->format != AV_PIX_FMT_GRAY8){
            sws_src_h = sr_context->input.height;
            sws_src_w = sr_context->input.width;
            sws_dst_h = sr_context->output.height;
            sws_dst_w = sr_context->output.width;

            switch (inlink->format){
            case AV_PIX_FMT_YUV420P:
                sws_src_h = AV_CEIL_RSHIFT(sws_src_h, 1);
                sws_src_w = AV_CEIL_RSHIFT(sws_src_w, 1);
                sws_dst_h = AV_CEIL_RSHIFT(sws_dst_h, 1);
                sws_dst_w = AV_CEIL_RSHIFT(sws_dst_w, 1);
                break;
            case AV_PIX_FMT_YUV422P:
                sws_src_w = AV_CEIL_RSHIFT(sws_src_w, 1);
                sws_dst_w = AV_CEIL_RSHIFT(sws_dst_w, 1);
                break;
            case AV_PIX_FMT_YUV444P:
                break;
            case AV_PIX_FMT_YUV410P:
                sws_src_h = AV_CEIL_RSHIFT(sws_src_h, 2);
                sws_src_w = AV_CEIL_RSHIFT(sws_src_w, 2);
                sws_dst_h = AV_CEIL_RSHIFT(sws_dst_h, 2);
                sws_dst_w = AV_CEIL_RSHIFT(sws_dst_w, 2);
                break;
            case AV_PIX_FMT_YUV411P:
                sws_src_w = AV_CEIL_RSHIFT(sws_src_w, 2);
                sws_dst_w = AV_CEIL_RSHIFT(sws_dst_w, 2);
                break;
            default:
                av_log(context, AV_LOG_ERROR,
                       "could not create SwsContext for scaling for given input pixel format: %s\n",
                       av_get_pix_fmt_name(inlink->format));
                return AVERROR(EIO);
            }
            sr_context->sws_contexts[0] = sws_getContext(sws_src_w, sws_src_h, AV_PIX_FMT_GRAY8,
                                                         sws_dst_w, sws_dst_h, AV_PIX_FMT_GRAY8,
                                                         SWS_BICUBIC, NULL, NULL, NULL);
            if (!sr_context->sws_contexts[0]){
                av_log(context, AV_LOG_ERROR, "could not create SwsContext for scaling\n");
                return AVERROR(ENOMEM);
            }
            sr_context->sws_slice_h = sws_src_h;
        }
    }

    return 0;
}