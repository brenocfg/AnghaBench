#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ data; } ;
struct TYPE_13__ {scalar_t__ extra_hw_frames; int /*<<< orphan*/  sw_pix_fmt; int /*<<< orphan*/  coded_height; int /*<<< orphan*/  coded_width; TYPE_1__* opaque; } ;
struct TYPE_12__ {scalar_t__ initial_pool_size; int /*<<< orphan*/  sw_format; int /*<<< orphan*/  format; void* height; void* width; TYPE_2__* hwctx; } ;
struct TYPE_11__ {int /*<<< orphan*/  frame_type; } ;
struct TYPE_10__ {int /*<<< orphan*/  hwaccel_uninit; int /*<<< orphan*/  hwaccel_get_buffer; TYPE_7__* hw_frames_ctx; } ;
typedef  TYPE_1__ InputStream ;
typedef  TYPE_2__ AVQSVFramesContext ;
typedef  TYPE_3__ AVHWFramesContext ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_PIX_FMT_QSV ; 
 int /*<<< orphan*/  ENOMEM ; 
 void* FFALIGN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET ; 
 int /*<<< orphan*/  av_buffer_unref (TYPE_7__**) ; 
 TYPE_7__* av_hwframe_ctx_alloc (int /*<<< orphan*/ ) ; 
 int av_hwframe_ctx_init (TYPE_7__*) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hw_device_ctx ; 
 int qsv_device_init (TYPE_1__*) ; 
 int /*<<< orphan*/  qsv_get_buffer ; 
 int /*<<< orphan*/  qsv_uninit ; 

int qsv_init(AVCodecContext *s)
{
    InputStream *ist = s->opaque;
    AVHWFramesContext *frames_ctx;
    AVQSVFramesContext *frames_hwctx;
    int ret;

    if (!hw_device_ctx) {
        ret = qsv_device_init(ist);
        if (ret < 0)
            return ret;
    }

    av_buffer_unref(&ist->hw_frames_ctx);
    ist->hw_frames_ctx = av_hwframe_ctx_alloc(hw_device_ctx);
    if (!ist->hw_frames_ctx)
        return AVERROR(ENOMEM);

    frames_ctx   = (AVHWFramesContext*)ist->hw_frames_ctx->data;
    frames_hwctx = frames_ctx->hwctx;

    frames_ctx->width             = FFALIGN(s->coded_width,  32);
    frames_ctx->height            = FFALIGN(s->coded_height, 32);
    frames_ctx->format            = AV_PIX_FMT_QSV;
    frames_ctx->sw_format         = s->sw_pix_fmt;
    frames_ctx->initial_pool_size = 64 + s->extra_hw_frames;
    frames_hwctx->frame_type      = MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;

    ret = av_hwframe_ctx_init(ist->hw_frames_ctx);
    if (ret < 0) {
        av_log(NULL, AV_LOG_ERROR, "Error initializing a QSV frame pool\n");
        return ret;
    }

    ist->hwaccel_get_buffer = qsv_get_buffer;
    ist->hwaccel_uninit     = qsv_uninit;

    return 0;
}