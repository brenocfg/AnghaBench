#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_2__* device_ctx; TYPE_4__* hwctx; TYPE_1__* internal; } ;
struct TYPE_11__ {int /*<<< orphan*/  surfaces; } ;
struct TYPE_10__ {int /*<<< orphan*/  surfaces_internal; } ;
struct TYPE_9__ {int type; } ;
struct TYPE_8__ {TYPE_3__* priv; } ;
typedef  TYPE_3__ QSVFramesContext ;
typedef  TYPE_4__ AVQSVFramesContext ;
typedef  TYPE_5__ AVHWFramesContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOSYS ; 

__attribute__((used)) static int qsv_frames_derive_to(AVHWFramesContext *dst_ctx,
                                AVHWFramesContext *src_ctx, int flags)
{
    QSVFramesContext *s = dst_ctx->internal->priv;
    AVQSVFramesContext *dst_hwctx = dst_ctx->hwctx;
    int i;

    switch (src_ctx->device_ctx->type) {
#if CONFIG_VAAPI
    case AV_HWDEVICE_TYPE_VAAPI:
        {
            AVVAAPIFramesContext *src_hwctx = src_ctx->hwctx;
            s->surfaces_internal = av_mallocz_array(src_hwctx->nb_surfaces,
                                                    sizeof(*s->surfaces_internal));
            if (!s->surfaces_internal)
                return AVERROR(ENOMEM);
            for (i = 0; i < src_hwctx->nb_surfaces; i++) {
                qsv_init_surface(dst_ctx, &s->surfaces_internal[i]);
                s->surfaces_internal[i].Data.MemId = src_hwctx->surface_ids + i;
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
            dst_hwctx->frame_type  = MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
        }
        break;
#endif
#if CONFIG_DXVA2
    case AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2FramesContext *src_hwctx = src_ctx->hwctx;
            s->surfaces_internal = av_mallocz_array(src_hwctx->nb_surfaces,
                                                    sizeof(*s->surfaces_internal));
            if (!s->surfaces_internal)
                return AVERROR(ENOMEM);
            for (i = 0; i < src_hwctx->nb_surfaces; i++) {
                qsv_init_surface(dst_ctx, &s->surfaces_internal[i]);
                s->surfaces_internal[i].Data.MemId = (mfxMemId)src_hwctx->surfaces[i];
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
            if (src_hwctx->surface_type == DXVA2_VideoProcessorRenderTarget)
                dst_hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET;
            else
                dst_hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
        }
        break;
#endif
    default:
        return AVERROR(ENOSYS);
    }

    dst_hwctx->surfaces = s->surfaces_internal;

    return 0;
}