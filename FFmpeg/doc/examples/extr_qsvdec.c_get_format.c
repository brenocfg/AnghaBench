#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_12__ {scalar_t__ data; } ;
struct TYPE_11__ {TYPE_6__* hw_frames_ctx; int /*<<< orphan*/  coded_height; int /*<<< orphan*/  coded_width; int /*<<< orphan*/  sw_pix_fmt; TYPE_1__* opaque; } ;
struct TYPE_10__ {int format; int initial_pool_size; void* height; void* width; int /*<<< orphan*/  sw_format; TYPE_2__* hwctx; } ;
struct TYPE_9__ {int /*<<< orphan*/  frame_type; } ;
struct TYPE_8__ {int /*<<< orphan*/  hw_device_ref; } ;
typedef  TYPE_1__ DecodeContext ;
typedef  TYPE_2__ AVQSVFramesContext ;
typedef  TYPE_3__ AVHWFramesContext ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int const AV_PIX_FMT_NONE ; 
 int const AV_PIX_FMT_QSV ; 
 void* FFALIGN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET ; 
 TYPE_6__* av_hwframe_ctx_alloc (int /*<<< orphan*/ ) ; 
 int av_hwframe_ctx_init (TYPE_6__*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int get_format(AVCodecContext *avctx, const enum AVPixelFormat *pix_fmts)
{
    while (*pix_fmts != AV_PIX_FMT_NONE) {
        if (*pix_fmts == AV_PIX_FMT_QSV) {
            DecodeContext *decode = avctx->opaque;
            AVHWFramesContext  *frames_ctx;
            AVQSVFramesContext *frames_hwctx;
            int ret;

            /* create a pool of surfaces to be used by the decoder */
            avctx->hw_frames_ctx = av_hwframe_ctx_alloc(decode->hw_device_ref);
            if (!avctx->hw_frames_ctx)
                return AV_PIX_FMT_NONE;
            frames_ctx   = (AVHWFramesContext*)avctx->hw_frames_ctx->data;
            frames_hwctx = frames_ctx->hwctx;

            frames_ctx->format            = AV_PIX_FMT_QSV;
            frames_ctx->sw_format         = avctx->sw_pix_fmt;
            frames_ctx->width             = FFALIGN(avctx->coded_width,  32);
            frames_ctx->height            = FFALIGN(avctx->coded_height, 32);
            frames_ctx->initial_pool_size = 32;

            frames_hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;

            ret = av_hwframe_ctx_init(avctx->hw_frames_ctx);
            if (ret < 0)
                return AV_PIX_FMT_NONE;

            return AV_PIX_FMT_QSV;
        }

        pix_fmts++;
    }

    fprintf(stderr, "The QSV pixel format not offered in get_format()\n");

    return AV_PIX_FMT_NONE;
}