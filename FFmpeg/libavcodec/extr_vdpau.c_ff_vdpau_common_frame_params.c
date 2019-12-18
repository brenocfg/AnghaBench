#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
typedef  int /*<<< orphan*/  VdpChromaType ;
struct TYPE_9__ {scalar_t__ data; } ;
struct TYPE_8__ {int /*<<< orphan*/  sw_pix_fmt; } ;
struct TYPE_7__ {void* height; void* width; int /*<<< orphan*/  sw_format; int /*<<< orphan*/  format; } ;
typedef  TYPE_1__ AVHWFramesContext ;
typedef  TYPE_2__ AVCodecContext ;
typedef  TYPE_3__ AVBufferRef ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_PIX_FMT_VDPAU ; 
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ av_vdpau_get_surface_parameters (TYPE_2__*,int /*<<< orphan*/ *,void**,void**) ; 

int ff_vdpau_common_frame_params(AVCodecContext *avctx,
                                 AVBufferRef *hw_frames_ctx)
{
    AVHWFramesContext *hw_frames = (AVHWFramesContext*)hw_frames_ctx->data;
    VdpChromaType type;
    uint32_t width;
    uint32_t height;

    if (av_vdpau_get_surface_parameters(avctx, &type, &width, &height))
        return AVERROR(EINVAL);

    hw_frames->format    = AV_PIX_FMT_VDPAU;
    hw_frames->sw_format = avctx->sw_pix_fmt;
    hw_frames->width     = width;
    hw_frames->height    = height;

    return 0;
}