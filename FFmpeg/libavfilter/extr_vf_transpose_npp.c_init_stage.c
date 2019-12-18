#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_14__ ;

/* Type definitions */
struct TYPE_20__ {int width; int height; } ;
struct TYPE_19__ {scalar_t__ data; } ;
struct TYPE_18__ {void* height; void* width; int /*<<< orphan*/  sw_format; int /*<<< orphan*/  format; } ;
struct TYPE_17__ {TYPE_4__* frames_ctx; TYPE_1__* planes_out; TYPE_8__* frame; int /*<<< orphan*/  out_fmt; TYPE_14__* planes_in; int /*<<< orphan*/  in_fmt; } ;
struct TYPE_16__ {int width; int height; } ;
struct TYPE_15__ {int width; int height; } ;
typedef  TYPE_2__ NPPTransposeStageContext ;
typedef  TYPE_3__ AVHWFramesContext ;
typedef  TYPE_4__ AVBufferRef ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_PIX_FMT_CUDA ; 
 int /*<<< orphan*/  ENOMEM ; 
 void* FFALIGN (int,int) ; 
 int FF_ARRAY_ELEMS (TYPE_14__*) ; 
 int /*<<< orphan*/  av_buffer_unref (TYPE_4__**) ; 
 int /*<<< orphan*/  av_frame_unref (TYPE_8__*) ; 
 TYPE_4__* av_hwframe_ctx_alloc (TYPE_4__*) ; 
 int av_hwframe_ctx_init (TYPE_4__*) ; 
 int av_hwframe_get_buffer (TYPE_4__*,TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_pix_fmt_get_chroma_sub_sample (int /*<<< orphan*/ ,int*,int*) ; 

__attribute__((used)) static int init_stage(NPPTransposeStageContext *stage, AVBufferRef *device_ctx)
{
    AVBufferRef *out_ref = NULL;
    AVHWFramesContext *out_ctx;
    int in_sw, in_sh, out_sw, out_sh;
    int ret, i;

    av_pix_fmt_get_chroma_sub_sample(stage->in_fmt,  &in_sw,  &in_sh);
    av_pix_fmt_get_chroma_sub_sample(stage->out_fmt, &out_sw, &out_sh);

    if (!stage->planes_out[0].width) {
        stage->planes_out[0].width  = stage->planes_in[0].width;
        stage->planes_out[0].height = stage->planes_in[0].height;
    }

    for (i = 1; i < FF_ARRAY_ELEMS(stage->planes_in); i++) {
        stage->planes_in[i].width   = stage->planes_in[0].width   >> in_sw;
        stage->planes_in[i].height  = stage->planes_in[0].height  >> in_sh;
        stage->planes_out[i].width  = stage->planes_out[0].width  >> out_sw;
        stage->planes_out[i].height = stage->planes_out[0].height >> out_sh;
    }

    out_ref = av_hwframe_ctx_alloc(device_ctx);
    if (!out_ref)
        return AVERROR(ENOMEM);
    out_ctx = (AVHWFramesContext*)out_ref->data;

    out_ctx->format    = AV_PIX_FMT_CUDA;
    out_ctx->sw_format = stage->out_fmt;
    out_ctx->width     = FFALIGN(stage->planes_out[0].width,  32);
    out_ctx->height    = FFALIGN(stage->planes_out[0].height, 32);

    ret = av_hwframe_ctx_init(out_ref);
    if (ret < 0)
        goto fail;

    av_frame_unref(stage->frame);
    ret = av_hwframe_get_buffer(out_ref, stage->frame, 0);
    if (ret < 0)
        goto fail;

    stage->frame->width  = stage->planes_out[0].width;
    stage->frame->height = stage->planes_out[0].height;
    av_buffer_unref(&stage->frames_ctx);
    stage->frames_ctx = out_ref;

    return 0;

fail:
    av_buffer_unref(&out_ref);
    return ret;
}