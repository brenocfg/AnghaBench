#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ VASurfaceID ;
struct TYPE_16__ {int /*<<< orphan*/ ** data; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  hw_frames_ctx; } ;
struct TYPE_15__ {TYPE_3__* hwctx; } ;
struct TYPE_14__ {int nb_surfaces; TYPE_2__* surfaces; } ;
struct TYPE_12__ {scalar_t__ MemId; } ;
struct TYPE_13__ {TYPE_1__ Data; } ;
typedef  int /*<<< orphan*/  IDirect3DSurface9 ;
typedef  TYPE_3__ AVQSVFramesContext ;
typedef  TYPE_4__ AVHWFramesContext ;
typedef  TYPE_5__ AVFrame ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 int ff_hwframe_map_create (int /*<<< orphan*/ ,TYPE_5__*,TYPE_5__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qsv_map_to(AVHWFramesContext *dst_ctx,
                      AVFrame *dst, const AVFrame *src, int flags)
{
    AVQSVFramesContext *hwctx = dst_ctx->hwctx;
    int i, err;

    for (i = 0; i < hwctx->nb_surfaces; i++) {
#if CONFIG_VAAPI
        if (*(VASurfaceID*)hwctx->surfaces[i].Data.MemId ==
            (VASurfaceID)(uintptr_t)src->data[3])
            break;
#endif
#if CONFIG_DXVA2
        if ((IDirect3DSurface9*)hwctx->surfaces[i].Data.MemId ==
            (IDirect3DSurface9*)(uintptr_t)src->data[3])
            break;
#endif
    }
    if (i >= hwctx->nb_surfaces) {
        av_log(dst_ctx, AV_LOG_ERROR, "Trying to map from a surface which "
               "is not in the mapped frames context.\n");
        return AVERROR(EINVAL);
    }

    err = ff_hwframe_map_create(dst->hw_frames_ctx,
                                dst, src, NULL, NULL);
    if (err)
        return err;

    dst->width   = src->width;
    dst->height  = src->height;
    dst->data[3] = (uint8_t*)&hwctx->surfaces[i];

    return 0;
}