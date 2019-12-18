#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ data; } ;
struct TYPE_12__ {scalar_t__ codec_id; scalar_t__ sw_pix_fmt; int /*<<< orphan*/  coded_height; int /*<<< orphan*/  coded_width; } ;
struct TYPE_11__ {int /*<<< orphan*/  BindFlags; int /*<<< orphan*/  surface_type; } ;
struct TYPE_10__ {scalar_t__ type; } ;
struct TYPE_9__ {scalar_t__ format; int initial_pool_size; TYPE_3__* hwctx; void* height; void* width; int /*<<< orphan*/  sw_format; TYPE_2__* device_ctx; } ;
typedef  TYPE_1__ AVHWFramesContext ;
typedef  TYPE_2__ AVHWDeviceContext ;
typedef  TYPE_3__ AVDXVA2FramesContext ;
typedef  TYPE_3__ AVD3D11VAFramesContext ;
typedef  TYPE_5__ AVCodecContext ;
typedef  TYPE_6__ AVBufferRef ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ AV_CODEC_ID_H264 ; 
 scalar_t__ AV_CODEC_ID_HEVC ; 
 scalar_t__ AV_CODEC_ID_MPEG2VIDEO ; 
 scalar_t__ AV_CODEC_ID_VP9 ; 
 scalar_t__ AV_HWDEVICE_TYPE_D3D11VA ; 
 scalar_t__ AV_HWDEVICE_TYPE_DXVA2 ; 
 scalar_t__ AV_PIX_FMT_D3D11 ; 
 scalar_t__ AV_PIX_FMT_DXVA2_VLD ; 
 int /*<<< orphan*/  AV_PIX_FMT_NV12 ; 
 int /*<<< orphan*/  AV_PIX_FMT_P010 ; 
 scalar_t__ AV_PIX_FMT_YUV420P10 ; 
 int /*<<< orphan*/  D3D11_BIND_DECODER ; 
 int /*<<< orphan*/  DXVA2_VideoDecoderRenderTarget ; 
 int /*<<< orphan*/  EINVAL ; 
 void* FFALIGN (int /*<<< orphan*/ ,int) ; 

int ff_dxva2_common_frame_params(AVCodecContext *avctx,
                                 AVBufferRef *hw_frames_ctx)
{
    AVHWFramesContext *frames_ctx = (AVHWFramesContext *)hw_frames_ctx->data;
    AVHWDeviceContext *device_ctx = frames_ctx->device_ctx;
    int surface_alignment, num_surfaces;

    if (device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        frames_ctx->format = AV_PIX_FMT_DXVA2_VLD;
    } else if (device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        frames_ctx->format = AV_PIX_FMT_D3D11;
    } else {
        return AVERROR(EINVAL);
    }

    /* decoding MPEG-2 requires additional alignment on some Intel GPUs,
    but it causes issues for H.264 on certain AMD GPUs..... */
    if (avctx->codec_id == AV_CODEC_ID_MPEG2VIDEO)
        surface_alignment = 32;
    /* the HEVC DXVA2 spec asks for 128 pixel aligned surfaces to ensure
    all coding features have enough room to work with */
    else if (avctx->codec_id == AV_CODEC_ID_HEVC)
        surface_alignment = 128;
    else
        surface_alignment = 16;

    /* 1 base work surface */
    num_surfaces = 1;

    /* add surfaces based on number of possible refs */
    if (avctx->codec_id == AV_CODEC_ID_H264 || avctx->codec_id == AV_CODEC_ID_HEVC)
        num_surfaces += 16;
    else if (avctx->codec_id == AV_CODEC_ID_VP9)
        num_surfaces += 8;
    else
        num_surfaces += 2;

    frames_ctx->sw_format = avctx->sw_pix_fmt == AV_PIX_FMT_YUV420P10 ?
                            AV_PIX_FMT_P010 : AV_PIX_FMT_NV12;
    frames_ctx->width = FFALIGN(avctx->coded_width, surface_alignment);
    frames_ctx->height = FFALIGN(avctx->coded_height, surface_alignment);
    frames_ctx->initial_pool_size = num_surfaces;


#if CONFIG_DXVA2
    if (frames_ctx->format == AV_PIX_FMT_DXVA2_VLD) {
        AVDXVA2FramesContext *frames_hwctx = frames_ctx->hwctx;

        frames_hwctx->surface_type = DXVA2_VideoDecoderRenderTarget;
    }
#endif

#if CONFIG_D3D11VA
    if (frames_ctx->format == AV_PIX_FMT_D3D11) {
        AVD3D11VAFramesContext *frames_hwctx = frames_ctx->hwctx;

        frames_hwctx->BindFlags |= D3D11_BIND_DECODER;
    }
#endif

    return 0;
}