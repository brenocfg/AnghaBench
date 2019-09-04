#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* device_ctx; int /*<<< orphan*/ * hwctx; } ;
struct TYPE_5__ {int type; } ;
typedef  int /*<<< orphan*/  AVQSVFramesContext ;
typedef  TYPE_2__ AVHWFramesContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOSYS ; 

__attribute__((used)) static int qsv_frames_derive_from(AVHWFramesContext *dst_ctx,
                                  AVHWFramesContext *src_ctx, int flags)
{
    AVQSVFramesContext *src_hwctx = src_ctx->hwctx;
    int i;

    switch (dst_ctx->device_ctx->type) {
#if CONFIG_VAAPI
    case AV_HWDEVICE_TYPE_VAAPI:
        {
            AVVAAPIFramesContext *dst_hwctx = dst_ctx->hwctx;
            dst_hwctx->surface_ids = av_mallocz_array(src_hwctx->nb_surfaces,
                                                      sizeof(*dst_hwctx->surface_ids));
            if (!dst_hwctx->surface_ids)
                return AVERROR(ENOMEM);
            for (i = 0; i < src_hwctx->nb_surfaces; i++)
                dst_hwctx->surface_ids[i] =
                    *(VASurfaceID*)src_hwctx->surfaces[i].Data.MemId;
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
        }
        break;
#endif
#if CONFIG_DXVA2
    case AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2FramesContext *dst_hwctx = dst_ctx->hwctx;
            dst_hwctx->surfaces = av_mallocz_array(src_hwctx->nb_surfaces,
                                                   sizeof(*dst_hwctx->surfaces));
            if (!dst_hwctx->surfaces)
                return AVERROR(ENOMEM);
            for (i = 0; i < src_hwctx->nb_surfaces; i++)
                dst_hwctx->surfaces[i] =
                    (IDirect3DSurface9*)src_hwctx->surfaces[i].Data.MemId;
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
            if (src_hwctx->frame_type == MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET)
                dst_hwctx->surface_type = DXVA2_VideoDecoderRenderTarget;
            else
                dst_hwctx->surface_type = DXVA2_VideoProcessorRenderTarget;
        }
        break;
#endif
    default:
        return AVERROR(ENOSYS);
    }

    return 0;
}