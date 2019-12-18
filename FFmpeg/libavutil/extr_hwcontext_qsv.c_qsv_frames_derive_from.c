#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VASurfaceID ;
struct TYPE_14__ {TYPE_4__* hwctx; TYPE_1__* device_ctx; } ;
struct TYPE_13__ {int nb_surfaces; int /*<<< orphan*/  surface_type; int /*<<< orphan*/  frame_type; int /*<<< orphan*/ ** surfaces; int /*<<< orphan*/ * surface_ids; } ;
struct TYPE_12__ {scalar_t__ MemId; } ;
struct TYPE_11__ {TYPE_3__ Data; } ;
struct TYPE_10__ {int type; } ;
typedef  int /*<<< orphan*/  IDirect3DSurface9 ;
typedef  TYPE_4__ AVVAAPIFramesContext ;
typedef  TYPE_4__ AVQSVFramesContext ;
typedef  TYPE_6__ AVHWFramesContext ;
typedef  TYPE_4__ AVDXVA2FramesContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
#define  AV_HWDEVICE_TYPE_DXVA2 129 
#define  AV_HWDEVICE_TYPE_VAAPI 128 
 int /*<<< orphan*/  DXVA2_VideoDecoderRenderTarget ; 
 int /*<<< orphan*/  DXVA2_VideoProcessorRenderTarget ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET ; 
 void* av_mallocz_array (int,int) ; 

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