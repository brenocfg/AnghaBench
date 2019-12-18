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
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mfxMemId ;
struct TYPE_19__ {TYPE_5__* hwctx; TYPE_2__* device_ctx; TYPE_1__* internal; } ;
struct TYPE_18__ {int nb_surfaces; TYPE_10__* surfaces; void* frame_type; int /*<<< orphan*/  surface_type; int /*<<< orphan*/  surface_ids; } ;
struct TYPE_17__ {TYPE_10__* surfaces_internal; } ;
struct TYPE_16__ {int /*<<< orphan*/  MemId; } ;
struct TYPE_15__ {int type; } ;
struct TYPE_14__ {TYPE_4__* priv; } ;
struct TYPE_13__ {TYPE_3__ Data; } ;
typedef  TYPE_4__ QSVFramesContext ;
typedef  TYPE_5__ AVVAAPIFramesContext ;
typedef  TYPE_5__ AVQSVFramesContext ;
typedef  TYPE_7__ AVHWFramesContext ;
typedef  TYPE_5__ AVDXVA2FramesContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
#define  AV_HWDEVICE_TYPE_DXVA2 129 
#define  AV_HWDEVICE_TYPE_VAAPI 128 
 int /*<<< orphan*/  DXVA2_VideoProcessorRenderTarget ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ENOSYS ; 
 void* MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET ; 
 void* MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET ; 
 void* av_mallocz_array (int,int) ; 
 int /*<<< orphan*/  qsv_init_surface (TYPE_7__*,TYPE_10__*) ; 

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